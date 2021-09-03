# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html
project(fbjni)

set (CMAKE_CXX_STANDARD 14)

# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(build_DIR ${CMAKE_SOURCE_DIR}/build)
set(PACKAGE_NAME "my_jni_module")
find_package(fbjni REQUIRED CONFIG)

add_subdirectory(./build/third-party-ndk/grpc/ ${CMAKE_CURRENT_BINARY_DIR}/grpc EXCLUDE_FROM_ALL)

include_directories(
        ../../node_modules/react-native/React
        ../../node_modules/react-native/React/Base
        ../../node_modules/react-native/ReactCommon
        ../../node_modules/react-native/ReactCommon/jsi
        ../../node_modules/react-native/ReactCommon/callinvoker
        ../../node_modules/react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni/ReactCommon
        ../../node_modules/react-native/ReactCommon/turbomodule/core
        ../../node_modules/react-native/ReactCommon/turbomodule
        ../../cpp/
        ../../cpp/net
)

add_library( # Sets the name of the library.
        ${PACKAGE_NAME}
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        ../../node_modules/react-native/ReactCommon/jsi/jsi/jsi.cpp
        ../../node_modules/react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni/ReactCommon/CallInvokerHolder.cpp
        ../../node_modules/react-native/ReactCommon/turbomodule/core/TurboModule.cpp
        ../../cpp/NativeModules.cpp
        ../../cpp/TrimNativeModule.cpp
        ../../cpp/jsiInstaller.cpp
        ./src/cpp/Logger.cpp
        ../../cpp/net/helloworld.grpc.pb.cc
        ../../cpp/net/helloworld.pb.cc
        )

target_link_libraries(${PACKAGE_NAME}
        fbjni::fbjni
        android
        log
        grpc++_reflection
        grpc++
        libprotobuf
)


add_library(
        turbomodulejsijni
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        ../../cpp/empty.cpp
)
