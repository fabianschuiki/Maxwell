/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "detail.hpp"

DEF_EXPR(BlockExpr)
{
	// Decide what result variable to use, and whether to use any at all. If
	// the context has a result variable configured already, we reuse that.
	// This allows an IfExpr or ForExpr to store the result of each of their
	// branches in one common variable.
	std::string resultVar/* = ctx.resultVar*/;

	if (resultVar.empty()) {
		TypeCode tc;
		generateType(node->getActualType(), tc);
		out.deps.insert(tc.deps.begin(), tc.deps.end());

		resultVar = ctx.makeTempSymbol();
		ctx.stmts.push_back(tc.code + " " + resultVar + ";");
	}
	out.code = resultVar;
	out.isRef = true;
	out.precedence = kPrimaryPrec;


	// Generate the code for each of the block's expressions. The last
	// expression is stored in the result variable.
	const NodeVector& exprs = node->getExprs();

	for (NodeVector::const_iterator i = exprs.begin(); i != exprs.end(); i++) {
		ExprCode ec;
		generateExpr(*i, ec, ctx);
		out.deps.insert(ec.deps.begin(), ec.deps.end());

		// If this is the last expression in the block, assign its value to the
		// result variable. Note that in case the expression is simply
		// returning a reference to the same result variable this block uses as
		// well, no assignment is generated.
		if (i+1 == exprs.end()) {
			if (!resultVar.empty()) {
				if (resultVar != ec.code)
					ctx.stmts.push_back(resultVar + " = " + precedenceWrap(ec, kAssignmentPrec) + ";");
			} else {
				out.code = ec.code;
				out.isRef = ec.isRef;
				out.precedence = ec.precedence;
				out.deps.insert(ec.deps.begin(), ec.deps.end());
			}
		}

		// Otherwise insert the expression code as a statement as long as said
		// code is not simply a reference to a variable.
		else if (!ec.isRef) {
			ctx.stmts.push_back(ec.code + ";");
		}
	}
}
