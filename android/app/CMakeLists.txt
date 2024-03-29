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

    #THIS RESULTS IN AN ERROR:
    #Could not find a package configuration file provided by "fbjni" with any of
    #the following names:
    #
    #fbjniConfig.cmake
    #fbjni-config.cmake
    #
    #Add the installation prefix of "fbjni" to CMAKE_PREFIX_PATH or set
    #"fbjni_DIR" to a directory containing one of the above files.  If "fbjni"
    #provides a separate development package or SDK, be sure it has been
    #installed.
find_package(fbjni REQUIRED CONFIG)

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
        )

target_link_libraries(${PACKAGE_NAME}
        fbjni::fbjni
        android
        log
)


add_library(
        turbomodulejsijni
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        ../../cpp/empty.cpp
)
