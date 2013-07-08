add_executable(ast-gen ast-gen.cpp ast-def.cpp)
add_executable(stage-gen stage-gen.cpp)
target_link_libraries(ast-gen ${Boost_LIBRARIES})
target_link_libraries(stage-gen ${Boost_LIBRARIES})

# Generate the AST
add_custom_command(
	TARGET ast-gen POST_BUILD
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/ast-gen ${PROJECT_SOURCE_DIR}/source/ast/nodes
	COMMENT "Generating AST"
)

# Generate the stages
add_custom_command(
	TARGET stage-gen POST_BUILD
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/stage-gen ${PROJECT_SOURCE_DIR}/source/stage
	COMMENT "Generating stages"
)