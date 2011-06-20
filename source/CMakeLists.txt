project(maxwell)
cmake_minimum_required(VERSION 2.6)

# Generate the AST parser if required.
add_custom_command(
	OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/parser/autogen/parser.cpp
	DEPENDS parser/parser.yy
	COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/parser/ && mkdir -p autogen && cd autogen &&
		bison --defines=parser.h -o parser.cpp ../parser.yy
)

# Generate the lexical analyzer if required.
add_custom_command(
	OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/scanner/autogen/scanner.cpp
	DEPENDS scanner/scanner.ll
	COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/scanner/ && mkdir -p autogen && cd autogen &&
		lex -o scanner.cpp ../scanner.ll
)


add_executable(
	maxwell
	
	main.cpp
	scanner/autogen/scanner.cpp
	parser/autogen/parser.cpp
	driver.cpp
	node.cpp
)

target_link_libraries(
	maxwell
)
