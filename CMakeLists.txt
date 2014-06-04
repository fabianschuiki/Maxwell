cmake_minimum_required(VERSION 2.8)
project(Maxwell)

find_package(Boost COMPONENTS unit_test_framework)
find_package(Boost COMPONENTS REQUIRED filesystem system)
add_definitions(-DBOOST_TEST_DYN_LINK)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(source)

enable_testing()
add_subdirectory(source)
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
