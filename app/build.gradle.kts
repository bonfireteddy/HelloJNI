plugins {
    id("com.android.application")
    id("org.jetbrains.kotlin.android")
}

android {
    namespace = "com.example.hellojni"
    compileSdk = 34
    ndkVersion = "23.0.7599858"

    defaultConfig {
        applicationId = "com.example.hellojni"
        minSdk = 33
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"

//        ndk {
//            abiFilters += "armeabi-v7a"
//            abiFilters += "arm64-v8a"
//            abiFilters += "x86"
//            abiFilters += "x86_64"
//        }

        externalNativeBuild {
            cmake {
                cppFlags("")
            }
        }

        sourceSets {
            getByName("main") {
                jniLibs.srcDir("src/main/cpp/libs")
            }
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }

    externalNativeBuild {
        cmake {
            path ("src/main/cpp/CMakeLists.txt")
        }

        viewBinding {
            enable = true
        }
    }

    kotlinOptions {
        jvmTarget = "1.8"
    }

    packagingOptions {
        pickFirst("lib/armeabi-v7a/libnative-lib.so")
        pickFirst("lib/x86_64/libnative-lib.so")
        pickFirst("lib/x86_64/libnative-lib.so")
    }

}

dependencies {

    implementation("androidx.core:core-ktx:1.13.1")
    implementation("androidx.appcompat:appcompat:1.7.0")
    implementation("com.google.android.material:material:1.12.0")
    implementation("androidx.constraintlayout:constraintlayout:2.1.4")
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.2.0")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.6.0")
}