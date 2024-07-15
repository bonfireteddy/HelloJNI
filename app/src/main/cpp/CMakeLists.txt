# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("HelloJNI")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        # HelloJni.c
        native-lib.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

#-----------------------------------------------------------------------
#add_library( SERIAL_LIB
#            STATIC
#            IMPORTED )
#
#GENERATE_EXPORT_HEADER(SERIAL_LIB
#        BASE_NAME SERIAL_LIB
#        EXPORT_MACRO_NAME SERIAL_LIB_EXPORTS
#        EXPORT_FILE_NAME init_serial.h
##        STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
#        )


#set_target_properties( # Specifies the target library.
#        imported-lib
#
#        # Specifies the parameter you want to define.
#        PROPERTIES IMPORTED_LOCATION
#
#        # Provides the path to the library you want to import.
##        imported-lib/src/${ANDROID_ABI}/libimported-lib.so
##        src/main/cpp/serial_static_lib.lib
#        imported-lib/serial_static_lib.lib
#        )
#include_directories( src/main/cpp/ )

#LINK_DIRECTORIES(src/main/cpp)
##
#find_library(
#        SERIAL_LIB
#        serial_static_lib.lib
#        HINTS src/main/cpp
#        REQUIRED)

#-----------------------------------------------------------------------
#
## searching for include directory
#find_path(SERIAL_LIB_INCLUDE_DIR init_serial.h)
## searching for library file
#find_library(SERIAL_LIB_LIBRARY serial_static_lib)
#if (SERIAL_LIB_INCLUDE_DIR AND SERIAL_LIB_LIBRARY)
#    # you may need that if further action in your CMakeLists.txt depends
#    # on detecting your library
#    set(SIFTGPU_FOUND TRUE)
#    # you may need that if you want to conditionally compile some parts
#    # of your code depending on library availability
##    add_definitions(-DHAVE_LIBSIFTGPU=1)
#    # those two, you really need
#    include_directories(${SERIAL_LIB_INCLUDE_DIR})
#    set(native_c_1 ${log-lib} ${SERIAL_LIB_LIBRARY})
#endif ()

#-----------------------------------------------------------------------

#cmake_minimum_required(VERSION 3.0)
#
#include(GenerateExportHeader)
#
#PROJECT("app1")
#
#INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}")
#ADD_LIBRARY(m SHARED m.c m.h m_exports.h)
#GENERATE_EXPORT_HEADER(m
#        BASE_NAME m
#        EXPORT_MACRO_NAME M_EXPORTS
#        EXPORT_FILE_NAME m_exports.h
#        STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)

#ADD_EXECUTABLE(myexe main.c)
#TARGET_LINK_LIBRARIES(myexe m)

#-----------------------------------------------------------------------

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        #        ${log-lib} ${SERIAL_LIB})
        #        ${log-lib} m)
        ${log-lib})