// blinky_service.hh
#pragma once

#include "ILED.hh"
#include "blinky.grpc.pb.h"
#include <grpcpp/grpcpp.h>

// Implementation of the BlinkService gRPC service.
class BlinkyServiceImpl final : public BlinkService::Service {
public:
  BlinkyServiceImpl(const std::shared_ptr<ILED> &ledInterface);
  // Override the SetLED RPC method.
  ::grpc::Status SetLED(::grpc::ServerContext *context,
                        const ::SetLEDRequest *request,
                        ::google::protobuf::Empty *response) override;

private:
  std::shared_ptr<ILED> led_interface_;
};