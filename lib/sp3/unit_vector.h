#pragma once

#include "sp3/vector.h"

namespace sp3
{
  class unit_vector
  {
  public:
    unit_vector() = default;
    ~unit_vector() = default;

    unit_vector(const unit_vector&) = default;
    unit_vector& operator=(const unit_vector&) = default;

    unit_vector(unit_vector&&) = default;
    unit_vector& operator=(unit_vector&&) = default;


    unit_vector(vector v) : v_{normalize(v)} {}
    unit_vector(float x, float y, float z) : unit_vector{vector{x, y, z}} {}

    operator vector() { return v_; }
    operator const vector() const { return v_; }

    float& x = v_.x;
    float& y = v_.y;
    float& z = v_.z;

  private:
      vector v_ = {0, 0, 0};
  };

  inline unit_vector cross(const unit_vector& a, const unit_vector& b)
  {
    return {cross(static_cast<vector>(a), static_cast<vector>(b))};
  }
}
