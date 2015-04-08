/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "maxwell/ast/nodes/ast.hpp"
#include "maxwell/stage/algorithm/type.hpp"
#include <boost/pointer_cast.hpp>

using namespace ast;
using boost::shared_ptr;
using boost::dynamic_pointer_cast;

namespace stage {
namespace algorithm {
namespace type {


/**
 * Copies the entries of the input vector of types to the output vector,
 * omitting duplicate types. Useful for TypeSet and UnionType simplification.
 */
void copyUnique(const NodeVector& input, NodeVector& output)
{
	for (NodeVector::const_iterator it = input.begin(); it != input.end(); it++) {
		bool exists = false;
		for (NodeVector::iterator is = output.begin(); is != output.end(); is++) {
			if (equal(*it, *is)) {
				exists = true;
				break;
			}
		}
		if (!exists) output.push_back(*it);
	}
	assert(output.size() <= input.size());
	assert(output.empty() == input.empty());
}

/**
 * Simplifies the given TypeSet by removing duplicate types. If the resulting
 * TypeSet contains only one type, that type is returned instead of the set.
 */
NodePtr simplify(const TypeSet::Ptr& input)
{
	// Remove duplicate types.
	NodeVector newTypes;
	copyUnique(input->getTypes(), newTypes);

	// Return either the new set or the only type left in the set, if there's one.
	if (newTypes.size() == 1) {
		return newTypes.front();
	}
	TypeSet::Ptr ts(new TypeSet);
	ts->setTypes(newTypes);
	return ts;
}

/**
 * Simplifies the given UnionType by removing duplicate types. If the resulting
 * UnionType contains only one type, that type is returned instead of the union.
 */
NodePtr simplify(const UnionType::Ptr& input)
{
	// Remove duplicate types.
	NodeVector newTypes;
	copyUnique(input->getTypes(), newTypes);

	// Return either the new union or the only type left in the vector, if there's one.
	if (newTypes.size() == 1) {
		return newTypes.front();
	}
	UnionType::Ptr ut(new UnionType);
	ut->setTypes(newTypes);
	return ut;
}


/**
 * Returns true if both defined types %a and %b point to the same type
 * definition, i.e. their type definitions have the same id.
 */
bool equal(const DefinedType::Ptr& a, const DefinedType::Ptr& b)
{
	return a->getDefinition()->getId() == b->getDefinition()->getId();
}

/**
 * Returns true if both qualified types %a and %b are equivalent, i.e. have the
 * same members, interfaces, ranges and native type equivalents.
 */
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
 * Returns true if the types in vector %a are all present in %b, and vice versa.
 * Useful for equality checks on TypeSet and UnionType nodes. The algorithm is
 * quite allergic to vectors that contain duplicate types.
 */
bool equalTypes(const NodeVector& a, const NodeVector& b)
{
	// Catch the trivial case of vectors that are not of equal length.
	if (a.size() != b.size()) return false;

	// Iterate through the first vector, counting the removed nodes in the other.
	// If a node cannot be found in the other, equality fails. If any nodes are
	// left in the other afterwards, equality fails as well.
	int found = 0;
	for (NodeVector::const_iterator ia = a.begin(); ia != a.end(); ia++) {
		bool anythingFound = false;
		for (NodeVector::const_iterator ib = b.begin(); ib != b.end(); ib++) {
			if (equal(*ia,*ib)) {
				found++;
				anythingFound = true;
			}
		}
		if (!anythingFound) return false; // since *ia is not present in b
	}

	// If 'found' does not equal b's length, there are elements left in
	// b that were not present in a, in which case the equality fails.
	return (found == b.size());
}

/**
 * Returns true if all types in TypeSet %a are also contained in %b, and vice
 * versa.
 */
bool equal(const TypeSet::Ptr& a, const TypeSet::Ptr& b)
{
	return equalTypes(a->getTypes(), b->getTypes());
}

/**
 * Returns true if all types in the UnionType %a are also contained in %b, and
 * vice versa.
 */
bool equal(const UnionType::Ptr& a, const UnionType::Ptr& b)
{
	return equalTypes(a->getTypes(), b->getTypes());
}

/**
 * Returns true if the type as well as the arguments of the specialization are
 * identical.
 */
bool equal(const SpecializedType::Ptr& a, const SpecializedType::Ptr& b)
{
	if (!equal(a->getType(), b->getType())) return false;
	const NodeVector& typesA = a->getSpecs();
	const NodeVector& typesB = b->getSpecs();
	if (typesA.size() != typesB.size()) return false;
	for (int i = 0; i < typesA.size(); i++) {
		if (!equal(typesA[i], typesB[i]))
			return false;
	}
	return true;
}

/**
 * Returns true if both sides of the function mapping are identical.
 */
bool equal(const FuncType::Ptr& a, const FuncType::Ptr& b)
{
	if (!equal(a->getIn(), b->getIn())) return false;
	if (!equal(a->getOut(), b->getOut())) return false;
	return true;
}

/**
 * Returns true if both tuples have the same fields, in the same order, with
 * the same names and same types.
 */
bool equal(const TupleType::Ptr& a, const TupleType::Ptr& b)
{
	const NodeVector& argsA = a->getArgs();
	const NodeVector& argsB = b->getArgs();
	if (argsA.size() != argsB.size())
		return false;

	for (NodeVector::const_iterator ia = argsA.begin(), ib = argsB.begin(); ia != argsA.end() && ib != argsB.end(); ia++, ib++) {
		const TupleTypeArg::Ptr& argA = TupleTypeArg::from(*ia);
		const TupleTypeArg::Ptr& argB = TupleTypeArg::from(*ib);
		if (!argA || !argB) return false;
		if (argA->getName(false) != argB->getName(false)) return false;
		if (!equal(argA->getType(), argB->getType())) return false;
	}
	return true;
}

/**
 * Returns true if both native types %a and %b are equivalent, i.e. their
 * segments are identical.
 */
bool equal(const NativeType::Ptr& a, const NativeType::Ptr& b) {
	return a->getSegments() == b->getSegments();
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
	if (const TypeSet::Ptr& t = TypeSet::from(input)) return simplify(t);
	if (const UnionType::Ptr& t = UnionType::from(input)) return simplify(t);
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
		return equal(defTypeA, defTypeB) || equal(defTypeA->getDefinition(), defTypeB->getDefinition());
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

	// Treat type sets and unions.
	TypeSet::Ptr typeSetA = TypeSet::from(a), typeSetB = TypeSet::from(b);
	if (typeSetA && typeSetB)
		return equal(typeSetA, typeSetB);
	UnionType::Ptr unionTypeA = UnionType::from(a), unionTypeB = UnionType::from(b);
	if (unionTypeA && unionTypeB)
		return equal(unionTypeA, unionTypeB);

	// Treat specialized types.
	SpecializedType::Ptr specTypeA = SpecializedType::from(a), specTypeB = SpecializedType::from(b);
	if (specTypeA && specTypeB)
		return equal(specTypeA, specTypeB);

	// Treat function types.
	FuncType::Ptr funcTypeA = FuncType::from(a), funcTypeB = FuncType::from(b);
	if (funcTypeA && funcTypeB)
		return equal(funcTypeA, funcTypeB);

	// Treat tuple types.
	TupleType::Ptr tupleTypeA = TupleType::from(a), tupleTypeB = TupleType::from(b);
	if (tupleTypeA && tupleTypeB)
		return equal(tupleTypeA, tupleTypeB);

	// Treat native types.
	auto nativeTypeA = NativeType::from(a);
	auto nativeTypeB = NativeType::from(b);
	if (nativeTypeA && nativeTypeB)
		return equal(nativeTypeA, nativeTypeB);

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

/**
 * @brief Resolves named types for their type definition.
 *
 * If r is a null pointer or not a named type, returns r.
 */
NodePtr resolve(const NodePtr& r)
{
	if (!r || !r->isKindOf(kDefinedType))
		return r;

	const auto& def = DefinedType::needFrom(r)->getDefinition();
	if (const auto& ntd = NativeTypeDef::from(def))
		return resolve(ntd->getType()->needTypeExpr()->getEvaluatedType());

	const auto& td = TypeDef::needFrom(def);
	return resolve(td->getType()->needTypeExpr()->getEvaluatedType());
}

NodePtr ignoreMapped(const NodePtr& in)
{
	if (const UnionMappedType::Ptr& type = UnionMappedType::from(in))
		return type->getIn();
	return in;
}

NodePtr acceptMapped(const NodePtr& in)
{
	if (const UnionMappedType::Ptr& type = UnionMappedType::from(in))
		return type->getOut();
	return in;
}

} // namespace type
} // namespace algorithm
} // namespace stage
