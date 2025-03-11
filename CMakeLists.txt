cmake_minimum_required(VERSION 3.23)

project(three-space
  VERSION 0.1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/CPM.cmake)

add_subdirectory(lib)
CPMAddPackage("gh:catchorg/Catch2@3.8.0")
add_subdirectory(tests)
