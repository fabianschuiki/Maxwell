cmake_minimum_required(VERSION 2.8)
project(Maxwell)

# Default to debug build.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions("-DBUILD_DEBUG")
endif()

find_package(Boost REQUIRED COMPONENTS)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(source)

add_subdirectory(source/driver)