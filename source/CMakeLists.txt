project(maxwell)
cmake_minimum_required(VERSION 2.6)


# Collect the source files.
set(sources
    main.cpp
)


# Specify the executable.
add_executable(maxwell ${sources})
