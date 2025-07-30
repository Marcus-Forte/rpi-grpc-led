
#pragma once

#include "ILED.hh"
#include <gpiod.h>
#include <string>

class GpiodLed : public ILED {
public:
  GpiodLed(const std::string &chip_name);
  ~GpiodLed() override;

  void SetOn(uint32_t line, bool on) override;

private:
  gpiod_chip *chip_; // Pointer to the GPIO line.
};