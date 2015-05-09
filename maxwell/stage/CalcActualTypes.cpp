/* Copyright (c) 2013 Fabian Schuiki */
#include "maxwell/stage/stages.hpp"
#include "maxwell/stage/algorithm/type.hpp"
#include <boost/lexical_cast.hpp>
#include <iostream>

using namespace ast;
using stage::CalcActualTypes;
using boost::lexical_cast;

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

	// See whether a change in mutability is required.
	if (actual->isKindOf(kInvalidType)) {
		if (auto possibleMut = MutableType::from(possible)) {
			// std::cerr << possible->describe() << " needs to be made immutable\n";
			ImmutableCastType::Ptr type(new ImmutableCastType);
			type->setIn(possible);
			actual = type;
		}
		else if (auto requiredMut = MutableType::from(required)) {
			// std::cerr << possible->describe() << " needs to be made mutable\n";
			MutableCastType::Ptr type(new MutableCastType);
			type->setIn(possible);
			actual = type;
		}
	}

	// Otherwise simply try to go with a regular cast.
	if (actual->isKindOf(kInvalidType)) {
		println(1, "Trying to cast from " + possible->describe() + " to " + required->describe(), node);

		// Assemble a list of available cast functions.
		NodePtr current(node->needGraph()->getGraphPrev());

		set<NodeId> castIds;
		while (current) {
			if (const FuncDef::Ptr& def = FuncDef::from(current)) {
				if (def->getName() == "cast") {
					castIds.insert(def->getId());
				}
			}
			current = current->asGraph()->getGraphPrev(false);
		}

		const Repository::ExternalNames& externals = repository.getExternalNamesForNodeId(node->getId());
		for (Repository::ExternalNames::const_iterator it = externals.begin(); it != externals.end(); it++) {
			if (it->second == "cast") {
				castIds.insert(it->first);
			}
		}

		// Filter the list of casts such that only the type-compatible ones remain.
		vector<CastType::Ptr> casts;
		for (set<NodeId>::iterator it = castIds.begin(); it != castIds.end(); it++) {

			// Lookup the cast function and find the input and output types.
			const FuncDef::Ptr& func = FuncDef::needFrom(repository.getNode(*it));
			const FuncType::Ptr& funcType = FuncType::needFrom(func->getType());
			const TupleType::Ptr& inTupleType = TupleType::from(funcType->getIn());
			const TupleType::Ptr& outTupleType = TupleType::from(funcType->getOut());

			if (!inTupleType || !outTupleType) continue; // ignore non-tuple types
			if (inTupleType->getArgs().size() != 1 || outTupleType->getArgs().size() != 1)
				continue; // ignore casts that have more or less than 1 input/output

			const NodePtr& inType = TupleTypeArg::needFrom(inTupleType->getArgs().front())->getType();
			const NodePtr& outType = TupleTypeArg::needFrom(outTupleType->getArgs().front())->getType();

			// Find the intersection between the possible and input, and the required and output type.
			NodePtr inPossible = algorithm::type::intersect(possible, inType);
			NodePtr outRequired = algorithm::type::intersect(required, outType);

			// If the cast is possible, i.e. none of the types is the InvalidType, keep the cast around.
			if (!inPossible->isKindOf(kInvalidType) && !outRequired->isKindOf(kInvalidType)) {
				CastType::Ptr c(new CastType);
				c->setIn(inPossible);
				c->setOut(outRequired);
				c->setFunc(func);
				casts.push_back(c);
			}
		}

		// Pick one of the casts found.
		if (casts.size() == 1) {
			actual = casts.front();
		} else if (casts.size() > 1) {
			throw std::runtime_error(lexical_cast<string>(casts.size()) + " casts viable from " + possible->describe() + " to " + required->describe() + ".");
		}
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
	// if (actual->isKindOf(kInvalidType)) {
	// 	throw std::runtime_error("Unable to find satisfy " + possible->describe() + " and " + required->describe() + " at the same time.");
	// }
	return actual;
}
