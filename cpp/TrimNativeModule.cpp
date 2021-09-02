#include "TrimNativeModule.h"
#include "Logger.h"

#include <grpcpp/grpcpp.h>

#include "net/helloworld.pb.h"
#include "net/helloworld.grpc.pb.h"

#include <android/log.h>

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
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

void sendGRPCMessage() {
  std::string target_str = "10.0.2.2:50051";
  std::string arg_str("--target");
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::string user("world");
  std::string reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;
  __android_log_print(ANDROID_LOG_VERBOSE, "COMM", "Greeter received: %s", reply.c_str());
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
