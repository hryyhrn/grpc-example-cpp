#include "client_stub.h"

int main() {
    // Create a gRPC channel for the stub to communicate to the gRPC server
    // Specify address and port of the server we want to connect to
    ExampleGrpcClient example(
        CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())
    );

    // Invoke the RPC
    std::cout << "Client name: " << example.getMyName("hryhrn") << "\n";

    return 0;
}