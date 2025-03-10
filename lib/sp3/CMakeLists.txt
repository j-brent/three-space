add_library(three-space STATIC
  vector.h
  point.h
  matrix.h
  matrix.cpp
  rotation.h
  pose.h
  transform.h
)

target_include_directories(three-space PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)