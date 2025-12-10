// gRPC
#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

// Interface
#include "example_grpc.grpc.pb.h"
#include "example_grpc.pb.h"

// Service interface implementation
class ExampleGrpcImpl final : public examplegrpc::ExampleGrpc::Service {
public:
    // getMyName RPC implementation
    grpc::Status getMyName(
        grpc::ServerContext* context,
        const examplegrpc::NameRequest* request,
        examplegrpc::NameResponse* response
    );
};

// Create and server
void RunServer();