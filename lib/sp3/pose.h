#pragma once

#include "rotation.h"
#include "point.h"

namespace sp3
{
  struct pose
  {
    point position = {};
    rotation orientation = {};
  };
}
