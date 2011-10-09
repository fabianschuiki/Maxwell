project(maxwell)
cmake_minimum_required(VERSION 2.6)


# Collect the source files.
file(GLOB_RECURSE sources RELATIVE ${CMAKE_SOURCE_DIR} *.cpp)


# Specify the executable.
add_executable(maxwell ${sources})
