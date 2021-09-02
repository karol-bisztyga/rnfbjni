
#import "Logger.h"
#import <Foundation/Foundation.h>

namespace my_namespace {

void Logger::log(const std::string str) {
  NSLog(
      @"RNFBJNI: %@",
      [NSString stringWithCString:str.c_str()
                         encoding:[NSString defaultCStringEncoding]]);
};

} // namespace my_namespace
