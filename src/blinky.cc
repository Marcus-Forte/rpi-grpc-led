
#include <iostream>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include "blinky_service.hh"
#include <print>


int main(int argc, char** argv) {

    if (argc < 2) {
        std::println(std::cerr, "Usage: {} <chip_name>", argv[0]);
        return 1;
    }

    const std::string chip_name = argv[1];

    BlinkyServiceImpl service(chip_name);

    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "gRPC server listening.." << std::endl;
    server->Wait();

    return 0;
}
