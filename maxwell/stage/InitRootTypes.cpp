/* Copyright (c) 2013-2015 Fabian Schuiki */
#include "maxwell/stage/stages.hpp"
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
	if (const FuncArg::Ptr& arg = FuncArg::from(node)) {
		const NodePtr& evt = arg->getTypeExpr()->needTypeExpr()->getEvaluatedType();
		arg->setPossibleType(evt);
		arg->setActualType(evt);
	}

	// Assign types to functions.
	if (const FuncDef::Ptr& def = FuncDef::from(node)) {
		NodePtr inType, outType;

		// Create either a tuple for the in and out types if the function has
		// input or output arguments, or nil if it doesn't.
		if (def->getIn().empty()) {
			inType.reset(new NilType);
		} else {
			NodeVector inArgs;
			wrapFuncArgs(inArgs, def->getIn());

			TupleType::Ptr inTuple(new TupleType);
			inTuple->setArgs(inArgs);
			inType = inTuple;
		}

		if (def->getImplOut()) {
			addDependency(def, "body.actualType");
			NodePtr actualType = def->getBody()->needType()->getActualType(false);
			if (!actualType)
				actualType.reset(new GenericType);

			TupleTypeArg::Ptr outArg(new TupleTypeArg);
			outArg->setName("_");
			outArg->setType(actualType);
			NodeVector outArgs(1);
			outArgs[0] = outArg;

			TupleType::Ptr outTuple(new TupleType);
			outTuple->setArgs(outArgs);
			outType = outTuple;
		} else if (def->getOut().empty()) {
			outType.reset(new NilType);
		} else {
			NodeVector outArgs;
			wrapFuncArgs(outArgs, def->getOut());

			TupleType::Ptr outTuple(new TupleType);
			outTuple->setArgs(outArgs);
			outType = outTuple;
		}

		// Wrap the two types in a FuncType node.
		FuncType::Ptr func(new FuncType);
		func->setIn(inType);
		func->setOut(outType);

		// Assign the FuncType to the function definition.
		def->setType(func);
	}

	// Assign types to native functions.
	if (const auto& def = NativeFuncDef::from(node)) {
		NodePtr inType, outType;

		// Create either a tuple for the in and out types if the function has
		// input or output arguments, or nil if it doesn't.
		if (def->getIn().empty()) {
			inType.reset(new NilType);
		} else {
			NodeVector inArgs;
			wrapFuncArgs(inArgs, def->getIn());

			TupleType::Ptr inTuple(new TupleType);
			inTuple->setArgs(inArgs);
			inType = inTuple;
		}

		if (def->getOut().empty()) {
			outType.reset(new NilType);
		} else {
			NodeVector outArgs;
			wrapFuncArgs(outArgs, def->getOut());

			TupleType::Ptr outTuple(new TupleType);
			outTuple->setArgs(outArgs);
			outType = outTuple;
		}

		// Wrap the two types in a FuncType node.
		FuncType::Ptr func(new FuncType);
		func->setIn(inType);
		func->setOut(outType);

		// Assign the FuncType to the function definition.
		def->setType(func);
	}
}

void InitRootTypes::wrapFuncArgs(NodeVector& args, const NodeVector& funcArgs)
{
	for (NodeVector::const_iterator it = funcArgs.begin(); it != funcArgs.end(); it++) {
		const FuncArg::Ptr& funcArg = FuncArg::from(*it);
		TupleTypeArg::Ptr arg(new TupleTypeArg);
		arg->setName(funcArg->getName());
		arg->setType(funcArg->getPossibleType());
		args.push_back(arg);
	}
}
