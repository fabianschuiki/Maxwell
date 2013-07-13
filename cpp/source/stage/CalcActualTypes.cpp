/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include "algorithm/type.hpp"
#include <iostream>

using namespace ast;
using stage::CalcActualTypes;

void CalcActualTypes::process(const NodePtr& node)
{
	// Calculate the actual types of our child nodes first.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Operate on nodes implementing the TypeInterface only.
	TypeInterface* typeIntf = node->asType();
	if (!typeIntf) return;

	// Fetch the two main snippets of information required.
	const NodePtr& possible = typeIntf->getPossibleType();
	const NodePtr& required = typeIntf->getRequiredType();
	addDependency(node, "possibleType");
	addDependency(node, "requiredType");

	// Catch the simple cases where possible, otherwise perform more elaborate calculations.
	NodePtr actual;
	if (possible->isKindOf(kInvalidType) || required->isKindOf(kGenericType)) {
		actual = possible;
	} else if (required->isKindOf(kInvalidType)) {
		throw std::runtime_error("Required type of " + node->getId().str() + " is invalid.");
	} else {
		actual = match(possible, required, node);
	}
	println(0, possible->describe() + " \u2229 " + required->describe() + " = " + actual->describe(), node);

	// Assign the calculated type to the node we're processing.
	typeIntf->setActualType(actual);
}

NodePtr CalcActualTypes::match(const NodePtr& possible, const NodePtr& required, const NodePtr& node)
{
	// First try to perform a simple intersect on the two types.
	NodePtr actual = algorithm::type::intersect(possible, required);

	// Otherwise simply try to go with a regular cast.
	if (actual->isKindOf(kInvalidType)) {
		println(1, "Trying to cast from " + possible->describe() + " to " + required->describe(), node);
	}

	return actual;
}