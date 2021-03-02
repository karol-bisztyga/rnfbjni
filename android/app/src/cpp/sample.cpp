#include <jsi/jsi.h>
#include <jni.h>
#include <fbjni/fbjni.h>
// #include "DraftNativeModule.h"

using namespace facebook;
/**/
extern "C"
{
    JNIEXPORT void JNICALL
    Java_com_rnfbjni_MainActivity_install(JNIEnv *env, jobject thiz, jlong runtimePtr)
    {
        jsi::Runtime *runtime = (jsi::Runtime *)runtimePtr;
        //        std::shared_ptr<comm::DraftNativeModule> nativeModule = std::make_shared<comm::DraftNativeModule>(jsCallInvoker);
        //
        //        runtime->global().setProperty(
        //                                     runtime,
        //                                     jsi::PropNameID::forAscii(*runtime, "commModule"),
        //                                     jsi::Object::createFromHostObject(runtime, nativeModule));
        runtime->global().setProperty(
            *runtime,
            jsi::PropNameID::forAscii(*runtime, "mytest"),
            jsi::Value(*runtime, 777333));
    }
}
/**/
