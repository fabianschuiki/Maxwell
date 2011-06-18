project(maxwell)
cmake_minimum_required(VERSION 2.6)

# Generate the AST parser if required.
add_custom_command(
	OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
	DEPENDS parser.yy
	COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} &&
		bison --defines=parser.h -o parser.cpp parser.yy
)

# Generate the lexical analyzer if required.
add_custom_command(
	OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/scanner.cpp
	DEPENDS scanner.ll
	COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} &&
		lex -o scanner.cpp scanner.ll
)


add_executable(
	maxwell
	
	main.cpp
	scanner.cpp
	parser.cpp
	driver.cpp
)

target_link_libraries(
	maxwell
)
