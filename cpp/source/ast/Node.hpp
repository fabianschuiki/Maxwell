/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <string>

namespace ast {

using std::string;

/**
 * @brief Base class for all nodes in the abstract syntax tree.
 */
class Node
{
public:
	Node() : modified(false) {}

	/// Overridden by subclasses to indicate what type of node they are.
	virtual bool isKindOf(Kind k) { return false; }

	/// Returns a description of this node and all its subnodes for debugging purposes.
	virtual string describe(int depth = -1) { return "Node"; }

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

	/**
	 * @brief Returns an indented version of the input string.
	 *
	 * This function basically puts two spaces after each newline character.
	 */
	string indent(string in)
	{
		string out;
		for (string::iterator it = in.begin(); it != in.end(); it++) {
			out += *it;
			if (*it == '\n')
				out += "  ";
		}
		return out;
	}
};

} // namespace ast