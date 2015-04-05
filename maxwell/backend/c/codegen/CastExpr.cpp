/* Copyright (c) 2015 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_EXPR(CastExpr) {

	// Generate the code for the variable type.
	TypeCode tc;
	generateType(node->getActualType(), tc);
	out += tc;

	// Generate the code for the expression.
	ExprCode ec;
	const NodePtr& initial = node->getExpr();
	generateExpr(initial, ec, ctx);
	out += ec;

	// Add the statement to the context and setup the output.
	out.code = "(" + tc.code + ")" + precedenceWrap(ec, kPrefixPrec);
	out.isRef = true;
	out.precedence = kPrefixPrec;
}
