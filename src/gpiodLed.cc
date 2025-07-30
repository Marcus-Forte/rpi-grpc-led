
// filepath: /workspaces/rpi-grpc-led/src/gpiodLed.cc
#include "gpiodLed.hh"
#include <print>
#include <stdexcept>

GpiodLed::GpiodLed(const std::string &chip_name) : chip_(nullptr) {
  chip_ = gpiod_chip_open_by_name(chip_name.c_str());
  if (!chip_) {
    throw std::runtime_error("Failed to open GPIO chip\n");
  }
}

GpiodLed::~GpiodLed() { gpiod_chip_close(chip_); }

void GpiodLed::SetOn(uint32_t line, bool on) {
  auto *line_ = gpiod_chip_get_line(chip_, line);
  if (!line_) {
    auto msg = std::format("Failed to get GPIO line for line {}", line);
    throw std::runtime_error(msg);
  }

  if (gpiod_line_consumer(line_) == nullptr) {
    // Open the line
    if (gpiod_line_request_output(line_, "led-blinker", 0) < 0) {
      auto msg =
          std::format("Failed to request line as output for line {}", line);
      throw std::runtime_error(msg);
    }
  }

  gpiod_line_set_value(line_, on);
}