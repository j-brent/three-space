set(THREE_SPACE_HEADER_FILES
  vector.h
  point.h
  matrix.h
  rotation.h
  pose.h
  transform.h
  angle.h
  detail/homogeneous.h
)

set(THREE_SPACE_SOURCE_FILES
  matrix.cpp
)

add_library(three-space STATIC
  ${THREE_SPACE_HEADER_FILES}
  ${THREE_SPACE_SOURCE_FILES}
)

add_library(three-space::three-space ALIAS three-space)

target_include_directories(three-space
  PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
