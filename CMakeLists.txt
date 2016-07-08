cmake_minimum_required(VERSION 3.5)

project(openjcvm CXX)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)
