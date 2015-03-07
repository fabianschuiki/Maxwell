/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_EXPR(ForExpr)
{
	const NodePtr& init = node->getInit(false);
	const NodePtr& cond = node->getCond();
	const NodePtr& step = node->getStep(false);

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


	// Generate the code for the initial expression.
	ExprCode initCode;
	if (init) {
		generateExpr(init, initCode, ctx);
		out += initCode;
	}

	// Generate the code for the condition expression inside the loop body's
	// context. If this spawns any statements within the loop body, the
	// condition is considered 'complex' and is moved inside the loop body.
	// Otherwise it is inserted in its usual place for(...; <cond>; ...).
	Context bodyCtx(ctx);
	ExprCode condCode;
	generateExpr(cond, condCode, bodyCtx);
	out += condCode;
	bool condComplex = !bodyCtx.stmts.empty();
	if (condComplex)
		bodyCtx.stmts.push_back("if (!" + precedenceWrap(condCode, kPrefixPrec) + ") break;");

	// Generate the code for the loop body.
	ExprCode bodyCode;
	generateExpr(node->getBody(), bodyCode, bodyCtx);
	out += bodyCode;

	if (resultVar != bodyCode.code)
		bodyCtx.stmts.push_back(resultVar + " = " + precedenceWrap(bodyCode, kAssignmentPrec) + ";");
	else if (!bodyCode.isRef)
		bodyCtx.stmts.push_back(bodyCode.code + ";");

	// Generate the code for the step expression. If this spawns additional
	// statements in the loop body, the step expression is considered 'complex'
	// and is moved inside the loop body. Otherwise it is inserted in its usual
	// place for(...; ...; <step>).
	ExprCode stepCode;
	bool stepComplex = false;
	if (step) {
		unsigned nums = bodyCtx.stmts.size();
		generateExpr(step, stepCode, bodyCtx);
		out += stepCode;
		stepComplex = (nums != bodyCtx.stmts.size());
		if (stepComplex && !stepCode.isRef)
			bodyCtx.stmts.push_back(stepCode.code + ";");
	}


	// Synthesize the for statement.
	std::string stmt = "for (";
	if (!initCode.code.empty() && !initCode.isRef)
		stmt += initCode.code;
	stmt += ";";

	if (condComplex || condCode.code.empty())
		stmt += ";";
	else
		stmt += " " + condCode.code + ";";

	if (!stepComplex && !stepCode.code.empty() && !stepCode.isRef)
		stmt += " " + stepCode.code;

	stmt += ")";

	// Loop body.
	bool compact = (bodyCtx.stmts.size() <= 1);
	stmt += (compact ? "\n" : " {\n");
	for (std::vector<std::string>::const_iterator i = bodyCtx.stmts.begin(); i != bodyCtx.stmts.end(); i++) {
		stmt += indent(*i);
		if (!compact)
			stmt += "\n";
	}
	if (!compact)
		stmt += "}";

	// Add the statement to the context.
	ctx.stmts.push_back(stmt);
}
