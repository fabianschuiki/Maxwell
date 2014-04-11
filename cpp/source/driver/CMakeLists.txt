add_custom_command(
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Parser.yy
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp ${CMAKE_CURRENT_BINARY_DIR}/Parser.hpp ${CMAKE_CURRENT_BINARY_DIR}/stack.hh ${CMAKE_CURRENT_BINARY_DIR}/position.hh ${CMAKE_CURRENT_BINARY_DIR}/location.hh ${CMAKE_CURRENT_BINARY_DIR}/Parser.output
	COMMAND bison --report=all -d -o ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Parser.yy
	COMMAND gramdiag ${CMAKE_CURRENT_BINARY_DIR}/Parser.output > ${CMAKE_CURRENT_BINARY_DIR}/Parser.report
	COMMENT "Generating Bison parser")

add_custom_command(
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.ll
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Scanner.cpp
	COMMAND lex -o ${CMAKE_CURRENT_BINARY_DIR}/Scanner.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.ll
	COMMENT "Generating Flex scanner")

add_executable(gramdiag gramdiag.c)
# add_custom_command(
# 	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Parser.output
# 	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Parser.report
# 	COMMAND gramdiag ${CMAKE_CURRENT_BINARY_DIR}/Parser.output > ${CMAKE_CURRENT_BINARY_DIR}/Parser.report
# 	COMMENT "Analyzing Bison output for grammar issues")
# add_custom_target(driver-diagnosis ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Parser.report)

include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_library(driver ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp ${CMAKE_CURRENT_BINARY_DIR}/Scanner.cpp Driver.cpp)
add_dependencies(driver ast-gen)

# Add the test executable used to debug the parser.
add_executable(test main.cpp)
target_link_libraries(test driver ast ${Boost_LIBRARIES})