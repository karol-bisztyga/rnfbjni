#include <jsi/jsi.h>
#include <fbjni/fbjni.h>
#include <CallInvokerHolder.h>
#include "TrimNativeModule.h"

using namespace facebook::jni;

class MyHybrid : public jni::HybridClass<MyHybrid> {
 public:
  static auto constexpr kJavaDescriptor =
      "Lcom/rnfbjni/MyHybrid;";

   static void initHybrid(
        jni::alias_ref<jhybridobject> jThis,
        jlong jsContext,
        jni::alias_ref<facebook::react::CallInvokerHolder::javaobject> jsCallInvokerHolder)
    {
      jsi::Runtime *runtime = (jsi::Runtime *)jsContext;
      auto jsCallInvoker = jsCallInvokerHolder->cthis()->getCallInvoker();
        std::shared_ptr<my_namespace::TrimNativeModule> nativeModule =
            std::make_shared<my_namespace::TrimNativeModule>(jsCallInvoker);


        runtime->global().setProperty(
             *runtime,
             jsi::PropNameID::forAscii(*runtime, "trimModule"),
             jsi::Object::createFromHostObject(*runtime, nativeModule));
    }

  static void registerNatives() {
    javaClassStatic()->registerNatives({
        makeNativeMethod("initHybrid", MyHybrid::initHybrid),
    });
  }

 private:
  friend HybridBase;

};

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void*) {
    return facebook::jni::initialize(vm, [] {
        MyHybrid::registerNatives();
    });
}

