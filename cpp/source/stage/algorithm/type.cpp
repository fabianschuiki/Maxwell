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
	DefinedType::Ptr defTypeA = DefinedType::from(a), defTypeB = DefinedType::from(b);
	if (defTypeA && defTypeB)
		return equal(defTypeA, defTypeB);
	return false;
}

} // namespace type
} // namespace algorithm
} // namespace stage