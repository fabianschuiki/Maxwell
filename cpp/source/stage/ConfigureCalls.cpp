/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>

using namespace ast;
using stage::ConfigureCalls;

void ConfigureCalls::process(const NodePtr& node)
{
	// Configure calls for the node's children.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Configure call expressions.
	if (CallExpr *call = dynamic_cast<CallExpr*>(node.get())) {
		
	}

	// Configure binary operators.
	if (BinaryOpExpr *call = dynamic_cast<BinaryOpExpr*>(node.get())) {
		
	}
}