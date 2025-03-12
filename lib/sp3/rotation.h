#pragma once

#include "angle.h"
#include "matrix.h"
#include "matrix_vector_functions.h"
#include "point.h"
#include "vector.h"
#include "vector_point_functions.h"

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

      m_matrix = sp3::matrix{{{
        {{uxx * (1-c) +     c, uxy * (1-c) - u.z*s, uxz * (1-c) + u.y*s}},
        {{uxy * (1-c) + u.z*s, uyy * (1-c) +     c, uyz * (1-c) - u.x*s}},
        {{uxz * (1-c) - u.y*s, uyz * (1-c) + u.x*s, uzz * (1-c) +     c}}
      }}};
    }

    point operator()(const point& p) const
    {
      return as_point(m_matrix * vector{p.x, p.y, p.z});
    }

    const sp3::matrix& matrix() const { return m_matrix; }

    rotation operator*(const rotation& rhs) const
    {
      return {this->m_matrix * rhs.m_matrix};
    }

    rotation inverse() const
    {
      return {transposed(m_matrix)};
    }

  private:
    rotation(sp3::matrix m) : m_matrix{std::move(m)} {}

    sp3::matrix m_matrix = matrix::identity();
  };
}