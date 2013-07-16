/* Copyright © 2013 Fabian Schuiki */
#include "type.hpp"
#include <ast/nodes/ast.hpp>
#include <boost/pointer_cast.hpp>

using namespace ast;
using boost::shared_ptr;
using boost::dynamic_pointer_cast;

namespace stage {
namespace algorithm {
namespace type {


/**
 * Simplifies the given TypeSet by removing duplicate types. If the resulting
 * TypeSet contains only one type, that type is returned instead of the set.
 */
NodePtr simplify(const TypeSet::Ptr& input)
{
	// Remove duplicate types.
	NodeVector newTypes;
	const NodeVector& types = input->getTypes();
	for (NodeVector::const_iterator it = types.begin(); it != types.end(); it++) {
		bool exists = false;
		for (NodeVector::iterator is = newTypes.begin(); is != newTypes.end(); is++) {
			if (equal(*it, *is)) {
				exists = true;
				break;
			}
		}
		if (!exists) newTypes.push_back(*it);
	}
	assert(newTypes.size() <= types.size());
	assert(newTypes.empty() == types.empty());

	// Return either the new set or the only type left in the set, if there's one.
	if (newTypes.size() == 1) {
		return newTypes.front();
	}
	TypeSet::Ptr ts(new TypeSet);
	ts->setTypes(newTypes);
	return ts;
}


/**
 * Returns true if both defined types %a and %b point to the same type
 * definition, i.e. their type definitions have the same id.
 */
bool equal(const DefinedType::Ptr& a, const DefinedType::Ptr& b)
{
	return a->getDefinition()->getId() == b->getDefinition()->getId();
}

bool equal(const QualifiedType::Ptr& a, const QualifiedType::Ptr& b)
{
	// Treat the trivial cases where the number of fields does not match.
	const NodeVector& membersA = a->getMembers(), membersB = b->getMembers();
	if (membersA.size() != membersB.size()) return false;
	const NodeVector& funcsA = a->getFuncs(), funcsB = b->getFuncs();
	if (funcsA.size() != funcsB.size()) return false;

	// Check each member separately.
	for (NodeVector::const_iterator ia = membersA.begin(), ib = membersB.begin(); ia != membersA.end() && ib != membersB.end(); ia++, ib++) {
		const QualifiedTypeMember::Ptr& memberA = QualifiedTypeMember::needFrom(*ia), memberB = QualifiedTypeMember::needFrom(*ib);
		if (memberA->getName() != memberB->getName())
			return false;
		if (!equal(memberA->getType(), memberB->getType()))
			return false;
	}

	// TODO: do the same for interface stuff.
	return true;
}


/**
 * Returns the intersection between the TypeSet and the other node. The other
 * node may also be a type set, in which case this function is called
 * recursively to resolve the intersect.
 */
NodePtr intersect(const TypeSet::Ptr& typeSet, const NodePtr& other)
{
	// Intersect all types in the type set with the other type.
	NodeVector newTypes;
	const NodeVector& types = typeSet->getTypes();
	for (NodeVector::const_iterator it = types.begin(); it != types.end(); it++) {
		NodePtr type = intersect(*it, other);
		if (type->isKindOf(kInvalidType)) continue; // skip if the intersect was impossible
		bool exists = false;
		for (NodeVector::iterator is = newTypes.begin(); is != newTypes.end(); is++) {
			if (equal(type, *is)) {
				exists = true;
				break;
			}
		}
		if (!exists) newTypes.push_back(type);
	}

	// Return the new type set if it contains multiple types, a single type if
	// there's only one left after the intersect, or InvalidType if the
	// intersect yielded no types in the set.
	if (newTypes.empty()) {
		return NodePtr(new InvalidType);
	} else if (newTypes.size() == 1) {
		return newTypes.front();
	} else {
		TypeSet::Ptr ts(new TypeSet);
		ts->setTypes(newTypes);
		return ts;
	}
}


/**
 * @brief Tries to simplify the %input type by removing obsolete and redundant
 * information.
 */
NodePtr simplify(const NodePtr& input)
{
	if (const TypeSet::Ptr& t = TypeSet::from(input))
		return simplify(t);
	return input;
}

/**
 * @brief Returns whether the two types are equal.
 */
bool equal(const NodePtr& a, const NodePtr& b)
{
	// Treat combinations of defined types.
	DefinedType::Ptr defTypeA = DefinedType::from(a), defTypeB = DefinedType::from(b);
	if (defTypeA && defTypeB)
		return equal(defTypeA, defTypeB);
	if (defTypeA && !defTypeB)
		return equal(defTypeA->getDefinition(), b);
	if (!defTypeA && defTypeB)
		return equal(defTypeB->getDefinition(), a);

	// Resolve type defs.
	TypeDef::Ptr typedefA = TypeDef::from(a), typedefB = TypeDef::from(b);
	if (typedefA && typedefB)
		return equal(typedefA->getType()->needTypeExpr()->getEvaluatedType(), typedefB->getType()->needTypeExpr()->getEvaluatedType());
	if (typedefA && !typedefB)
		return equal(typedefA->getType()->needTypeExpr()->getEvaluatedType(), b);
	if (!typedefA && typedefB)
		return equal(a, typedefB->getType()->needTypeExpr()->getEvaluatedType());

	// Treat qualified types.
	QualifiedType::Ptr qualiTypeA = QualifiedType::from(a), qualiTypeB = QualifiedType::from(b);
	if (qualiTypeA && qualiTypeB)
		return equal(qualiTypeA, qualiTypeB);

	return false;
}

/**
 * @brief Tries to find the largest common type between types %a and %b.
 *
 * Returns an InvalidType if the intersect is impossible.
 */
NodePtr intersect(const NodePtr& a, const NodePtr& b)
{
	// Shortcut if both types are equal.
	if (equal(a,b)) return a;

	// Intersection between TypeSets or a TypeSet and other type.
	TypeSet::Ptr typeSetA = TypeSet::from(a), typeSetB = TypeSet::from(b);
	if (typeSetA && typeSetB) {
		return intersect(typeSetA, typeSetB);
	} else if (typeSetA && !typeSetB) {
		return intersect(typeSetA, b);
	} else if (!typeSetA && typeSetB) {
		return intersect(typeSetB, a);
	}

	return NodePtr(new InvalidType);
}

} // namespace type
} // namespace algorithm
} // namespace stage