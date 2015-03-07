/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

void CodeGenerator::generateUnionMappedType(const ast::UnionMappedType::Ptr& type, ExprCode& out, Context& ctx)
{
	generateMappedType(type->getIn(), out, ctx);

	// Make a copy of the current ExprCode, which we will wrap in a mapping
	// further down.
	ExprCode ec = out;

	// Generate the code for the desired output type.
	TypeCode tc;
	generateType(type->getOut(), tc);
	out += tc;

	// Wrap the existing code inside an inline constructor for the UnionType's
	// struct.
	out.isRef = false;
	out.code = "(" + tc.code + "){ /*dummy*/ .a = 0, .v0 = " + precedenceWrap(ec, kAssignmentPrec) + "}";
	out.precedence = kPostfixPrec;
}
