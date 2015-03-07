/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_EXPR(IfCaseExpr)
{
	// Generate the temporary variable that will hold the result of the
	// expression.
	std::string resultVar;
	if (resultVar.empty()) {
		TypeCode tc;
		generateType(node->getActualType(), tc);
		out += tc;

		resultVar = ctx.makeTempSymbol();
		ctx.stmts.push_back(tc.code + " " + resultVar + ";");
	}
	out.code = resultVar;
	out.isRef = true;
	out.precedence = kPrimaryPrec;


	// Generate the code for the conditional branches of the if statement.
	const NodeVector& conds = node->getConds();
	std::string stmt;

	for (NodeVector::const_iterator i = conds.begin(); i != conds.end(); i++) {
		const IfCaseExprCond::Ptr& cond = IfCaseExprCond::needFrom(*i);

		// Generate the code for the condition expression.
		ExprCode condCode;
		generateExpr(cond->getCond(), condCode, ctx);
		out += condCode;

		// Generate the code for the condition body.
		Context bodyCtx(ctx);
		ExprCode bodyCode;
		generateExpr(cond->getExpr(), bodyCode, bodyCtx);
		out += bodyCode;

		if (resultVar != bodyCode.code)
			bodyCtx.stmts.push_back(resultVar + " = " + precedenceWrap(bodyCode, kAssignmentPrec) + ";");
		else if (!bodyCode.isRef)
			bodyCtx.stmts.push_back(bodyCode.code + ";");

		// Synthesize the code for this branch of the if statement.
		if (i != conds.begin())
			stmt += " else ";
		stmt += "if (" + condCode.code + ") {\n";
		for (std::vector<std::string>::const_iterator k = bodyCtx.stmts.begin(); k != bodyCtx.stmts.end(); k++)
			stmt += indent(*k) + "\n";
		stmt += "}";
	}

	// Generate the code for the 'otherwise' branch, if any.
	const NodePtr& otherwise = node->getOtherwise(false);
	if (otherwise) {
		Context bodyCtx(ctx);
		ExprCode bodyCode;
		generateExpr(otherwise, bodyCode, bodyCtx);
		out += bodyCode;

		if (resultVar != bodyCode.code)
			bodyCtx.stmts.push_back(resultVar + " = " + precedenceWrap(bodyCode, kAssignmentPrec) + ";");
		else if (!bodyCode.isRef)
			bodyCtx.stmts.push_back(bodyCode.code + ";");

		// Synthesize the code for the unconditional else statement.
		stmt += " else {\n";
		for (std::vector<std::string>::const_iterator i = bodyCtx.stmts.begin(); i != bodyCtx.stmts.end(); i++)
			stmt += indent(*i) + "\n";
		stmt += "}";
	}

	// Add the statement to the context.
	ctx.stmts.push_back(stmt);
}
