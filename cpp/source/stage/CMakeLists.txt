add_library(stage
	Stage.cpp
	BuildGraph.cpp
	BindIdentifiers.cpp
	BindNamedTypes.cpp
	EvalTypeExprs.cpp
	InitRootTypes.cpp
	ConfigureCalls.cpp
	FindCallCandidates.cpp
	CalcPossibleTypes.cpp
)

add_dependencies(stage stage-gen)
add_dependencies(stage ast)