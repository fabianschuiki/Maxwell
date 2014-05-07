/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>

using namespace ast;
using stage::BuildGraph;

void BuildGraph::process(const NodePtr& node)
{
	process(node, NodePtr());
}

NodePtr BuildGraph::process(const NodePtr& node, const NodePtr& carry)
{
	NodePtr previous; // last node in the chain
	if (GraphInterface* intf = node->asGraph()) {
		intf->setGraphPrev(carry);
		previous = node;
	} else {
		previous = carry;
	}

	// Perform the operation on the node's children.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		previous = process(*it, previous);
	}
	return previous;
}