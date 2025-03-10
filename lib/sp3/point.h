#pragma once

#include "real.h"

#include <compare>

namespace sp3
{
  struct point
  {
    real x = 0;
    real y = 0;
    real z = 0;

    auto operator<=>(const point&) const = default;
  };
}