#include "TrimNativeModule.h"
#include "net/Client.h"

namespace my_namespace {

jsi::String TrimNativeModule::nativeTrim(jsi::Runtime &rt, const jsi::String &text) {
    std::string str = text.utf8(rt);
    if (str.length() > 10) {
        str = str.substr(0, 7) + "...";
    }
    Client c;
    c.getResponseFromServer(str, [](std::string response){
      //...
    });
    return jsi::String::createFromUtf8(rt, str);
}

} // namespace my_namespace
