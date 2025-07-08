// filepath: /workspaces/rpi-blinky/src/blinky_service.cc

#include "blinky_service.hh"
#include <print>

BlinkyServiceImpl::BlinkyServiceImpl(const std::string& chip_name) {
    // Initialize GPIO chip and line here if needed.
    
    chip_ = gpiod_chip_open_by_name(chip_name.c_str());
    if (!chip_) {
        throw std::runtime_error("Failed to open GPIO chip\n");
    }

}

BlinkyServiceImpl::~BlinkyServiceImpl() {
    gpiod_chip_close(chip_);
}

// Implementation of the SetLED RPC method.
::grpc::Status BlinkyServiceImpl::SetLED(::grpc::ServerContext* context,
                                         const ::SetLEDRequest* request,
                                         ::google::protobuf::Empty* response) {
   
    const auto led_on = request->on();
    const auto line = request->line();
    std::println("SetLED called on line {}. Requested state: {}", line, (led_on ? "ON" : "OFF"));

    auto * line_ = gpiod_chip_get_line(chip_, line);
    if (!line_) {
        auto msg = std::format("Failed to get GPIO line for line {}", line);
        std::print(std::cerr, "{}", msg);
        return ::grpc::Status(::grpc::StatusCode::INTERNAL, msg);
    }
    
    if(gpiod_line_consumer(line_) == nullptr) {
        // Open the line
        if (gpiod_line_request_output(line_, "led-blinker", 0) < 0) {
            auto msg = std::format("Failed to request line as output for line {}", line);
            std::print(std::cerr, "{}", msg);
            return ::grpc::Status(::grpc::StatusCode::INTERNAL, msg);
        }
    }

    gpiod_line_set_value(line_, request->on());

    return ::grpc::Status::OK;
}