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
    matrix_nm()
    {
      std::array<real, NCOLS> zeros;
      zeros.fill(real{0});

      for ( int i = 0; i < NROWS; ++i)
        m_data[i] = zeros;
    }

    static matrix_nm identity()
    {
      std::array<std::array<real, NCOLS>, NROWS> data;

      for ( int i = 0; i < NROWS; ++i)
        for ( int j = 0; j < NCOLS; ++j)
          data[i][j] = (i == j) ? 1 : 0;
      
      return matrix_nm{std::move(data)};
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

    real& operator()(size_t i, size_t j)
    {
      return m_data[i][j];
    }

    vector row(size_t i) const 
    {
      assert(i < NROWS);
      return {m_data[i][0], m_data[i][1], m_data[i][2]};
    }

    bool operator==(const matrix_nm& other) const
    {
      return m_data == other.m_data;
    }

    bool operator!=(const matrix_nm& other) const
    {
      return !(*this == other);
    }

  private:
    size_t m_nrows = NROWS;
    size_t m_ncols = NCOLS;
    std::array<std::array<real, NCOLS>, NROWS> m_data = {};
  };

  using matrix = matrix_nm<3, 3>;


  template <int NROWS, int NCOLS>
  matrix_nm<NROWS, NCOLS> operator+(const matrix_nm<NROWS, NCOLS>& A, const matrix_nm<NROWS, NCOLS>& B)
  {
    std::array<std::array<real, NCOLS>, NROWS> C;
    for( auto i = 0; i < NROWS; ++i)
      for( auto j = 0; j < NCOLS; ++j)
        C[i][j] = A(i, j) + B(i, j);
    
    return matrix_nm<NROWS, NCOLS>{std::move(C)};
  }

  template <int NROWS, int NCOLS>
  matrix_nm<NROWS, NCOLS> operator-(const matrix_nm<NROWS, NCOLS>& A, const matrix_nm<NROWS, NCOLS>& B)
  {
    std::array<std::array<real, NCOLS>, NROWS> C;
    for( auto i = 0; i < NROWS; ++i)
      for( auto j = 0; j < NCOLS; ++j)
        C[i][j] = A(i, j) - B(i, j);
    
    return matrix_nm<NROWS, NCOLS>{std::move(C)};
  }

  template <int NROWS, int NCOLS>
  matrix_nm<NROWS, NCOLS> operator*(const matrix_nm<NROWS, NCOLS>& A, const matrix_nm<NROWS, NCOLS>& B)
  {
    std::array<std::array<real, NCOLS>, NROWS> C;
    for( auto i = 0; i < NROWS; ++i)
      for( auto j = 0; j < NCOLS; ++j)
      {
        auto c_ij = sp3::real{0};
        for (auto k = 0; k < NCOLS; ++k)
          c_ij += A(i, k) * B(k, j);
        C[i][j] = c_ij;
      }
    
    return matrix_nm<NROWS, NCOLS>{std::move(C)};
  }

  template <int NROWS, int NCOLS>
  matrix_nm<NROWS, NCOLS> operator*(real s, const matrix_nm<NROWS, NCOLS>& A)
  {
    std::array<std::array<real, NCOLS>, NROWS> sA;
    for( auto i = 0; i < NROWS; ++i)
      for( auto j = 0; j < NCOLS; ++j)
        sA[i][j] = s * A(i, j);
    
    return matrix_nm<NROWS, NCOLS>{std::move(sA)};
  }

  template <int NROWS, int NCOLS>
  matrix_nm<NROWS, NCOLS> operator/(const matrix_nm<NROWS, NCOLS>& A, real s)
  {
    std::array<std::array<real, NCOLS>, NROWS> As;
    for( auto i = 0; i < NROWS; ++i)
      for( auto j = 0; j < NCOLS; ++j)
        As[i][j] = A(i, j) / s;
    
    return matrix_nm<NROWS, NCOLS>{std::move(As)};
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