/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_EXPR(VarDefExpr)
{
	// Pick a name.
	std::string name = ctx.makeSymbol(makeFriendly(node->getName()));
	ctx.vars[node->getId()] = name;

	// Generate the code for the variable type.
	TypeCode tc;
	generateType(node->getActualType(), tc);
	out += tc;
	std::string decl = tc.code + " " + name;

	// Generate the code for the initial value.
	ExprCode ec;
	const NodePtr& initial = node->getInitialExpr(false);
	if (initial) {
		generateExpr(initial, ec, ctx);
		out += ec;
		decl += " = " + precedenceWrap(ec, kAssignmentPrec);
	}
	decl += ";";

	// Add the statement to the context and setup the output.
	ctx.stmts.push_back(decl);
	out.code = name;
	out.isRef = true;
	out.precedence = kPrimaryPrec;
}

DEF_EXPR(TypelessVarDefExpr)
{
	// Pick a name.
	std::string name = ctx.makeSymbol(makeFriendly(node->getName()));
	ctx.vars[node->getId()] = name;

	// Generate the code for the variable type.
	TypeCode tc;
	generateType(node->getActualType(), tc);
	out += tc;
	std::string decl = tc.code + " " + name;

	// Generate the code for the initial value.
	ExprCode ec;
	generateExpr(node->getInitialExpr(), ec, ctx);
	out += ec;
	decl += " = " + precedenceWrap(ec, kAssignmentPrec);
	decl += ";";

	// Add the statement to the context and setup the output.
	ctx.stmts.push_back(decl);
	out.code = name;
	out.isRef = true;
	out.precedence = kPrimaryPrec;
}
