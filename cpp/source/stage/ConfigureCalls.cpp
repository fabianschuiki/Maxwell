/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>

using namespace ast;
using stage::ConfigureCalls;

void ConfigureCalls::process(const NodePtr& node)
{
	// Configure calls for the node's children.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Configure call expressions.
	if (CallExpr *call = dynamic_cast<CallExpr*>(node.get())) {
		
	}

	// Configure binary operators.
	if (BinaryOpExpr *binop = dynamic_cast<BinaryOpExpr*>(node.get())) {
		if (binop->getCallName().empty() || binop->getCallArgs().empty())
		{
			// Use the operator as function name.
			binop->setCallName(binop->getOperatorName());

			// Create references to the left and right hand side.
			shared_ptr<CallArg> lhs(new CallArg), rhs(new CallArg);
			lhs->setExpr(binop->getLhs());
			rhs->setExpr(binop->getRhs());

			// Create the argument vector.
			NodeVector args(2);
			args[0] = lhs;
			args[1] = rhs;

			// Store the arguments in the call interface.
			binop->setCallArgs(args);
		}
	}
}