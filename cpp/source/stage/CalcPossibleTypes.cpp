/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>

using namespace ast;
using stage::CalcPossibleTypes;

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
		process(*it);
	}

	// Variable definitions.
	if (VarDefExpr *var = dynamic_cast<VarDefExpr*>(node.get())) {
		if (const NodePtr& type = var->getType(false)) {
			addDependency(var, "type.evaluatedType");
			var->setPossibleType(type->asTypeExpr()->getEvaluatedType());
		} else {
			addDependency(var, "type");
			var->setPossibleType(NodePtr(new GenericType));
		}
	}

	// Function arguments.
	if (FuncArg *arg = dynamic_cast<FuncArg*>(node.get())) {
		if (const NodePtr& type = arg->getType(false)) {
			addDependency(arg, "type.evaluatedType");
			arg->setPossibleType(type->asTypeExpr()->getEvaluatedType());
		} else {
			addDependency(arg, "type");
			arg->setPossibleType(NodePtr(new GenericType));
		}
	}

	// Identifier expressions.
	if (IdentifierExpr *ident = dynamic_cast<IdentifierExpr*>(node.get())) {
		const NodePtr& target = ident->getBindingTarget();
		if (VarDefExpr *t = dynamic_cast<VarDefExpr*>(target.get())) {
			addDependency(ident, "actualType");
			ident->setPossibleType(t->getActualType());
		} else if (FuncArg *t = dynamic_cast<FuncArg*>(target.get())) {
			addDependency(ident, "actualType");
			ident->setPossibleType(t->getActualType());
		} else if (FuncDef *f = dynamic_cast<FuncDef*>(target.get())) {
			// addDependency(f, "type");
			// TODO: this is just a dummy, actually calculate the function type!
			ident->setPossibleType(NodePtr(new GenericType));
		} else {
			throw std::runtime_error("Identifier target '" + target->getId().str() + "' (a " + target->getClassName() + ") not supported for CalcPossibleTypes.");
		}
	}

	// Call expressions.
	if (CallExpr *call = dynamic_cast<CallExpr*>(node.get())) {
		// TODO: this is just a dummy, actually take the possible return types of the call into account!
		call->setPossibleType(NodePtr(new GenericType));
	}

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