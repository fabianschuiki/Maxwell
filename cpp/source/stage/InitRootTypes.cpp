/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>

using namespace ast;
using stage::InitRootTypes;
using boost::dynamic_pointer_cast;

void InitRootTypes::process(const NodePtr& node)
{
	// Calculate the possible type of all child nodes first.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Assign types to function arguments.
	if (FuncArg* arg = dynamic_cast<FuncArg*>(node.get())) {
		const NodePtr& evt = arg->getType()->needTypeExpr()->getEvaluatedType();
		arg->setPossibleType(evt);
		arg->setActualType(evt);
	}

	// Assign types to functions.
	if (FuncDef* def = dynamic_cast<FuncDef*>(node.get()))
	{
		// Create the arrays of input and output TupleTypeArgs based on the
		// function arguments.
		NodeVector inArgs, outArgs;
		wrapFuncArgs(inArgs, def->getIn());
		wrapFuncArgs(outArgs, def->getOut());

		// Wrap the arrays in two TupleType nodes.
		shared_ptr<TupleType> inTuple(new TupleType), outTuple(new TupleType);
		inTuple->setArgs(inArgs);
		outTuple->setArgs(outArgs);

		// Wrap the two TupleTypes in a FuncType node.
		shared_ptr<FuncType> func(new FuncType);
		func->setIn(inTuple);
		func->setOut(outTuple);

		// Assign the FuncType to the function definition.
		def->setType(func);
	}
}

void InitRootTypes::wrapFuncArgs(NodeVector& args, const NodeVector& funcArgs)
{
	for (NodeVector::const_iterator it = funcArgs.begin(); it != funcArgs.end(); it++) {
		const shared_ptr<FuncArg>& funcArg = dynamic_pointer_cast<FuncArg>(*it);
		shared_ptr<TupleTypeArg> arg(new TupleTypeArg);
		arg->setName(funcArg->getName());
		arg->setType(funcArg->getPossibleType());
		args.push_back(arg);
	}
}