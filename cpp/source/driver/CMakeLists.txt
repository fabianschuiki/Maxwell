add_custom_command(
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Parser.yy
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Parser.hpp ${CMAKE_CURRENT_SOURCE_DIR}/stack.hh ${CMAKE_CURRENT_SOURCE_DIR}/position.hh ${CMAKE_CURRENT_SOURCE_DIR}/location.hh
	COMMAND bison -d -o ${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Parser.yy
	COMMENT "Generating Bison parser")

add_custom_command(
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.ll
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.cpp
	COMMAND lex -o ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.ll
	COMMENT "Generating Flex scanner")

add_library(driver ${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.cpp Driver.cpp)
add_dependencies(driver ast-gen)

# Add the test executable used to debug the parser.
add_executable(test main.cpp)
target_link_libraries(test driver ast)