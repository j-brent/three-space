#pragma once

#include "real.h"
#include "vector.h"

#include <array>
#include <cassert>

namespace sp3
{
  template <int NROWS, int NCOLS>
  class matrix_nm
  {
  public:
    using data = std::array<std::array<real, NCOLS>, NROWS>;

    matrix_nm()
    {
      std::array<real, NCOLS> zeros;
      zeros.fill(real{0});

      for ( int i = 0; i < NROWS; ++i)
        m_data[i] = zeros;
    }

    explicit matrix_nm(const std::array<std::array<real, NCOLS>, NROWS>& data)
    : m_data{std::move(data)}
    {}
    ~matrix_nm() = default;

    matrix_nm(const matrix_nm&) = default;
    matrix_nm& operator=(const matrix_nm&) = default;
    
    matrix_nm(matrix_nm&&) = default;
    matrix_nm& operator=(matrix_nm&&) = default;
    
    real operator()(size_t i, size_t j) const
    {
      return m_data[i][j];
    }

    vector row(size_t i) const 
    {
      assert(i < NROWS);
      return {m_data[i][0], m_data[i][1], m_data[i][2]};
    }

  private:
    size_t m_nrows = NROWS;
    size_t m_ncols = NCOLS;
    std::array<std::array<real, NCOLS>, NROWS> m_data = {};
  };

  using matrix = matrix_nm<3, 3>;


  template <int NROWS, int NCOLS>
  matrix_nm<NCOLS, NROWS> operator+(const matrix_nm<NROWS, NCOLS>& A, const matrix_nm<NROWS, NCOLS>& B)
  {
    std::array<std::array<real, NROWS>, NCOLS> C;
    for( auto i = 0; i < NCOLS; ++i)
      for( auto j = 0; j < NROWS; ++j)
        C[i][j] = A(i, j) + B(i, j);
    
    return matrix_nm<NCOLS, NROWS>{std::move(C)};
  }

  template <int NROWS, int NCOLS>
  matrix_nm<NCOLS, NROWS> operator-(const matrix_nm<NROWS, NCOLS>& A, const matrix_nm<NROWS, NCOLS>& B)
  {
    std::array<std::array<real, NROWS>, NCOLS> C;
    for( auto i = 0; i < NCOLS; ++i)
      for( auto j = 0; j < NROWS; ++j)
        C[i][j] = A(i, j) - B(i, j);
    
    return matrix_nm<NCOLS, NROWS>{std::move(C)};
  }

  template <int NROWS, int NCOLS>
  matrix_nm<NCOLS, NROWS> operator*(real s, const matrix_nm<NROWS, NCOLS>& A)
  {
    std::array<std::array<real, NROWS>, NCOLS> sA;
    for( auto i = 0; i < NCOLS; ++i)
      for( auto j = 0; j < NROWS; ++j)
        sA[i][j] = s * A(i, j);
    
    return matrix_nm<NCOLS, NROWS>{std::move(sA)};
  }

  template <int NROWS, int NCOLS>
  matrix_nm<NCOLS, NROWS> operator/(const matrix_nm<NROWS, NCOLS>& A, real s)
  {
    std::array<std::array<real, NROWS>, NCOLS> As;
    for( auto i = 0; i < NCOLS; ++i)
      for( auto j = 0; j < NROWS; ++j)
        As[i][j] = A(i, j) / s;
    
    return matrix_nm<NCOLS, NROWS>{std::move(As)};
  }

  template <int NROWS, int NCOLS>
  matrix_nm<NCOLS, NROWS> transposed(const matrix_nm<NROWS, NCOLS>& A)
  {
    std::array<std::array<real, NROWS>, NCOLS> transposed;
    for( auto i = 0; i < NCOLS; ++i)
      for( auto j = 0; j < NROWS; ++j)
        transposed[i][j] = A(j, i);
    
    return matrix_nm<NCOLS, NROWS>{std::move(transposed)};
  }
}