add_library(ast
	Node.cpp
	Repository.cpp
	SourceRepository.cpp
	NodeRepository.cpp
	Serializer.cpp
	BuiltinRepository.cpp
	SymbolRepository.cpp
)

add_dependencies(ast ast-gen)