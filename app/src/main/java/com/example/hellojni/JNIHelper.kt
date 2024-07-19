package com.example.hellojni

//Singleton Class
class JNIHelper private constructor(){

    init {
        System.loadLibrary("native-lib")
    }

    companion object{
        @Volatile
        private  var instance: JNIHelper? = null

        fun getInstance(): JNIHelper =
            instance ?: synchronized(this){
                instance ?: JNIHelper().also { instance = it }
            }
    }

    // JNI String print test 함수
    external fun stringFromJNI(): String

    //UNIX Donmain Socket 통신으로 trayctl제어 명령어를 Server로 송신하는 함수
    external fun unixSocketClient(module:String, action:String, param1:String, param2:String): String

}