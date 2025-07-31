#include "simLed.hh"
#include <print>

SimLed::SimLed(const std::string &chip_name) {
  // Simulate initialization with chip name
  std::println("Simulated LED initialized with chip name: {}", chip_name);
}

void SimLed::SetOn(uint32_t line, bool on) {
  {
    // Simulate setting the LED state
    if (on) {
      std::println("Simulated LED on line {} is ON", line);
    } else {
      std::println("Simulated LED on line {} is OFF", line);
    }
  }
}

bool SimLed::isOn(uint32_t line) const {
  // Simulate checking the LED state
  std::println("Simulated check for LED on line {}", line);
  return false; // Always return false for simulation
}