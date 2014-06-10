/* Copyright (c) 2013 Fabian Schuiki */
#include "maxwell/stage/stages.hpp"
#include <boost/pointer_cast.hpp>
#include <iostream>

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
	if (const CallExpr::Ptr& call = CallExpr::from(node)) {
		if (call->getCallName(false).empty() || call->getCallArgs().empty())
		{
			// Reuse the call name.
			call->setCallName(call->getName());

			// If a context is set, inject that as the first argument to the call.
			NodeVector args;
			if (const NodePtr& context = call->getContext(false)) {
				CallArg::Ptr arg(new CallArg);
				arg->setExpr(context);
				args.push_back(arg);
			}

			// Wrap the CallExprArg nodes into CallArg nodes. This is required
			// as the parent node may inject additional arguments which should
			// not modify the CallExpr itself.
			const NodeVector& argsGiven = call->getArgs();
			for (NodeVector::const_iterator it = argsGiven.begin(); it != argsGiven.end(); it++) {
				const CallExprArg::Ptr& argGiven = CallExprArg::needFrom(*it);
				CallArg::Ptr arg(new CallArg);
				arg->setName(argGiven->getName(false));
				arg->setExpr(argGiven->getExpr());
				args.push_back(arg);
			}

			// Store the arguments.
			call->setCallArgs(args);
			call->updateHierarchyOfChildren();
		}
	}

	// Configure call expressions that reside inside an assignment.
	if (const AssignmentExpr::Ptr& assign = AssignmentExpr::from(node)) {
		if (const CallExpr::Ptr& call = CallExpr::from(assign->getLhs())) {
			string cn = call->getCallName();
			if (cn[cn.size() - 1] != '=') {
				// Append a "=" to the called function's name.
				cn += '=';
				call->setCallName(cn);

				// Append the rhs of the assignment as a function argument.
				NodeVector args = call->getCallArgs();
				CallArg::Ptr arg(new CallArg);
				arg->setExpr(assign->getRhs());
				args.push_back(arg);

				// Store the new arguments.
				call->setCallArgs(args);
				call->updateHierarchyOfChildren();
			}
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
