#pragma once

#include "detail/homogeneous.h"
#include "point.h"
#include "rotation.h"
#include "vector.h"

namespace sp3
{
  class transform
  {
  public:
    transform() = default;

    transform(vector t, rotation r, real scale = 1)
    : m_matrix{detail::homogeneous_matrix::make(std::move(t), std::move(r), scale)}
    {}

    point operator()(const point& p) const
    {
      return this->m_matrix * p;
    }

    transform operator*(const transform& rhs) const
    {
      return {this->m_matrix * rhs.m_matrix};
    }
    
  private:
    transform(detail::homogeneous_matrix m) : m_matrix{m} {}

    detail::homogeneous_matrix m_matrix;
  };
}