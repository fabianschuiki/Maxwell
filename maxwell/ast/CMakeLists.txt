# Copyright (c) 2013-2015 Fabian Schuiki
# Collects the automatically generated AST source files and compiles them into a
# library.

file(
	GLOB_RECURSE MAXWELL_AST_SOURCES
	RELATIVE ${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_BINARY_DIR}/maxwell/ast/nodes/*.cpp
)

add_library(ast
	Node.cpp
	NodeId.cpp
	Repository.cpp
	SourceRepository.cpp
	NodeRepository.cpp
	Serializer.cpp
	BuiltinRepository.cpp
	SymbolRepository.cpp
	DependencyRepository.cpp
	NodeFlagsRepository.cpp
	${MAXWELL_AST_SOURCES}
)

add_dependencies(ast ast-gen)
target_link_libraries(ast obj-common ${Boost_LIBRARIES})
