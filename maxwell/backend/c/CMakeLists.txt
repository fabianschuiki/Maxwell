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
	codegen/NativeType.cpp
	codegen/NativeTypeDef.cpp
	codegen/NilType.cpp
	codegen/NumberConstExpr.cpp
	codegen/StringConstExpr.cpp
	codegen/TupleExpr.cpp
	codegen/TupleType.cpp
	codegen/TypeDef.cpp
	codegen/UnionMappedType.cpp
	codegen/UnionType.cpp
	codegen/VarDefExpr.cpp
	CodeGenerator.cpp
)
