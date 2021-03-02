#pragma once

#include <jsi/jsi.h>
#include "NativeModules.h"

using namespace facebook;

namespace my_namespace {

class TrimNativeModule : public facebook::react::SchemaCxxSpecJSI {
public:
  jsi::String nativeTrim(jsi::Runtime &rt, const jsi::String &text) override;
  TrimNativeModule(std::shared_ptr<facebook::react::CallInvoker> jsInvoker) :
        facebook::react::SchemaCxxSpecJSI(jsInvoker) {};
};

} // namespace my_namespace
