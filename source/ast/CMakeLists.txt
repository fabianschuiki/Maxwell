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
)

add_dependencies(ast ast-gen)
target_link_libraries(ast base64 ${Boost_LIBRARIES})
