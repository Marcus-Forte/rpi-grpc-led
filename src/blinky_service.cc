
#include "blinky_service.hh"
#include <print>

BlinkyServiceImpl::BlinkyServiceImpl(const std::shared_ptr<ILED> &ledInterface)
    : led_interface_(ledInterface) {}

::grpc::Status BlinkyServiceImpl::SetLED(::grpc::ServerContext *context,
                                         const ::SetLEDRequest *request,
                                         ::google::protobuf::Empty *response) {

  const auto led_on = request->on();
  const auto line = request->line();
  std::println("SetLED called on line {}. Requested state: {}", line,
               (led_on ? "ON" : "OFF"));
  led_interface_->SetOn(line, led_on);

  return ::grpc::Status::OK;
}