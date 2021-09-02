#include "Logger.h"

#include <android/log.h>

namespace my_namespace {

void Logger::log(const std::string str) {
  __android_log_print(ANDROID_LOG_VERBOSE, "RNFBJNI", "%s", str.c_str());
};

} // namespace my_namespace
