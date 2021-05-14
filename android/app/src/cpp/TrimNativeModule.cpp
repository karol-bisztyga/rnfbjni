#include "TrimNativeModule.h"

#include <folly/MPMCQueue.h>

namespace my_namespace {

jsi::String TrimNativeModule::nativeTrim(jsi::Runtime &rt, const jsi::String &text) {
  folly::MPMCQueue<int> q(10);
  q.write(5);
  q.write(6);
  q.write(8);

  std::string str = text.utf8(rt);
  if (str.length() > 10) {
    str = str.substr(0, 7) + "...("+ std::to_string(q.size()) +")";
  }
  return jsi::String::createFromUtf8(rt, str);
}

} // namespace my_namespace
