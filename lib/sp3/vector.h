#pragma once

#include "real.h"

#include <cmath>
#include <ostream>

namespace sp3
{
  struct vector
  {
    real x = 0;
    real y = 0;
    real z = 0;
  };
  
  inline std::ostream& operator<<(std::ostream& os, const vector& v)
  {
    os << "<"<< v.x << ", " << v.y << ", " << v.z << ">";
    return os;
  }


  inline bool operator==(const vector& lhs, const vector& rhs)
  {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z); 
  }

  inline vector operator-(const vector& v)
  {
    return {-v.x, -v.y, -v.z};
  }

  inline vector operator+(const vector& v, const vector& u)
  {
    return {v.x + u.x, v.y + u.y, v.z + u.z};
  }

  inline vector operator-(const vector& v, const vector& u)
  {
    return {v.x - u.x, v.y - u.y, v.z - u.z};
  }

  inline real dot(const vector& v, const vector& u)
  {
    return {v.x * u.x + v.y * u.y + v.z * u.z};
  }

  inline real norm(const vector& v)
  {
    return std::hypot(v.x, v.y, v.z);
  }

  inline vector operator*(real s, const vector& v)
  {
    return {s * v.x, s * v.y, s * v.z};
  }

  inline vector operator*(const vector& v, real s)
  {
    return s*v;
  }
  
  inline vector operator/(const vector& v, real s)
  {
    return {v.x / s, v.y / s, v.z / s};
  }

  inline vector cross(const vector& a, const vector& b)
  {
    const auto [a1, a2, a3] = a;
    const auto [b1, b2, b3] = b;
    return{a2*b3 - a3*b2, a3*b1 - a1*b3, a1*b2 - a2*b1};
  }
}