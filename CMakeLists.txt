# Copyright (c) 2014 Fabian Schuiki
# Project configuration file for the Maxwell compiler

cmake_minimum_required(VERSION 2.8)
project(Maxwell)

# Add an option to enable gcov output.
set(GCC_COVERAGE_COMPILE_FLAGS "-O0 -fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINKER_FLAGS  "-lgcov")

option(ENABLE_GCOV "Enable gcov output" off)
if (${ENABLE_GCOV})
	set(CMAKE_BUILD_TYPE Debug)
	list(APPEND CMAKE_C_FLAGS   ${GCC_COVERAGE_COMPILE_FLAGS})
	list(APPEND CMAKE_CXX_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})
	list(APPEND CMAKE_C_LINKER_FLAGS   ${GCC_COVERAGE_LINKER_FLAGS})
	list(APPEND CMAKE_CXX_LINKER_FLAGS ${GCC_COVERAGE_LINKER_FLAGS})
	message("## gcov output enabled")
endif()
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message("## debug build")
endif()

find_package(Boost COMPONENTS unit_test_framework)
find_package(Boost COMPONENTS REQUIRED filesystem system)
add_definitions(-DBOOST_TEST_DYN_LINK)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(.)

enable_testing()
add_subdirectory(maxwell)
add_subdirectory(tests)

# If Doxygen is available, add a target that compiles the documentation.
find_package(Doxygen)
if (DOXYGEN_FOUND)
	configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile @ONLY)
	add_custom_target(
		doc
		${DOXYGEN_EXECUTABLE} Doxyfile 1> doxygen.log 2> doxygen.err
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc
		COMMENT "Generating documentation with Doxygen" VERBATIM)
endif()
