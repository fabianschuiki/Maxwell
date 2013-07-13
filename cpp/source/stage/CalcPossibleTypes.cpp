/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
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
		if (const NodePtr& type = var->getType(false)) {
			addDependency(node, "type.evaluatedType");
			var->setPossibleType(type->asTypeExpr()->getEvaluatedType());
		} else {
			addDependency(node, "type");
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
				const shared_ptr<CallCandidate>& candidate = dynamic_pointer_cast<CallCandidate>(*it);
				outTypes.push_back(candidate->getType());
				addDependency(candidate, "type");
			}

			// Wrap the output types into a TypeSet which may be further processed
			// through type modification functions.
			shared_ptr<TypeSet> types(new TypeSet);
			types->setTypes(outTypes);

			// Assign this type set as the call's possible type.
			typeIntf->setPossibleType(types);
		}
	}

	// Call candidates simply copy the function's return type.
	if (CallCandidate* candidate = dynamic_cast<CallCandidate*>(node.get())) {
		const shared_ptr<FuncDef>& func = dynamic_pointer_cast<FuncDef>(candidate->getFunc());
		// For now enforce single return values.
		if (func->getOut().size() > 1) {
			throw std::runtime_error("Only calls to functions with zero or one output argument are supported at the moment. Function " + func->getId().str() + " called by " + node->getParent()->getId().str() + " violates this constraint.");
		}
		addDependency(func, "out.0.actualType");
		if (func->getOut().size() == 1) {
			candidate->setType(func->getOut()[0]->needVariable()->getActualType());
		} else {
			candidate->setType(NodePtr(new InvalidType));
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
			throw std::runtime_error("No possibleType calculated for node " + node->getId().str() + ".");
		}
		if (!intf->getActualType(false)) {
			intf->setActualType(intf->getPossibleType());
		}
	}
}