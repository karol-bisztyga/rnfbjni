# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(build_DIR ${CMAKE_SOURCE_DIR}/build)
set(PACKAGE_NAME "my_jni_module")

find_package(fbjni REQUIRED CONFIG)

include_directories(
  ../../node_modules/react-native/React
  ../../node_modules/react-native/React/Base
  ../../node_modules/react-native/ReactCommon
  ../../node_modules/react-native/ReactCommon/jsi
  ../../node_modules/react-native/ReactCommon/callinvoker
  ../../node_modules/react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni/ReactCommon
  ../../node_modules/react-native/ReactCommon/turbomodule/core/
  # external libs
  ./build/third-party-ndk/folly
  ./build/third-party-ndk/glog
  ./build/third-party-ndk/boost/boost
  ./build/third-party-ndk/double-conversion
  # custom cpp
  ./src/cpp/
)

# search for all cpp files in this directory
file(GLOB ANDROID_NATIVE_CODE "./src/cpp/*.cpp")
file(GLOB FOLLY "./build/third-party-ndk/folly/folly/**/*.cpp")
file(GLOB DOUBLE_CONVERSION_SOURCES "./build/third-party-ndk/double-conversion/double-conversion/*.cc")
file(GLOB GLOG_SOURCES "./build/third-party-ndk/glog/glog-0.3.5/src/*.cc")

# include(${CMAKE_CURRENT_SOURCE_DIR}/build/third-party-ndk/glog/glog-0.3.5/CMakeLists.txt)

add_library(
        ${PACKAGE_NAME}
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        ../../node_modules/react-native/ReactCommon/jsi/jsi/jsi.cpp
        ../../node_modules/react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni/ReactCommon/CallInvokerHolder.cpp
        ../../node_modules/react-native/ReactCommon/turbomodule/core/TurboModule.cpp

        # folly
        ./build/third-party-ndk/folly/folly/detail/Futex.cpp
        ./build/third-party-ndk/folly/folly/synchronization/ParkingLot.cpp
        ./build/third-party-ndk/folly/folly/lang/SafeAssert.cpp
        ./build/third-party-ndk/folly/folly/FileUtil.cpp
        ./build/third-party-ndk/folly/folly/Subprocess.cpp
        ./build/third-party-ndk/folly/folly/File.cpp
        ./build/third-party-ndk/folly/folly/Format.cpp
        ./build/third-party-ndk/folly/folly/Conv.cpp
        ./build/third-party-ndk/folly/folly/io/IOBuf.cpp
        ./build/third-party-ndk/folly/folly/memory/detail/MallocImpl.cpp
        ./build/third-party-ndk/folly/folly/ScopeGuard.cpp
        ./build/third-party-ndk/folly/folly/hash/SpookyHashV2.cpp
        ./build/third-party-ndk/folly/folly/io/IOBufQueue.cpp
        ./build/third-party-ndk/folly/folly/lang/Assume.cpp
        ./build/third-party-ndk/folly/folly/String.cpp

        # double-conversion
        ${DOUBLE_CONVERSION_SOURCES}

        # custom cpp code
        ${ANDROID_NATIVE_CODE}
)

add_definitions(
  -DFOLLY_NO_CONFIG=1
  -DFOLLY_HAVE_CLOCK_GETTIME=1
  -DFOLLY_HAVE_MEMRCHR=1
  -DFOLLY_USE_LIBCPP=1
  -DFOLLY_MOBILE=1
  -DON_ANDROID
)

find_library(log-lib log)

target_link_libraries(${PACKAGE_NAME}
        fbjni::fbjni
        android
        log
)

# add a dummy library which is required by CallInvokerHolderImpl.java
add_library(
        turbomodulejsijni
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        ./src/cpp/empty.cpp
)
