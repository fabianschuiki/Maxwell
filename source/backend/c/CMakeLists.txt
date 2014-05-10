add_library(backendc
	database.cpp
	code.cpp

	# Packager
	Packager.cpp
	Packager-collect.cpp
	Packager-sort.cpp
	Packager-group.cpp
	Packager-compile.cpp
	
	# Code Generator
	CodeGenerator.cpp
	codegen/AssignmentExpr.cpp
	codegen/BlockExpr.cpp
	codegen/CallIntf.cpp
	codegen/DefinedType.cpp
	codegen/ForExpr.cpp
	codegen/FuncDef.cpp
	codegen/FuncExpr.cpp
	codegen/FuncType.cpp
	codegen/IdentifierExpr.cpp
	codegen/IfCaseExpr.cpp
	codegen/IfExpr.cpp
	codegen/IndexOpExpr.cpp
	codegen/NumberConstExpr.cpp
	codegen/TupleExpr.cpp
	codegen/TupleType.cpp
	codegen/TypeDef.cpp
	codegen/UnionType.cpp
	codegen/VarDefExpr.cpp
)
