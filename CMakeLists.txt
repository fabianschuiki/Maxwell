# Copyright (c) 2014 Fabian Schuiki
# Root project configuration for the Maxwell programming language.
cmake_minimum_required(VERSION 2.8)
project(Maxwell)

if (CMAKE_BUILD_TYPE)
	message("## ${CMAKE_BUILD_TYPE} build")
endif()

# Project version.
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)


# Enable C++11 support and enable all warnings.
if (UNIX)
	add_definitions(-Wall)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()


# Add the build type "gcov" that produces a debug build with gcov output
# enabled. Useful for coverage analysis.
set(GCC_COVERAGE_COMPILER_FLAGS "-O0 -fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINKERR_FLAGS "-lgcov")

set(CMAKE_C_FLAGS_GCOV
	"${CMAKE_C_FLAGS_DEBUG} ${GCC_COVERAGE_COMPILER_FLAGS}"
	CACHE STRING "Flags used by the compiler during gcov-enabled debug builds")
set(CMAKE_CXX_FLAGS_GCOV
	"${CMAKE_CXX_FLAGS_DEBUG} ${GCC_COVERAGE_COMPILER_FLAGS}"
	CACHE STRING "Flags used by the compiler during gcov-enabled debug builds")
set(CMAKE_C_LINKER_FLAGS_GCOV
	"${CMAKE_C_LINKER_FLAGS_DEBUG} ${GCC_COVERAGE_LINKER_FLAGS}"
	CACHE STRING "Flags used by the linker during gcov-enabled debug builds")
set(CMAKE_CXX_LINKER_FLAGS_GCOV
	"${CMAKE_CXX_LINKER_FLAGS_DEBUG} ${GCC_COVERAGE_LINKER_FLAGS}"
	CACHE STRING "Flags used by the linker during gcov-enabled debug builds")

mark_as_advanced(
	CMAKE_C_FLAGS_GCOV
	CMAKE_CXX_FLAGS_GCOV
	CMAKE_C_LINKER_FLAGS_GCOV
	CMAKE_CXX_LINKER_FLAGS_GCOV)


# Add a target to clear all gcov output files.
add_custom_target(clean-gcov
	find . -name '*.gcov' -or -name '*.gcda' | xargs rm
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})


find_package(Boost COMPONENTS REQUIRED filesystem system unit_test_framework)
add_definitions(-DBOOST_TEST_DYN_LINK)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(.)

enable_testing()
add_subdirectory(maxwell)
add_subdirectory(tests)
add_subdirectory(test)

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
