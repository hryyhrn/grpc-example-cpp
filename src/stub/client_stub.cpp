#include "client_stub.h"

// Client object constructor
ExampleGrpcClient::ExampleGrpcClient(std::shared_ptr<grpc::ChannelInterface> channel) : client_stub(examplegrpc::ExampleGrpc::NewStub(channel)) {};

// Service method (getMyName) call implementation
std::string ExampleGrpcClient::getMyName(std::string client_name) {
    examplegrpc::NameRequest request;
    examplegrpc::NameResponse response;
    request.set_name(client_name);
    return getMyNameImpl(request, &response);
}

// getMyName() stub implementation function
std::string ExampleGrpcClient::getMyNameImpl(const examplegrpc::NameRequest request, examplegrpc::NameResponse* response) {
    // To set the client's configs for the RPC session
    grpc::ClientContext context;

    // The stub marshals and invokes the RPC
    grpc::Status status = client_stub -> getMyName(&context, request, response);

    // Return the necessary result
    return response -> name();
}