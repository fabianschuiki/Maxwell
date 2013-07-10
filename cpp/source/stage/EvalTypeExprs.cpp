/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>

using namespace ast;
using stage::EvalTypeExprs;

void EvalTypeExprs::process(const NodePtr& node)
{
	// Evaluate children's type expressions.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Operate on type expressions.
	if (TypeExprInterface *intf = node->asTypeExpr())
	{
		// Do nothing if the type expression is already evaluated.
		if (intf->getEvaluatedType(false))
			return;

		// Otherwise operate on all known expressions.
		if (NamedTypeExpr *expr = dynamic_cast<NamedTypeExpr*>(node.get())) {
			const NodePtr& def = expr->getDefinition();
			assert(def && "NamedTypeExpr without a resolved definition.");
			shared_ptr<DefinedType> t(new DefinedType);
			t->setDefinition(def);
			intf->setEvaluatedType(t);
		}

		// Throw an error if we were unable to assign an evaluated type.
		if (!intf->getEvaluatedType(false)) {
			throw std::runtime_error("Could not evaluate type expression " + node->getId().str() + ".");
		}
	}
}