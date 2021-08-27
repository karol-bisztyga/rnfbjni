#include "Client.h"

#include <android/log.h>
#include <grpcpp/grpcpp.h>

#include "helloworld.pb.h"
#include "helloworld.grpc.pb.h"

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
      throw std::runtime_error("RPC failed ["+ std::to_string(status.error_code()) +"]: " + status.error_message());
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

void Client::getResponseFromServer(
  std::string message,
  std::function<void(std::string)> clb
) {
  // 10.0.2.2 is for android emulator
  // for a real device use ifconfig to get your local hostname
  std::string target_str = "10.0.2.2:50051";
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::string reply = greeter.SayHello("world");
  __android_log_print(ANDROID_LOG_INFO, "HERE", "Greeter received: %s", reply.c_str());
  clb(reply);
}