#pragma once

#include <cstdint>

// Interface
class ILED {
public:
  virtual ~ILED() = default;
  virtual void SetOn(uint32_t line, bool on) = 0;
};
