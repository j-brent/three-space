#pragma once

#include "point.h"
#include "vector.h"

namespace sp3
{
  inline point operator+(const point& p, const vector& v)
  {
    return {p.x + v.x, p.y + v.y, p.z + v.z};
  }

  inline vector operator-(const point& b, const point& a)
  {
    return {b.x - a.x, b.y - a.y, b.z - a.z};
  }

  inline point as_point(vector&& v)
  {
    return {std::move(v.x), std::move(v.y), std::move(v.z)};
  }
}