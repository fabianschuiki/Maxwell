/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <string>
#include <iostream>

namespace ast {

using std::string;

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
	NodeId(string str);

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

	// Resets this id to empty.
	void clear() { source = 0; root = 0; id.clear(); }

	NodeId operator+(string s) const { return NodeId(source, root, id.empty() ? s : id + '.' + s); }
	NodeId operator+(const char* s) const { return *this + string(s); }
};

std::ostream& operator<<(std::ostream& s, const NodeId& id);

} // namespace ast