/* Copyright © 2013-2014 Fabian Schuiki */
#include "stages.hpp"
#include "algorithm/type.hpp"
#include <iostream>

using namespace ast;
using stage::CalcPossibleTypes;
using boost::dynamic_pointer_cast;

void CalcPossibleTypes::process(const NodePtr& node)
{
	if (TypeInterface *intf = node->asType()) {
		if (!intf->getRequiredType(false)) {
			intf->setRequiredType(NodePtr(new GenericType));
		}
	}
	processChildren(node);
}

void CalcPossibleTypes::processChildren(const NodePtr& node)
{
	// Calculate the possible type of all child nodes first.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		processChildren(*it);
	}
	println(1, "processing " + node->getId().str());

	// Variable-like nodes.
	if (VariableInterface *var = node->asVariable()) {
		if (const NodePtr& typeExpr = var->getTypeExpr(false)) {
			addDependency(node, "typeExpr.evaluatedType");
			var->setPossibleType(typeExpr->needTypeExpr()->getEvaluatedType());
		} else {
			addDependency(node, "typeExpr");
			NodePtr result;
			VarDefExpr::Ptr vardef;
			NodePtr initialExpr;
			if (const VarDefExpr::Ptr& vardef = VarDefExpr::from(node)) {
				if (const NodePtr& initialExpr = vardef->getInitialExpr(false)) {
					addDependency(node, "initialExpr.actualType");
					result = initialExpr->needType()->getActualType();
				}
			} else if (const TypelessVarDefExpr::Ptr& vardef = TypelessVarDefExpr::from(node)) {
				addDependency(node, "initialExpr.actualType");
				result = vardef->getInitialExpr()->needType()->getActualType();
			}
			if (result)
				var->setPossibleType(result);
			else
				var->setPossibleType(NodePtr(new GenericType));
		}
	}

	// Identifier expressions.
	if (IdentifierExpr *ident = dynamic_cast<IdentifierExpr*>(node.get())) {
		const NodePtr& target = ident->getBindingTarget();
		if (VariableInterface *intf = target->asVariable()) {
			addDependency(target, "actualType");
			ident->setPossibleType(intf->getActualType());
		} else {
			throw std::runtime_error("Identifier target '" + target->getId().str() + "' (a " + target->getClassName() + ") not supported for CalcPossibleTypes.");
		}
	}

	// Assignment expressions return their assignment type.
	if (const AssignmentExpr::Ptr& assign = AssignmentExpr::from(node)) {
		addDependency(assign, "lhs.actualType");
		assign->setPossibleType(assign->getLhs()->needType()->getActualType());
	}

	// Constants.
	if (const NumberConstExpr::Ptr& num = NumberConstExpr::from(node)) {
		// DefinedType::Ptr typeInt(new DefinedType), typeReal(new DefinedType);
		// typeInt->setDefinition(repository.getBuiltinType("Int"));
		// typeReal->setDefinition(repository.getBuiltinType("Real"));
		// NodeVector types(2);
		// types[0] = typeInt;
		// types[1] = typeReal;
		// TypeSet::Ptr typeSet(new TypeSet);
		// typeSet->setTypes(types);
		// num->setPossibleType(typeSet);
		DefinedType::Ptr type(new DefinedType);
		if (num->getValue().find('.') != string::npos) {
			type->setDefinition(repository.getBuiltinType("Real"));
		} else {
			type->setDefinition(repository.getBuiltinType("Int"));
		}
		num->setPossibleType(type);
	}
	if (const StringConstExpr::Ptr& str = StringConstExpr::from(node)) {
		DefinedType::Ptr type(new DefinedType);
		type->setDefinition(repository.getBuiltinType("String"));
		str->setPossibleType(type);
	}
	if (const ArrayConstExpr::Ptr& ac = ArrayConstExpr::from(node)) {
		NodeVector types;
		const NodeVector& exprs = ac->getExprs();
		for (NodeVector::const_iterator it = exprs.begin(); it != exprs.end(); it++) {
			addDependency((*it), "actualType");
			types.push_back((*it)->needType()->getActualType());
		}
		UnionType::Ptr unionType(new UnionType);
		unionType->setTypes(types);
		NodePtr exprsType = algorithm::type::simplify(unionType);
		ac->setExprsType(exprsType);

		DefinedType::Ptr typeArray(new DefinedType);
		typeArray->setDefinition(repository.getBuiltinType("Array"));
		NodeVector specs(1);
		specs[0] = exprsType;
		SpecializedType::Ptr type(new SpecializedType);
		type->setType(typeArray);
		type->setSpecs(specs);
		ac->setPossibleType(type);
	}

	// IfCaseExpr produce the union type of all expressions.
	if (const IfCaseExpr::Ptr& expr = IfCaseExpr::from(node)) {
		NodeVector types;

		// Gather the types of all the expressions and the optional otherwise expression.
		const NodeVector& conds = expr->getConds();
		for (NodeVector::const_iterator it = conds.begin(); it != conds.end(); it++) {
			const IfCaseExprCond::Ptr& cond = IfCaseExprCond::from(*it);
			addDependency(cond, "expr.actualType");
			types.push_back(cond->getExpr()->needType()->getActualType());
		}
		const NodePtr& othw = expr->getOtherwise(false);
		if (othw) {
			addDependency(othw, "actualType");
			types.push_back(othw->needType()->getActualType());
		}

		// Wrap the types up in a UnionType.
		UnionType::Ptr unionType(new UnionType);
		unionType->setTypes(types);
		expr->setPossibleType(algorithm::type::simplify(unionType));
	}

	// Blocks in general "return" the same type/value as their last element, or nil if they are empty.
	if (const BlockExpr::Ptr& block = BlockExpr::from(node)) {
		if (block->getExprs().empty()) {
			block->setPossibleType(NodePtr(new NilType));
		} else {
			const NodePtr& last = block->getExprs().back();
			addDependency(last, "actualType");
			block->setPossibleType(last->needType()->getActualType());
		}
	}

	// If-expressions produce the union type of both branches.
	if (const IfExpr::Ptr& expr = IfExpr::from(node)) {
		NodeVector types;

		// Gather the types.
		const NodePtr& bodyBranch = expr->getBody();
		const NodePtr& elseBranch = expr->getElseExpr(false);
		addDependency(bodyBranch, "actualType");
		types.push_back(bodyBranch->needType()->getActualType());
		if (elseBranch) {
			addDependency(elseBranch, "actualType");
			types.push_back(elseBranch->needType()->getActualType());
		}

		// Wrap up in a UnionType.
		UnionType::Ptr unionType(new UnionType);
		unionType->setTypes(types);
		expr->setPossibleType(algorithm::type::simplify(unionType));
	}

	// For-expressions produce a nil type for now. Later on they maybe should return the last expression
	// in the body for the last iteration step.
	if (const ForExpr::Ptr& expr = ForExpr::from(node)) {
		// expr->setPossibleType(NodePtr(new NilType));
		const NodePtr& bodyBranch = expr->getBody();
		addDependency(bodyBranch, "actualType");
		expr->setPossibleType(bodyBranch->needType()->getActualType());
	}


	/*
	 * Call-related stuff.
	 */

	// For nodes that implement the CallInterface, iterate through all call
	// candidates and find the union set of the return types.
	if (CallInterface *intf = node->asCall()) {
		if (TypeInterface* typeIntf = node->asType()) {
			// Iterate over the call candidates and gather a list of output types.
			NodeVector outTypes;
			const NodeVector& candidates = intf->getCallCandidates();
			for (NodeVector::const_iterator it = candidates.begin(); it != candidates.end(); it++) {
				const CallCandidate::Ptr& candidate = CallCandidate::needFrom(*it);
				if (candidate->getFeasible()) {
					outTypes.push_back(candidate->getActualType());
				}
				addDependency(candidate, "feasible");
				addDependency(candidate, "actualType");
			}

			// Wrap the output types into a TypeSet which may be further processed
			// through type modification functions.
			shared_ptr<TypeSet> typeSet(new TypeSet);
			typeSet->setTypes(outTypes);

			// Assign this type set as the call's possible type.
			typeIntf->setPossibleType(algorithm::type::simplify(typeSet));
		}
	}

	// Call candidates simply copy the function's return type.
	if (const CallCandidate::Ptr& candidate = CallCandidate::from(node)) {
		if (!candidate->getFeasible()) return;

		const NodePtr& funcNode = candidate->getFunc();
		FuncType::Ptr funcType;
		if (CallableInterface* func = funcNode->asCallable()) {
			funcType = FuncType::needFrom(func->getType());
			addDependency(funcNode, "type.out");
		} else if (TypeInterface* type = funcNode->asType()) {
			funcType = FuncType::needFrom(type->getActualType());
			addDependency(funcNode, "actualType.out");
		} else {
			candidate->setFeasible(false);
			return;
		}
		const TupleType::Ptr& outTuple = TupleType::from(funcType->getOut());

		// If the output type of the function is not a tuple we reuse it directly.
		// Otherwise we dissect the tuple. This step should become obsolete later on
		// when 1-tuples have an implicit conversion to their only field.
		if (!outTuple) {
			candidate->setPossibleType(funcType->getOut());
		} else {
			assert(outTuple->getArgs().size() > 0 && "Output tuple should have at least one field, or be nil otherwise.");

			// For now enforce single return values.
			if (outTuple->getArgs().size() > 1) {
				throw std::runtime_error("Only calls to functions with zero or one output argument are supported at the moment. Function " + funcNode->getId().str() + " called by " + node->getParent()->getId().str() + " violates this constraint.");
			}
			addDependency(funcNode, "type.out.args.0.type");
			if (outTuple->getArgs().size() == 1) {
				const TupleTypeArg::Ptr& funcOut0 = TupleTypeArg::needFrom(outTuple->getArgs()[0]);
				candidate->setPossibleType(funcOut0->getType());
			}
		}
	}

	// Call candidate arguments simply copy the function's argument type.
	if (CallCandidateArg* arg = dynamic_cast<CallCandidateArg*>(node.get())) {
		addDependency(arg, "arg.possibleType");
		arg->setPossibleType(arg->getArg()->needCallArg()->getExpr()->needType()->getPossibleType());
	}

	if (const FuncExpr::Ptr& fe = FuncExpr::from(node)) {
		addDependency(fe, "expr.actualType");
		const NodeVector& args = fe->getArgs();
		const NodePtr& expr = fe->getExpr();

		// Assemble the input arguments.
		NodePtr inType;
		if (args.empty()) {
			inType.reset(new NilType);
		} else {
			NodeVector tupleArgs;
			for (NodeVector::const_iterator it = args.begin(); it != args.end(); it++) {
				const FuncArg::Ptr& funcArg = FuncArg::from(*it);
				TupleTypeArg::Ptr arg(new TupleTypeArg);
				arg->setName(funcArg->getName());
				arg->setType(funcArg->getPossibleType());
				tupleArgs.push_back(arg);
			}

			TupleType::Ptr tuple(new TupleType);
			tuple->setArgs(tupleArgs);
			inType = tuple;
		}

		FuncType::Ptr type(new FuncType);
		type->setIn(inType);
		type->setOut(expr->needType()->getActualType());
		fe->setPossibleType(type);
	}


	/*
	 * Wrapping up.
	 */

	// In case no actualy type has been set yet, simply copy the possible type over.
	if (TypeInterface *intf = node->asType()) {
		if (!intf->getPossibleType(false)) {
			throw std::runtime_error("No possibleType calculated for node " + node->getId().str() + " (a " + node->getClassName() + ").");
		}
		if (!intf->getActualType(false)) {
			intf->setActualType(intf->getPossibleType());
		}
	}
}