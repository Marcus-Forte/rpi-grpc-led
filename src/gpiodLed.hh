
#pragma once

#include "ILED.hh"
#include <gpiod.h>
#include <string>

class GpiodLed : public ILED {
public:
  GpiodLed(const std::string &chip_name);
  ~GpiodLed() override;

  void SetOn(uint32_t line, bool on) override;
  bool isOn(uint32_t line) const override;

private:
  void checkLine(gpiod_line * line, uint32_t offset) const;
  gpiod_chip *chip_; // Pointer to the GPIO line.
};