// blinky_service.hh
#pragma once

#include <grpcpp/grpcpp.h>
#include "blinky.grpc.pb.h"
#include <gpiod.h>

// Implementation of the BlinkService gRPC service.
class BlinkyServiceImpl final : public BlinkService::Service {
public:
    BlinkyServiceImpl(const std::string& chip_name);
        ~BlinkyServiceImpl();
    // Override the SetLED RPC method.
    ::grpc::Status SetLED(::grpc::ServerContext* context,
                          const ::SetLEDRequest* request,
                          ::google::protobuf::Empty* response) override;

private:
    gpiod_chip* chip_; // Pointer to the GPIO line.
};