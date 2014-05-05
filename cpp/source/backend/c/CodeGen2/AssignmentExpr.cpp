/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "detail.hpp"

DEF_EXPR(AssignmentExpr)
{
	// Assigning to an identifier is fairly dull at the moment.
	if (const IdentifierExpr::Ptr& lhs = IdentifierExpr::from(node->getLhs())) {
		ExprCode ec;
		generateIdentifierExpr(lhs, ec, ctx);
		out.deps.insert(ec.deps.begin(), ec.deps.end());

		// Generate the code for the RHS of the assignment.
		ExprCode rhs;
		generateExpr(node->getRhs(), rhs, ctx);
		out.deps.insert(rhs.deps.begin(), rhs.deps.end());

		// Synthesize the output.
		out.code = ec.code + " = " + precedenceWrap(rhs, kAssignmentPrec);
		out.isRef = false;
		out.precedence = kAssignmentPrec;
	}

	// Assigning to a function call is handled by simply generating the call
	// which has already been prepared for this setup: A '=' was added to its
	// name and the arguments were extended by the assignment's RHS.
	else if (const CallExpr::Ptr& lhs = CallExpr::from(node->getLhs())) {
		generateExpr(lhs, out, ctx);
	}

	else {
		throw std::runtime_error("Only IdentifierExpr or CallExpr may be used as the lhs of an assignment, got " + node->getLhs()->getClassName() + " instead.");
	}
}
