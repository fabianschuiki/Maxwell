/* Copyright © 2013 Fabian Schuiki */
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
			var->setPossibleType(typeExpr->asTypeExpr()->getEvaluatedType());
		} else {
			addDependency(node, "typeExpr");
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
		DefinedType::Ptr typeInt(new DefinedType), typeReal(new DefinedType);
		typeInt->setDefinition(repository.getBuiltinType("Int"));
		typeReal->setDefinition(repository.getBuiltinType("Real"));
		NodeVector types(2);
		types[0] = typeInt;
		types[1] = typeReal;
		TypeSet::Ptr typeSet(new TypeSet);
		typeSet->setTypes(types);
		num->setPossibleType(typeSet);
	}
	if (const StringConstExpr::Ptr& str = StringConstExpr::from(node)) {
		DefinedType::Ptr type(new DefinedType);
		type->setDefinition(repository.getBuiltinType("String"));
		str->setPossibleType(type);
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
		const NodePtr& funcNode = candidate->getFunc();
		CallableInterface* func = funcNode->needCallable();
		// For now enforce single return values.
		if (func->getOut().size() > 1) {
			throw std::runtime_error("Only calls to functions with zero or one output argument are supported at the moment. Function " + funcNode->getId().str() + " called by " + node->getParent()->getId().str() + " violates this constraint.");
		}
		addDependency(funcNode, "out.0.actualType");
		if (func->getOut().size() == 1) {
			const NodePtr& funcOut0 = func->getOut()[0];
			// println(-1, "func->getOut()[0] = " + funcOut0->getId().str(), candidate);
			// println(-1, "func->getOut()[0]->needType()->getActualType() = " + funcOut0->needType()->getActualType()->getId().str(), candidate);
			candidate->setPossibleType(funcOut0->needType()->getActualType());
		} else {
			candidate->setPossibleType(NodePtr(new InvalidType));
		}
	}

	// Call candidate arguments simply copy the function's argument type.
	if (CallCandidateArg* arg = dynamic_cast<CallCandidateArg*>(node.get())) {
		addDependency(arg, "arg.possibleType");
		arg->setPossibleType(arg->getArg()->needCallArg()->getExpr()->needType()->getPossibleType());
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