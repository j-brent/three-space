#pragma once

#include "real.h"

#include <compare>
#include <ostream>

namespace sp3
{
  struct point
  {
    real x = 0;
    real y = 0;
    real z = 0;

    auto operator<=>(const point&) const = default;
  };

  inline std::ostream& operator<<(std::ostream& os, const point& p)
  {
    os << "("<< p.x << ", " << p.y << ", " << p.z << ")";
    return os;
  }

}