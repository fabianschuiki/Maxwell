/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "detail.hpp"

DEF_EXPR(VarDefExpr)
{
	// Pick a name.
	std::string name = ctx.makeSymbol(makeFriendly(node->getName()));
	ctx.vars[node->getId()] = name;

	// Generate the code for the variable type.
	TypeCode tc;
	generateType(node->getActualType(), tc);
	out.deps.insert(tc.deps.begin(), tc.deps.end());
	std::string decl = tc.code + " " + name;

	// Generate the code for the initial value.
	ExprCode ec;
	const NodePtr& initial = node->getInitialExpr(false);
	if (initial) {
		generateExpr(initial, ec, ctx);
		out.deps.insert(ec.deps.begin(), ec.deps.end());
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
	out.deps.insert(tc.deps.begin(), tc.deps.end());
	std::string decl = tc.code + " " + name;

	// Generate the code for the initial value.
	ExprCode ec;
	generateExpr(node->getInitialExpr(), ec, ctx);
	out.deps.insert(ec.deps.begin(), ec.deps.end());
	decl += " = " + precedenceWrap(ec, kAssignmentPrec);
	decl += ";";

	// Add the statement to the context and setup the output.
	ctx.stmts.push_back(decl);
	out.code = name;
	out.isRef = true;
	out.precedence = kPrimaryPrec;
}
