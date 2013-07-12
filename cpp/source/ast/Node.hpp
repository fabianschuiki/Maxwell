/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "nodes/types.hpp" // for ast::Kind
#include "nodes/BaseNode.hpp" // for ast::BaseNode
#include "NodeId.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace ast {

using std::string;
using std::vector;
using boost::shared_ptr;

class Encoder;
class Decoder;
class Repository;

/**
 * @brief Base class for all nodes in the abstract syntax tree.
 */
class Node : public boost::enable_shared_from_this<Node>, public BaseNode
{
public:
	Node();

	/// Overridden by subclasses to indicate a node reference.
	virtual bool isReference() { return false; }

	/// Overridden by subclasses to indicate what type of node they are.
	virtual bool isKindOf(Kind k) { return false; }
	/// Overridden by subclasses to indicate what interfaces they implement.
	virtual bool implements(Interface i) { return false; }

	/// Returns a description of this node and all its subnodes for debugging purposes.
	virtual string describe(int depth = -1) { return "Node"; }

	/// Returns the class name of this node used in serialization.
	virtual string getClassName() const = 0;

	/// Overridden by subclasses to encode their member variables.
	virtual void encode(Encoder& e) = 0;
	/// Overridden by subclasses to reconstruct their member variables.
	virtual void decode(Decoder& d) = 0;

	/// Overridden by subclasses to contain child nodes.
	virtual vector<shared_ptr<Node> > getChildren() { return vector<shared_ptr<Node> >(); }

	/// Overridden by subclasses to descend into the tree to lookup a node.
	virtual const shared_ptr<Node>& resolvePath(const string& path) = 0;

	/// Returns the node's id.
	const NodeId& getId() const { return id; }
	/// Returns the node's parent node, or an empty pointer if this is a root node.
	Node* getParent() const { return parent; }
	/// Returns the node's repository, or an empty pointer if it is not part of one.
	Repository* getRepository() const { return repository; }

	virtual void updateHierarchy(const NodeId& id, Repository* repository = NULL, Node* parent = NULL);
	/// Overridden by subclasses to propagate hierarchy changes to child nodes.
	virtual void updateHierarchyOfChildren() {}

protected:
	bool modified;
	NodeId id;
	Node* parent;
	Repository* repository;

	void modify();
	string indent(string in);

	string describeVector(const vector<shared_ptr<Node> >& nodes, int depth = -1);
};

typedef shared_ptr<Node> NodePtr;
typedef vector<NodePtr> NodeVector;

/**
 * @brief Reference to another node in the repository.
 *
 * A NodeRef acts a special node wrapping a by-id-reference to another node
 * in the NodeRef's repository. Concrete nodes should be aware of this class
 * and transparently use get() to resolve the reference.
 */
class NodeRef
{
public:
	NodeRef() {}
	NodeRef(const NodeId& id) : id(id) {}

	NodeId id;
	NodePtr resolved;

	const NodePtr& get(Repository* repository);
	void set(const NodePtr& node);
	void set(const NodeId& id);
	void reset();
	bool empty() const { return id.empty(); }
	operator bool() const { return !id.empty(); }
};

} // namespace ast