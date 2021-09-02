#include "TrimNativeModule.h"
#include "Logger.h"

#include <grpcpp/grpcpp.h>

#include "net/helloworld.pb.h"
#include "net/helloworld.grpc.pb.h"

using my_namespace::Logger;

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      Logger::log(std::to_string(status.error_code()) + ": " + status.error_message());
      return "RPC failed(see the logs)";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};


// platform specific defines here
#ifdef __ANDROID__
#define HOST_ADDRESS "10.0.2.2"
#else
#define HOST_ADDRESS "localhost"
#endif

void sendGRPCMessage() {
  std::string target_str = HOST_ADDRESS;
  target_str += ":50051";
  std::string arg_str("--target");
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::string user("world");
  std::string reply = greeter.SayHello(user);
  Logger::log("Greeter received: " + reply);
}

namespace my_namespace {

jsi::String TrimNativeModule::nativeTrim(jsi::Runtime &rt, const jsi::String &text) {
    std::string str = text.utf8(rt);
    if (str.length() > 10) {
        str = str.substr(0, 7) + "...";
    }
    Logger::log("Logger test");
    sendGRPCMessage();
    return jsi::String::createFromUtf8(rt, str);
}

} // namespace my_namespace
