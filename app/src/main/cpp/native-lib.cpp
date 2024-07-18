#include <jni.h>
#include <string>
#include <stdio.h> // 표준 입출력 함수
#include <unistd.h> // 유닉스 표준 함수
#include <stdlib.h> // 표준 라이브러리 함수
#include <sys/types.h> // 소켓 통신 및 파일 관련 함수와 타입
#include <sys/stat.h> // 소켓 통신 및 파일 관련 함수와 타입
#include <sys/socket.h> // 소켓 통신 및 파일 관련 함수와 타입
#include <sys/un.h> // 소켓 통신 및 파일 관련 함수와 타입
#include <android/log.h> // android log출력을 위한 함수


#define MAXLINE 1024 // 한 번에 송수신할 데이터의 최대 크기를 정의
#define SOCK_NAME "/data/trayctl/trayctl.sock" // 소켓 파일 경로
#define LOG_TAG "UNIXSocketClient" // 로그 태그
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__) // ANDROID LOG PRINT

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_hellojni_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_hellojni_MainActivity_unixSocketClient(JNIEnv *env, jobject thiz, jstring jmodule, jstring jaction, jstring jparam1, jstring jparam2){

    int client_len; // 소켓 주소 구조체의 길이를 저장
    int client_sockfd; // 클라이언트 소켓 파일 디스크립터

    char buf_send[MAXLINE]; // 송신할 데이터를 저장할 버퍼
    char buf_recv[MAXLINE]; // 수신할 데이터를 저장할 버퍼

    struct sockaddr_un clientaddr; // 클라이언트 주소 구조체

    // 명령어 인자  변환 할당
    //JNI 함수 env ->GetStringUTFChars는 Java 문자열 (jstring)을 UTF-8 형식의 C 스타일 문자열 (const char*)로 변환.
    const char *module = env ->GetStringUTFChars(jmodule, 0);
    const char *action = env ->GetStringUTFChars(jaction, 0);
    const char *param1 = env ->GetStringUTFChars(jparam1, 0);
    const char *param2 = env ->GetStringUTFChars(jparam2, 0);

    // UNIX 도메인 소켓 생성 AF_UNIX(로컬 통신을 위한 주소 체계)
    // SOCK_STREAM(스트림 소켓)
    client_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    // 소켓 생성에 실패하면 오류 메시지를 출력하고 종료
    if(client_sockfd == -1){
        LOGD("[tool] error: socket creation failed");
        return env -> NewStringUTF("[tool] error: socket creation failed");
    }

    LOGD("[tool] 소켓 생성 성공");

    // 소켓 주소 구조체 설정
    bzero(&clientaddr, sizeof(clientaddr)); // 주소 구조체 0으로 초기화
    clientaddr.sun_family = AF_UNIX; // 주소 체계를 UNIX 도메인으로 설정
    strcpy(clientaddr.sun_path, SOCK_NAME); // 소켓 파일 경로 설정
    client_len = sizeof(clientaddr); // 주소 구조체의 길이를 설정

    // 서버에 연결 - 실패 시 오류 메시지를 출력하고 종료
    if (connect(client_sockfd, (struct sockaddr *)&clientaddr, client_len) < 0) {
        close(client_sockfd);
        LOGD("[tool] Connect error: connection failed");
        return env->NewStringUTF("[tool] Connect error: connection failed");
    }

    // 송수신 버퍼 초기화 - 송수신 버퍼를 0으로 초기화
    memset(buf_send, 0x00, MAXLINE);
    memset(buf_recv, 0x00, MAXLINE);

    // 메시지 생성 및 전송 - JSON 형식의 요청 메시지를 생성
    snprintf(buf_send, sizeof(buf_send),
             "{\"type\":\"request\",\"module\":\"%s\",\"data\":{\"cmd\":\"%s\",\"sub_cmd1\":\"%s\",\"sub_cmd2\":\"%s\"}}",
            module, action, param1 ? param1 : "none", param2 ? param2 : "none");

    LOGD("[tool] Send IPC Data-> %s", buf_send); // 생성된 메시지를 출력
    write(client_sockfd, buf_send, strlen(buf_send)); // 메시지를 서버로 전송

    LOGD("[tool] Waiting IPC response"); // 응답 수신 대기
    read(client_sockfd, buf_recv, MAXLINE); // 응답 수신 buf_recv에 저장
    LOGD("[tool] Recv IPC Data-> %s", buf_recv); // 응답 IPC Data 출력

    //소켓은 제한된 시스템 리소스. 사용 후 닫지 않으면 리소스 누수가 발생할 수 있다
    close(client_sockfd); // 소켓을 닫기

    // GetStringUTFChars로 할당한 C 스타일 문자열의 메모리를 해제
    // 변환된 문자열은 힙 메모리에 할당되기 때문에, 이를 해제하지 않으면 메모리 누수가 발생할 수 있음
    env->ReleaseStringUTFChars(jmodule, module);
    env->ReleaseStringUTFChars(jaction, action);
    env->ReleaseStringUTFChars(jparam1, param1);
    env->ReleaseStringUTFChars(jparam2, param2);

    // 네이티브 함수의 결과를 Java 문자열(jstring)로 변환하여 반환
    return env->NewStringUTF(buf_recv);
}





























