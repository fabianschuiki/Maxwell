/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <string>
#include <sstream>

namespace ast {

using std::string;
using std::stringstream;

/**
 * @brief Full id of a single node.
 *
 * In general of the form <source>.<root>.<id>, where source is the id of the
 * source file that spawned the node, root is the unique id of the root node
 * within the file and id is path from the root to the node.
 */
class NodeId
{
public:
	int source;
	int root;
	string id;

	NodeId();
	NodeId(int source, int root, string id = "");

	bool operator<(const NodeId& other) const;
	bool operator==(const NodeId& other) const;
	bool operator!=(const NodeId& other) const { return !(*this == other); }

	string str() const;
	operator string() const { return str(); }
	const char* c_str() const { return str().c_str(); }

	NodeId getRoot() const;

	/// Returns whether this id points to a root node, i.e. has the form <source>.<root>
	bool isRoot() const { return id.empty(); }
	/// Returns whether this id points to a builtin node, i.e. has the form 0.<root>
	bool isBuiltin() const { return source == 0; }
	/// Returns whether this id is empty.
	bool empty() const { return root == 0; }
};

std::ostream& operator<<(std::ostream& s, const NodeId& id);

/**
 * @brief Base class for all nodes in the abstract syntax tree.
 */
class Node
{
public:
	Node();

	/// Overridden by subclasses to indicate what type of node they are.
	virtual bool isKindOf(Kind k) { return false; }

	/// Returns a description of this node and all its subnodes for debugging purposes.
	virtual string describe(int depth = -1) { return "Node"; }

	const NodeId& getId() const;
	void setId(const NodeId& i);

protected:
	bool modified;
	NodeId id;

	void modify();
	string indent(string in);
};

} // namespace ast