#pragma once

#include "matrix.h"
#include "vector.h"

namespace sp3
{
  vector operator*(const matrix& M, const vector& v)
  {
    return {dot(M.row(0), v), dot(M.row(1), v), dot(M.row(2), v)};
  }
}