#pragma once

#include "angle.h"
#include "matrix.h"
#include "vector.h"

#include <cmath>

namespace sp3
{
  class rotation
  {
  public:
    rotation() = default;

    rotation(const vector& axis, angle theta)
    {
      //https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
      const vector u = axis / norm(axis);
      const real uxx = u.x * u.x;
      const real uxy = u.x * u.y;
      const real uxz = u.x * u.z;
      const real uyy = u.y * u.y;
      const real uyz = u.y * u.z;
      const real uzz = u.z * u.z;

      const real s = std::sin(theta.rad());
      const real c = std::cos(theta.rad());

      m_matrix = matrix{{{
        {{uxx * (1-c) +     c, uxy * (1-c) - u.z*s, uxz * (1-c) + u.y*s}},
        {{uxy * (1-c) + u.z*s, uyy * (1-c) +     c, uyz * (1-c) - u.x*s}},
        {{uxz * (1-c) - u.y*s, uyz * (1-c) + u.x*s, uzz * (1-c) +     c}}
      }}};
    }

    matrix& matrix() const { return m_matrix; }

    rotation operator*(const rotation& rhs) const
    {
      return {this->m_matrix * rhs.m_matrix};
    }

    rotation inverse() const
    {
      return {transposed(m_matrix)};
    }

  private:
    rotation(matrix m) : m_matrix{std::move(m)} {}

    matrix m_matrix = matrix::identity();
  };
}