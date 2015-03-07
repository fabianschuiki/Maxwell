/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_EXPR(IndexOpExpr)
{
	// Generate the code for the type of the members of this tuple. We assume
	// that all fields have the same type for now, as this makes things
	// significantly easier.
	TypeCode tc;
	generateType(node->getActualType(), tc);
	out += tc;

	// Generate the code for the indexee and the index.
	ExprCode indexeeCode, indexCode;
	generateExpr(node->getIndexee(), indexeeCode, ctx);
	generateExpr(node->getIndex(), indexCode, ctx);
	out += indexeeCode;
	out += indexCode;

	// If the indexee is not just a reference to another statement, we have to
	// store its value in an intermediate variable.
	if (!indexeeCode.isRef) {
		TypeCode tc;
		generateType(node->getIndexee()->needType()->getActualType(), tc);
		out += tc;

		std::string varName = ctx.makeTempSymbol();
		ctx.stmts.push_back(tc.code + " " + varName + " = " + precedenceWrap(indexeeCode, kAssignmentPrec) + ";");
		indexeeCode.code = varName;
		indexeeCode.isRef = true;
		indexeeCode.precedence = kPrimaryPrec;
	}

	// We simply cast the tuple to an array of its member types, thus allowing
	// indexed access. This is quite ugly to say the least.
	out.code = "((" + tc.code + "*)&" +
		precedenceWrap(indexeeCode, kPrefixPrec) +
		")[" + precedenceWrap(indexCode, kLowestPrec) + "]";
	out.precedence = kPostfixPrec;
	out.isRef = true;
}
