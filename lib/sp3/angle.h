#pragma once

#include "real.h"

#include <numbers>
#include <ostream>
#include <format>

namespace sp3
{
  constexpr real pi = std::numbers::pi_v<real>;
  
  namespace literals
  {
    constexpr real operator""_degrees(long double deg)
    {
      return static_cast<real>(pi * deg / 180);
    }

    constexpr real operator""_degrees(unsigned long long int deg)
    {
      return static_cast<real>(pi * deg / 180);
    }
  }

  class angle
  {
  public:
    angle() = default;
    ~angle() = default;
    angle(const angle&) = default;
    angle& operator=(const angle&) = default;
    angle(angle&&) = default;
    angle& operator=(angle&&) = default;
  
    constexpr explicit angle(real radians) : m_radians{radians} {}

    real rad() const { return m_radians; }

    real deg() const { return m_radians * 180 / pi; }

  private:
    real m_radians = 0;
  };

  inline std::ostream& operator<<(std::ostream& os, const angle& a)
  {
    // os << (a.rad() / sp3::pi) << "pi radians";
    os << std::format("{:.2f} pi radians", a.rad() / sp3::pi);
    return os;
  }
}