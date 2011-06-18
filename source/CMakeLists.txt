project(maxwell)
cmake_minimum_required(VERSION 2.6)

# Generate the lexical analyzer if required.
add_custom_command(
	OUTPUT tokens.cpp
	DEPENDS tokens.l
	COMMAND lex -o tokens.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tokens.l
)


add_executable(
	maxwell
	
	main.cpp
	tokens.cpp
)

target_link_libraries(
	maxwell
)
