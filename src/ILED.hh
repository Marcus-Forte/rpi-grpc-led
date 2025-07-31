#pragma once

#include <cstdint>

// Interface
class ILED {
public:
  virtual ~ILED() = default;
  virtual void SetOn(uint32_t line, bool on) = 0;
  virtual bool isOn(uint32_t line) const = 0;
};
