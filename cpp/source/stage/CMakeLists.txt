add_library(stage
	BuildGraph.cpp
	BindIdentifiers.cpp
	BindNamedTypes.cpp
	EvalTypeExprs.cpp
	ConfigureCalls.cpp
	CalcPossibleTypes.cpp
)

add_dependencies(stage stage-gen)
add_dependencies(stage ast)