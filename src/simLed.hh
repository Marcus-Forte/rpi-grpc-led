#pragma once

#include "ILED.hh"
#include <string>

class SimLed : public ILED {
public:
  SimLed(const std::string &chip_name);
  ~SimLed() override = default;
  void SetOn(uint32_t line, bool on) override;
  bool isOn(uint32_t line) const override;

  private:
};