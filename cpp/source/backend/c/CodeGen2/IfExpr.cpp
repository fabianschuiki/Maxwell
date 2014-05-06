/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "detail.hpp"

static bool hasPrefix(const std::string& s, const std::string& prefix)
{
	return (s.length() >= prefix.length() && s.substr(0, prefix.length()) == prefix);
}

DEF_EXPR(IfExpr)
{
	// Generate the temporary variable that will hold the result of the
	// expression.
	std::string resultVar;
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


	// Generate the code for the condition expression.
	ExprCode condCode;
	generateExpr(node->getCond(), condCode, ctx);
	out.deps.insert(condCode.deps.begin(), condCode.deps.end());

	// Generate the code for the main expression.
	Context bodyCtx(ctx);
	ExprCode bodyCode;
	generateExpr(node->getBody(), bodyCode, bodyCtx);
	out.deps.insert(bodyCode.deps.begin(), bodyCode.deps.end());

	if (resultVar != bodyCode.code)
		bodyCtx.stmts.push_back(resultVar + " = " + precedenceWrap(bodyCode, kAssignmentPrec) + ";");
	else if (!bodyCode.isRef)
		bodyCtx.stmts.push_back(bodyCode.code + ";");

	// Generate the code for the else expression, if any.
	const NodePtr& elseExpr = node->getElseExpr(false);
	Context elseCtx(ctx);
	ExprCode elseCode;
	if (elseExpr) {
		generateExpr(elseExpr, elseCode, elseCtx);
		out.deps.insert(elseCode.deps.begin(), elseCode.deps.end());

		if (resultVar != elseCode.code)
			elseCtx.stmts.push_back(resultVar + " = " + precedenceWrap(elseCode, kAssignmentPrec) + ";");
		else if (!elseCode.isRef)
			elseCtx.stmts.push_back(elseCode.code + ";");
	}


	// Synthesize the if statement.
	bool compact = (bodyCtx.stmts.size() <= 1 && elseCtx.stmts.size() <= 1);
	std::string stmt = "if (" + condCode.code + ")";

	// Main branch.
	stmt += compact ? "\n" : " {\n";
	for (std::vector<std::string>::const_iterator i = bodyCtx.stmts.begin(); i != bodyCtx.stmts.end(); i++)
		stmt += indent(*i) + "\n";
	if (!compact)
		stmt += "}";

	// Else branch, if it has any statements. Otherwise it is omitted.
	if (!elseCtx.stmts.empty()) {
		if (!compact)
			stmt += " ";
		stmt += "else";

		// If the statements of the else branch is simply another if statement,
		// there is no need to add additional braces around it, so we make the
		// else compact. Otherwise we simply follow what was decided for the
		// main branch in terms of compactness.
		int compactness = compact ? 1 : 0;
		if (hasPrefix(elseCtx.stmts.front(), "if") && elseCtx.stmts.size() == 1)
			compactness = 2;

		if (compactness == 0)
			stmt += " {";
		if (compactness < 2)
			stmt += "\n";
		for (std::vector<std::string>::const_iterator i = elseCtx.stmts.begin(); i != elseCtx.stmts.end(); i++)
			stmt += indent(*i) + "\n";
		if (compactness == 0)
			stmt += "}";
	}

	// Add the statement to the context.
	ctx.stmts.push_back(stmt);
}
