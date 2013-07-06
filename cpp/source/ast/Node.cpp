/* Copyright © 2013 Fabian Schuiki */
#include "Node.hpp"
#include "Repository.hpp"
#include <stdexcept>
#include <sstream>

using ast::Node;
using ast::NodeId;
using ast::NodeVector;
using ast::Repository;
using std::string;
using std::stringstream;

NodeId::NodeId() : source(0), root(0) {}
NodeId::NodeId(int source, int root, string id) : source(source), root(root), id(id) {}

NodeId::NodeId(string str)
{
	size_t firstDot = str.find('.');
	if (firstDot == string::npos || firstDot == 0 || firstDot == str.size()-1) {
		throw std::runtime_error("Invalid node id '" + str + "'. Must be of form <source>.<root>[.<id>].");
	}
	size_t secondDot = str.find('.', firstDot + 1);
	source = atoi(str.substr(0, firstDot).c_str());
	root = atoi(str.substr(firstDot+1, secondDot).c_str());
	if (secondDot != string::npos) {
		id = str.substr(secondDot+1);
	}
}

bool NodeId::operator<(const NodeId& other) const
{
	if (source < other.source) return true;
	if (source > other.source) return false;
	if (root < other.root) return true;
	if (root > other.root) return false;
	return id < other.id;
}

bool NodeId::operator==(const NodeId& other) const
{
	return (source == other.source && root == other.root && id == other.id);
}

string NodeId::str() const
{
	stringstream s;
	s << source << '.' << root;
	if (!id.empty()) s << '.' << id;
	return s.str();
}

/**
 * @brief Returns the NodeId of the root node containing this node.
 *
 * Basically returns the node id <source>.<root>, with the id portion omitted.
 */
NodeId NodeId::getRoot() const
{
	if (id.empty())
		return *this;
	return NodeId(source, root);
}

/// Allows NodeId objects to be written directly to output streams.
std::ostream& ast::operator<<(std::ostream& s, const NodeId& id)
{
	s << id.str();
	return s;
}


Node::Node()
{
	modified = false;
}

/**
 * @brief Sets the node's id, parent and repository in one go.
 *
 * Note that this may also alter the node's children.
 */
void Node::updateHierarchy(const NodeId& id, const weak_ptr<Repository>& repository, const weak_ptr<Node>& parent)
{
	this->id = id;
	this->parent = parent;
	this->repository = repository;
}

/**
 * @brief Called by subclasses when the node is modified and needs to be persisted.
 *
 * The modification is propagated to the parent nodes.
 */
void Node::modify()
{
	shared_ptr<Repository> r(repository.lock());
	shared_ptr<Node> p(parent.lock());

	if (!modified && r) {
		modified = true;
		if (p) {
			p->modify();
		} else {
			r->markModified(id);
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