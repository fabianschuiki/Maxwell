/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>
#include <boost/pointer_cast.hpp>

using namespace ast;
using stage::ConfigureCalls;
using boost::dynamic_pointer_cast;

void ConfigureCalls::process(const NodePtr& node)
{
	// Configure calls for the node's children.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Configure call expressions.
	if (CallExpr* call = dynamic_cast<CallExpr*>(node.get())) {
		/* CallExpr nodes do not need any argument configuration, as they
		 * already have their arguments configured  as callArgs attributes. This
		 * allows call code to automatically use the actual arguments.
		 */
		if (call->getCallName(false).empty()) {
			if (call->getContext(false)) {
				throw std::runtime_error("Contextual calls (as in " + call->getId().str() + ") are not yet supported.");
			}
			call->setCallName(call->getName());
		}
	}

	// Configure binary operators.
	if (BinaryOpExpr *binop = dynamic_cast<BinaryOpExpr*>(node.get())) {
		if (binop->getCallName(false).empty() || binop->getCallArgs().empty())
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
			binop->updateHierarchyOfChildren();
		}
	}

	// Configure unary operators.
	if (UnaryOpExpr *unop = dynamic_cast<UnaryOpExpr*>(node.get())) {
		if (unop->getCallName(false).empty() || unop->getCallArgs().empty())
		{
			// Use the operator as function name.
			string name = unop->getOperatorName();
			if (unop->getPostfix()) {
				name = '_' + name;
			}
			unop->setCallName(name);

			// Create a reference to the operand.
			shared_ptr<CallArg> arg(new CallArg);
			arg->setExpr(unop->getExpr());

			// Create the argument vector.
			NodeVector args(1);
			args[0] = arg;

			// Store the arguments in the call interface.
			unop->setCallArgs(args);
			unop->updateHierarchyOfChildren();
		}
	}
}