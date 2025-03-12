#pragma once

#include "sp3/matrix.h"
#include "sp3/matrix_vector_functions.h"
#include "sp3/point.h"
#include "sp3/rotation.h"
#include "sp3/vector.h"
#include "sp3/vector_point_functions.h"

namespace sp3
{
  namespace detail
  {
    class homogeneous_matrix
    {
    public:
      homogeneous_matrix() = default;

      static homogeneous_matrix make(real scale)
      {
        homogeneous_matrix S;
        S.m_mat33(0, 0) = scale;
        S.m_mat33(1, 1) = scale;
        S.m_mat33(2, 2) = scale;
        return S;
      }

      static homogeneous_matrix make(rotation R)
      {
        homogeneous_matrix H;
        H.m_mat33 = R.matrix();
        return H;
      }

      static homogeneous_matrix make(const rotation& R, real scale)
      {
        homogeneous_matrix H;
        H.m_mat33 = scale * R.matrix();
        return H;
      }

      static homogeneous_matrix make(const vector& t, const rotation& R, real scale)
      {
        homogeneous_matrix H = make(R, scale);
        H.m_t = t;
        return H;
      }

      point operator*(const point& p) const
      {
        return as_point(m_mat33 * vector{p.x, p.y, p.z} + m_t);
      }

      homogeneous_matrix operator*(const homogeneous_matrix& rhs) const
      {
        // [Rl tl] * [Rr tr] = [Rl*Rr  Rl*tr + tl]
        // [ 0  1]   [ 0  1]   [    0           1]

        const auto& Rl = this->m_mat33;
        const auto& tl = this->m_t;
        const auto& Rr = rhs.m_mat33;
        const auto& tr = rhs.m_t; 

        return {Rl*Rr, Rl*tr + tl};
      }

    private:
      homogeneous_matrix(matrix m, vector t) : m_mat33{std::move(m)}, m_t{std::move(t)} {}

      matrix m_mat33 = matrix::identity();
      vector m_t = {};
    };
  }
}