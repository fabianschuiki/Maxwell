/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_EXPR(TupleExpr)
{
	// Generate the code for each of the tuple arguments.
	const NodeVector& args = node->getArgs();
	std::string body;

	for (NodeVector::const_iterator i = args.begin(); i != args.end(); i++) {
		const TupleExprArg::Ptr& arg = TupleExprArg::needFrom(*i);

		if (i != args.begin())
			body += ", ";

		std::string name = makeFriendly(arg->getName(false));
		if (!name.empty()) {
			body += "." + name + " = ";
		}

		ExprCode ec;
		generateExpr(arg->getExpr(), ec, ctx);
		body += precedenceWrap(ec, kLowestPrec);
		out.deps.insert(ec.deps.begin(), ec.deps.end());
	}


	// Generate the code for the tuple type.
	TypeCode tc;
	generateType(node->getActualType(), tc);
	out.deps.insert(tc.deps.begin(), tc.deps.end());


	// Synthesize the output.
	out.code = "(" + tc.code + "){" + body + "}";
	out.isRef = true;
	out.precedence = kPrimaryPrec;
}
