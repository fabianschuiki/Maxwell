# Copyright (c) 2013-2015 Fabian Schuiki
add_custom_command(
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Parser.yy
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp ${CMAKE_CURRENT_BINARY_DIR}/Parser.hpp ${CMAKE_CURRENT_BINARY_DIR}/stack.hh ${CMAKE_CURRENT_BINARY_DIR}/position.hh ${CMAKE_CURRENT_BINARY_DIR}/location.hh ${CMAKE_CURRENT_BINARY_DIR}/Parser.output
	COMMAND bison --report=all -d -o ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Parser.yy
	COMMENT "Generating Bison parser")

add_custom_command(
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.ll
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Scanner.cpp
	COMMAND lex -o ${CMAKE_CURRENT_BINARY_DIR}/Scanner.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.ll
	COMMENT "Generating Flex scanner")

include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_library(driver ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp ${CMAKE_CURRENT_BINARY_DIR}/Scanner.cpp Driver.cpp)
target_link_libraries(driver ast)
add_dependencies(driver ast-gen)
