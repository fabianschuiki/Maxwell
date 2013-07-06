add_executable(ast-gen main.cpp def.cpp)
target_link_libraries(ast-gen ${Boost_LIBRARIES})

# Generate the AST
add_custom_command(
	TARGET ast-gen POST_BUILD
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/ast-gen ${PROJECT_SOURCE_DIR}/source/ast/nodes
	COMMENT "Generating AST"
)