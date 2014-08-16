/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "maxwell/ast/nodes/InterfaceQualifier.hpp"
#include "maxwell/ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::InterfaceQualifier;
using ast::NodePtr;
using ast::NodeVector;

InterfaceQualifier::InterfaceQualifier() : Node(),
	interfaceGraph(this) {}

bool InterfaceQualifier::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kInterfaceQualifier;
}

bool InterfaceQualifier::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kGraphInterface) return true;
	return false;
}

NodePtr InterfaceQualifier::copy() {
	Ptr c (new InterfaceQualifier);
	Node::copy(this->graphPrev, c->graphPrev);
	Node::copy(this->stmts, c->stmts);
	return c;
}

bool InterfaceQualifier::equalTo(const NodePtr& o) {
	const shared_ptr<InterfaceQualifier>& other = boost::dynamic_pointer_cast<InterfaceQualifier>(o);
	if (!other) return false;
	if (!equal(this->graphPrev, other->graphPrev)) return false;
	if (!equal(this->stmts, other->stmts)) return false;
	return true;
}

std::string InterfaceQualifier::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "InterfaceQualifier{…}";
	str << "InterfaceQualifier{";
	if (this->graphPrev) b << "\n  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
	if (!this->stmts.empty()) b << "\n  \033[1mstmts\033[0m = " << indent(describeVector(this->stmts, depth-1));
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void InterfaceQualifier::setGraphPrev(const NodePtr& v) {
	if (!v && graphPrev) {
		modify("graphPrev");
		graphPrev.reset();
	}
	if (!graphPrev || v->getId() != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

void InterfaceQualifier::setGraphPrev(const NodeId& v) {
	if (v != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

const NodePtr& InterfaceQualifier::getGraphPrev(bool required) {
	const NodePtr& v = graphPrev.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
	}
	return v;
}


void InterfaceQualifier::setStmts(const NodeVector& v) {
	if (!equal(v, stmts)) {
		modify("stmts");
		stmts = v;
	}
}

const NodeVector& InterfaceQualifier::getStmts(bool required) {
	const NodeVector& v = stmts;
	return v;
}


void InterfaceQualifier::encode(Encoder& e) {
	e.encode(this->graphPrev);
	e.encode(this->stmts);
}

void InterfaceQualifier::decode(Decoder& d) {
	d.decode(this->graphPrev);
	d.decode(this->stmts);
}


void InterfaceQualifier::updateHierarchyOfChildren() {
	for (int i = 0; i < this->stmts.size(); i++) {
		char buf[32]; snprintf(buf, 31, "%i", i);
		this->stmts[i]->updateHierarchy((id + "stmts") + buf, repository, this);
	}
}

const NodePtr& InterfaceQualifier::resolvePath(const std::string& path) {
	size_t size = path.size();
	// .*
	if (true) {
		// graphPrev.*
		if (size >= 9 && path[0] == 'g' && path[1] == 'r' && path[2] == 'a' && path[3] == 'p' && path[4] == 'h' && path[5] == 'P' && path[6] == 'r' && path[7] == 'e' && path[8] == 'v') {
			// graphPrev
			if (size == 9) {
				return getGraphPrev();
			} else if (path[9] == '.') {
				return getGraphPrev()->resolvePath(path.substr(10));
			}
		}
		// stmts.*
		if (size >= 5 && path[0] == 's' && path[1] == 't' && path[2] == 'm' && path[3] == 't' && path[4] == 's') {
			// stmts
			if (size == 5) {
				throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
			} else if (path[5] == '.') {
				size_t dot = path.find(".", 6);
				string idx_str = path.substr(6, dot);
				int idx = atoi(idx_str.c_str());
				const NodeVector& a = getStmts();
				if (idx < 0 || idx >= a.size()) {
					throw std::runtime_error("Index into array '" + path.substr(0, 5) + "' is out of bounds.");
				}
				if (dot == string::npos) {
					return a[idx];
				} else {
					return a[idx]->resolvePath(path.substr(dot + 1));
				}
			}
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector InterfaceQualifier::getChildren() {
	NodeVector v;
	v.insert(v.end(), this->stmts.begin(), this->stmts.end());
	return v;
}
