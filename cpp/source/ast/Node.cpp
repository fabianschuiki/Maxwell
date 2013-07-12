/* Copyright © 2013 Fabian Schuiki */
#include "Node.hpp"
#include "Repository.hpp"
#include <stdexcept>
#include <sstream>

using ast::Node;
using ast::NodePtr;
using ast::NodeRef;
using ast::NodeId;
using ast::NodeVector;
using ast::Repository;
using std::string;
using std::stringstream;

Node::Node()
{
	modified = false;
	repository = NULL;
	parent = NULL;
}

/**
 * @brief Sets the node's id, parent and repository in one go.
 *
 * Note that this may also alter the node's children.
 */
void Node::updateHierarchy(const NodeId& id, Repository* repository, Node* parent)
{
	this->id = id;
	this->parent = parent;
	this->repository = repository;
	updateHierarchyOfChildren(); // gives subclasses the chance to update their child hierarchies
}

/**
 * @brief Called by subclasses when the node is modified and needs to be persisted.
 *
 * The modification is propagated to the parent nodes.
 */
void Node::modify()
{
	if (!modified && repository) {
		modified = true;
		if (parent) {
			parent->modify();
		} else {
			repository->markModified(id);
		}
	}
}

/**
 * @brief Returns an indented version of the input string.
 *
 * This function basically puts two spaces after each newline character.
 */
string Node::indent(string in)
{
	string out;
	for (string::iterator it = in.begin(); it != in.end(); it++) {
		out += *it;
		if (*it == '\n')
			out += "  ";
	}
	return out;
}

/**
 * @brief Helper function that describes a NodeVector.
 */
string Node::describeVector(const NodeVector& nodes, int depth)
{
	if (depth == 0) {
		return "[…]";
	}
	stringstream out;
	out << "[";
	for (NodeVector::const_iterator it = nodes.begin(); it != nodes.end(); it++) {
		out << "\n  - " << indent((*it)->describe(depth-1));
	}
	if (!nodes.empty())
		out << "\n";
	out << "]";
	return out.str();
}

/**
 * @brief Returns the referenced node, resolving it if necessary.
 */
const NodePtr& NodeRef::get(Repository* repository)
{
	if (!resolved && !id.empty()) {
		if (!repository) {
			throw std::runtime_error("Resolving reference to node '" + id.str() + "' without a repository to query for the instance.");
		}
		resolved = repository->getNode(id);
	}
	return resolved;
}

/**
 * @brief Sets the referenced node.
 */
void NodeRef::set(const NodePtr& node)
{
	if (resolved != node) {
		resolved = node;
		if (node) {
			id = node->getId();
		} else {
			id.clear();
		}
	}
}

/**
 * @brief Sets the referenced node's id.
 */
void NodeRef::set(const NodeId& id)
{
	if (this->id != id) {
		this->id = id;
		resolved.reset();
	}
}

/**
 * @brief Resets the reference to empty.
 */
void NodeRef::reset()
{

}