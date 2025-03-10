find_package(Catch2 3 REQUIRED)

add_executable(sp3-tests
  matrix-tests.cpp
  matrix-vector-functions-tests.cpp
  point-tests.cpp
  pose-tests.cpp
  rotation-tests.cpp
  transform-tests.cpp
  vector-point-functions-tests.cpp
  vector-tests.cpp
)
target_link_libraries(sp3-tests 
  PUBLIC three-space
  PRIVATE Catch2::Catch2WithMain
)

include(CTest)
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
catch_discover_tests(sp3-tests)
