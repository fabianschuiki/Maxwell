/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "nodes/types.hpp" // for ast::Kind
#include <string>
#include <vector>
#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace ast {

using std::string;
using std::vector;
using boost::shared_ptr;
using boost::weak_ptr;

class Encoder;
class Decoder;
class Repository;

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

/**
 * @brief Base class for all nodes in the abstract syntax tree.
 */
class Node : public boost::enable_shared_from_this<Node>
{
public:
	Node();

	/// Overridden by subclasses to indicate a node reference.
	virtual bool isReference() { return false; }

	/// Overridden by subclasses to indicate what type of node they are.
	virtual bool isKindOf(Kind k) { return false; }

	/// Returns a description of this node and all its subnodes for debugging purposes.
	virtual string describe(int depth = -1) { return "Node"; }

	/// Returns the class name of this node used in serialization.
	virtual string getClassName() const = 0;

	/// Overridden by subclasses to encode their member variables.
	virtual void encode(Encoder& e) = 0;
	/// Overridden by subclasses to reconstruct their member variables.
	virtual void decode(Decoder& d) = 0;

	/// Overridden by subclasses to descend into the tree to lookup a node.
	virtual const shared_ptr<Node>& resolvePath(const string& path) = 0;

	/// Returns the node's id.
	const NodeId& getId() const { return id; }
	/// Returns the node's parent node, or an empty weak_ptr if this is a root node.
	const weak_ptr<Node>& getParent() const { return parent; }
	/// Returns the node's repository, or an empty weak_ptr if it is not part of one.
	const weak_ptr<Repository>& getRepository() const { return repository; }

	virtual void updateHierarchy(const NodeId& id, const weak_ptr<Repository>& repository = weak_ptr<Repository>(), const weak_ptr<Node>& parent = weak_ptr<Node>());

protected:
	bool modified;
	NodeId id;
	weak_ptr<Node> parent;
	weak_ptr<Repository> repository;

	void modify();
	string indent(string in);

	string describeVector(const vector<shared_ptr<Node> >& nodes, int depth = -1);
	shared_ptr<Node> resolveReference(const NodeId& id);
};

typedef shared_ptr<Node> NodePtr;
typedef vector<NodePtr> NodeVector;

/// A special subclass of Node that acts as a placeholder for another node.
/*class NodeReference : public Node
{
public:
	virtual string getClassName() const { throw std::runtime_error("Calling getClassName() on a NodeReference does not make sense."); }
	virtual void encode(Encoder& e) { throw std::runtime_error("Calling encode() on a NodeReference does not make sense."); }
	virtual void decode(Decoder& d) { throw std::runtime_error("Calling decode() on a NodeReference does not make sense."); }
};*/

} // namespace ast