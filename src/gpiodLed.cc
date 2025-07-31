
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

void GpiodLed::checkLine(gpiod_line *line, uint32_t offset) const {
  if (!line) {
    auto msg = std::format("Failed to get GPIO line for line {}", offset);
    throw std::runtime_error(msg);
  }

  if (gpiod_line_consumer(line) == nullptr) {
    // Open the line
    if (gpiod_line_request_output(line, "led-blinker", 0) < 0) {
      auto msg =
          std::format("Failed to request line as output for line {}", offset);
      throw std::runtime_error(msg);
    }
  }
}

void GpiodLed::SetOn(uint32_t line, bool on) {
  auto *line_ = gpiod_chip_get_line(chip_, line);
  checkLine(line_, line);
  gpiod_line_set_value(line_, on);
}

bool GpiodLed::isOn(uint32_t line) const {
  auto *line_ = gpiod_chip_get_line(chip_, line);
  checkLine(line_, line);

  int value = gpiod_line_get_value(line_);
  if (value < 0) {
    auto msg = std::format("Failed to read value for line {}", line);
    throw std::runtime_error(msg);
  }

  return value != 0;
}