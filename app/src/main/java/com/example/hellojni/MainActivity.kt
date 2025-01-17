package com.example.hellojni

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.example.hellojni.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    // 전역 변수로 바인딩 객체 선언
    private var mBinding: ActivityMainBinding? = null

    // 매번 null체크를 할 필요없이 편의성을 위해 바인딩 변수 재 선언
    private val binding get() = mBinding!!

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // 자동 생성된 뷰 바인딩 클래스에서의 inflate라는 매서드를 활용해서
        // 액티비티에서 사용할 바인딩 클래스의 인스턴스 생성
        mBinding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val jniHelper = JNIHelper.getInstance()

        Log.d("JNI String 호출", jniHelper.stringFromJNI())
        binding.jnitext.text = jniHelper.stringFromJNI()

        jniHelper.unixSocketClient("tray", "move","5", "")
        jniHelper.unixSocketClient("medicine", "move","out", "current")
    }
}