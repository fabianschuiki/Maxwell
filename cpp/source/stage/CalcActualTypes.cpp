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
		actual = required;
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

	// In case the required type is a union, try mapping the possible type to
	// the required union type.
	if (actual->isKindOf(kInvalidType) && required->isKindOf(kUnionType)) {
		println(1, "Trying to map " + possible->describe() + " to union " + required->describe(), node);
		const UnionType::Ptr& possibleUnion = UnionType::from(possible);
		const UnionType::Ptr& requiredUnion = UnionType::from(required);

		NodeVector types;
		if (possibleUnion) {
			types = possibleUnion->getTypes();
		} else {
			types.push_back(possible);
		}

		bool valid = true;
		for (NodeVector::iterator ia = types.begin(); ia != types.end(); ia++) {
			bool found = false;
			for (NodeVector::const_iterator ib = requiredUnion->getTypes().begin(); ib != requiredUnion->getTypes().end(); ib++) {
				if (algorithm::type::equal(*ia, *ib)) {
					found = true;
					break;
				}
			}
			if (!found) {
				valid = false;
				break;
			}
		}

		if (valid) {
			UnionMappedType::Ptr type(new UnionMappedType);
			type->setIn(possible);
			type->setOut(required);
			actual = type;
		}
	}

	// Otherwise simply try to go with a regular cast.
	if (actual->isKindOf(kInvalidType)) {
		println(1, "Trying to cast from " + possible->describe() + " to " + required->describe(), node);
	}

	// In case the possible type is a 1-tuple and the required type is not, try
	// the implicit tuple access.
	if (actual->isKindOf(kInvalidType) && possible->isKindOf(kTupleType) && !required->isKindOf(kTupleType)) {
		const TupleType::Ptr& ptuple = TupleType::needFrom(possible);
		if (ptuple->getArgs().size() == 1) {
			println(1, "Implicitly accessing single field of 1-tuple " + possible->describe());

			OneTupleMappedType::Ptr type(new OneTupleMappedType);
			type->setTuple(ptuple);
			actual = type;
			// actual = match(ptuple->getArgs()[0], required, node);
		}
	}

	// Complain if the conversion was not possible.
	if (actual->isKindOf(kInvalidType)) {
		throw std::runtime_error("Unable to find satisfy " + possible->describe() + " and " + required->describe() + " at the same time.");
	}
	return actual;
}