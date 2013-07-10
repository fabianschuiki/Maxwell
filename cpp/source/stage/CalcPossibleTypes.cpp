/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>

using namespace ast;
using stage::CalcPossibleTypes;

void CalcPossibleTypes::process(const NodePtr& node)
{
	if (TypeInterface *intf = node->asType()) {
		if (!intf->getRequiredType()) {
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
		addDependency(var, "type");
		var->setPossibleType(var->getType());
	}

	// Identifier expressions.
	if (IdentifierExpr *ident = dynamic_cast<IdentifierExpr*>(node.get())) {
		const NodePtr& target = ident->getBindingTarget();
		if (VarDefExpr *t = dynamic_cast<VarDefExpr*>(target.get())) {
			addDependency(ident, "actualType");
			ident->setPossibleType(t->getActualType());
		} else if (FuncArg *t = dynamic_cast<FuncArg*>(target.get())) {
			addDependency(ident, "type");
			ident->setPossibleType(t->getType());
		} else {
			throw std::runtime_error("Identifier target '" + target->getId().str() + "' not supported for CalcPossibleTypes.");
		}
	}

	// In case no actualy type has been set yet, simply copy the possible type over.
	if (TypeInterface *intf = node->asType()) {
		if (!intf->getActualType()) {
			intf->setActualType(intf->getPossibleType());
		}
	}
}