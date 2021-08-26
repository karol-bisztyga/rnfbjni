  #import <Foundation/Foundation.h>

#import <GRPCClient/GRPCCall+ChannelArg.h>
#import <GRPCClient/GRPCCall+Tests.h>
#import <GRPCClient/GRPCTransport.h>

#include <Helloworld.pbrpc.h>

#import "../cpp/net/Client.h"

@interface HLWResponseHandler : NSObject<GRPCProtoResponseHandler>

@end

// A response handler object dispatching messages to main queue
@implementation HLWResponseHandler
{
  std::function<void(std::string)> clb;
}

- (id)initWithCallback:(std::function<void(std::string)>)clb {
  self->clb = clb;
  return self;
}

- (dispatch_queue_t)dispatchQueue {
  return dispatch_get_main_queue();
}

- (void)didReceiveProtoMessage:(GPBMessage *)message {
  NSLog(@"received response: %@", [message valueForKey:@"message"]);
  NSString * nsStr = [message valueForKey:@"message"];
  std::string str([nsStr UTF8String]);
  self->clb(str);
}

@end

void Client::getResponseFromServer(std::string message, std::function<void(std::string)> clb) {
  NSLog(@"HERE hello from client #1");
  
  static NSString * const kHostAddress = @"localhost:50051";
  HLWGreeter *client = [[HLWGreeter alloc] initWithHost:kHostAddress];
  HLWHelloRequest *request = [HLWHelloRequest message];
  request.name = [NSString stringWithCString:message.c_str()
                                        encoding:[NSString defaultCStringEncoding]];

  GRPCMutableCallOptions *options = [[GRPCMutableCallOptions alloc] init];
  // this example does not use TLS (secure channel); use insecure channel instead
  options.transport = GRPCDefaultTransportImplList.core_insecure;
  options.userAgentPrefix = @"HelloWorld/1.0";
  HLWResponseHandler *rh = [[HLWResponseHandler alloc] initWithCallback:clb];

  [[client sayHelloWithMessage:request
               responseHandler:rh
                   callOptions:options] start];
  
  NSLog(@"HERE hello from client #2");
}
