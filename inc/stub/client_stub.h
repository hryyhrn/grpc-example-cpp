// gRPC
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

// Interface
#include "example_grpc.grpc.pb.h"
#include "example_grpc.pb.h"

// Client stub implementation
class ExampleGrpcClient {
private:
    std::unique_ptr<examplegrpc::ExampleGrpc::Stub> client_stub;

public:
    // Client object constructor
    // Creates an instance of the client stub from the interface
    ExampleGrpcClient(std::shared_ptr<grpc::ChannelInterface> channel);

    // Service method (getMyName) call implementation
    std::string getMyName(std::string client_name);

private:
    // getMyName() stub implementation function
    std::string getMyNameImpl(const examplegrpc::NameRequest request, examplegrpc::NameResponse* response);
};