/* Copyright © 2013 Fabian Schuiki */
#pragma once

namespace ast {

/**
 * @brief Base class for all nodes in the abstract syntax tree.
 */
class Node
{
public:
	Node() : modified(false) {}

	/// Overridden by subclasses to indicate what type of node they are.
	virtual bool isKindOf(Kind k) { return false; }

protected:
	bool modified;

	/**
	 * @brief Called by subclasses when the node is modified and needs to be persisted.
	 *
	 * The modification is propagated to the parent nodes.
	 */
	void modify()
	{
		if (!modified) {
			modified = true;
		}
	}
};

} // namespace ast