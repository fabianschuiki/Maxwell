file(GLOB_RECURSE MAXWELL_AST_SOURCES
	 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	 nodes/*.cpp)

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
target_link_libraries(ast base64 ${Boost_LIBRARIES})
