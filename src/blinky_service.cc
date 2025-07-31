
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

  try {
    led_interface_->SetOn(line, led_on);
  } catch (const std::exception &e) {
    std::cerr << "Error setting LED state: " << e.what() << std::endl;
    return ::grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  }

  return ::grpc::Status::OK;
}

::grpc::Status BlinkyServiceImpl::IsOn(::grpc::ServerContext *context,
                                       const ::IsOnRequest *request,
                                       ::IsOnResponse *response) {
  const auto line = request->line();
  std::println("IsOn called for line {}", line);

  try {
    response->set_is_on(led_interface_->isOn(line));
  } catch (const std::exception &e) {
    std::cerr << "Error checking LED state: " << e.what() << std::endl;
    return ::grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  }

  return ::grpc::Status::OK;
}