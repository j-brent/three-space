#pragma once

#include "real.h"

#include <numbers>

namespace sp3
{
  constexpr real pi = std::numbers::pi_v<real>;
  
  class angle
  {
  public:
    explicit angle(real radians) : m_radians{radians} {}

    real rad() const { return m_radians; }

    real deg() const { return m_radians * 180 / pi; }

  private:
    real m_radians;
  };
}