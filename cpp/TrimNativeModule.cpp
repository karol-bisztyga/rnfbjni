#include "TrimNativeModule.h"
#include "Logger.h"

#include "libopaque-cmake/opaque.h"

namespace my_namespace
{
  Opaque_Ids ids = {4, (uint8_t *)"user", 6, (uint8_t *)"server"};
  Opaque_PkgConfig cfg = {
      .skU = NotPackaged,
      .pkU = NotPackaged,
      .pkS = InSecEnv,
      .idS = NotPackaged,
      .idU = NotPackaged,
  };

  jsi::String TrimNativeModule::nativeTrim(jsi::Runtime &rt, const jsi::String &text)
  {
    // const int envLen = 0;
    const uint32_t envLen = opaque_envelope_len(&cfg, &ids);
    std::string str = text.utf8(rt);
    if (str.length() > 10)
    {
      str = str.substr(0, 7) + "...{"+ std::to_string(envLen) +"}";
    }
    Logger::log("Logger test");
    return jsi::String::createFromUtf8(rt, str);
  }

} // namespace my_namespace
