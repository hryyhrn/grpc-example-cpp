#include "service_impl.h"

// Service interface getMyName RPC implementation
grpc::Status ExampleGrpcImpl::getMyName(
    grpc::ServerContext* context,
    const examplegrpc::NameRequest* request,
    examplegrpc::NameResponse* response) 
{
    std::string client_name = request -> name();
    std::cout << "Recieved request from client: " << client_name << "\n";
    response -> set_name(client_name);
    return grpc::Status::OK;
}

// Create and server
void RunServer() {
    // Address and port where the server would run
    std::string server_address("0.0.0.0:50051");
    // Service implementation that the server provides
    ExampleGrpcImpl service;

    // Create instance of the factory (service-server builder)
    grpc::ServerBuilder builder;
    // Address and port where the server would run
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register service implementation with the factory
    builder.RegisterService(&service);
    
    // Create and start server
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << "\n";

    // Call wait on the server so that the thread invoking RunServer() 
    // waits till the server instance terminates
    server -> Wait();
}