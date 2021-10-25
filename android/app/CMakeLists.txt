PROJECT(rnfbjni C CXX)

# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

include(FetchContent)

cmake_minimum_required(VERSION 3.18.1)

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

FetchContent_Declare(Sodium
  GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
)
set(SODIUM_DISABLE_TESTS ON)
FetchContent_MakeAvailable(Sodium)


set(LIBOPAQUE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cpp/libopaque-cmake)
# add_subdirectory(${LIBOPAQUE_PATH})

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
        ${LIBOPAQUE_PATH}/
        ${LIBOPAQUE_PATH}/aux/
)

set_source_files_properties(${LIBOPAQUE_PATH}/common.c PROPERTIES LANGUAGE CXX)
set_source_files_properties(${LIBOPAQUE_PATH}/opaque.c PROPERTIES LANGUAGE CXX)
set_source_files_properties(${LIBOPAQUE_PATH}/aux/kdf_hkdf_sha256.c PROPERTIES LANGUAGE CXX)

add_library( # Sets the name of the library.
        ${PACKAGE_NAME}
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        ../../node_modules/react-native/ReactCommon/jsi/jsi/jsi.cpp
        ../../node_modules/react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni/ReactCommon/CallInvokerHolder.cpp
        ../../node_modules/react-native/ReactCommon/turbomodule/core/TurboModule.cpp

        ${LIBOPAQUE_PATH}/common.c
        ${LIBOPAQUE_PATH}/opaque.c
        ${LIBOPAQUE_PATH}/aux/kdf_hkdf_sha256.c

        ../../cpp/NativeModules.cpp
        ../../cpp/TrimNativeModule.cpp
        ../../cpp/jsiInstaller.cpp
        ./src/cpp/Logger.cpp
        )

target_link_libraries(${PACKAGE_NAME}
        fbjni::fbjni
        android
        log
  sodium
)


add_library(
        turbomodulejsijni
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        ../../cpp/empty.cpp
)
