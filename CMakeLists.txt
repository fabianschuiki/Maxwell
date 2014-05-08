cmake_minimum_required(VERSION 2.8)
project(Maxwell)

if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions("-DBUILD_DEBUG")
endif()

find_package(Boost COMPONENTS unit_test_framework)
find_package(Boost COMPONENTS REQUIRED filesystem system)
add_definitions(-DBOOST_TEST_DYN_LINK)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(source)

enable_testing()
add_subdirectory(source)
