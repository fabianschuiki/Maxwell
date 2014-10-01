/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "maxwell/ast/nodes/TupleType.hpp"
#include "maxwell/ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::TupleType;
using ast::NodePtr;
using ast::NodeVector;

TupleType::TupleType() : Node() {}

bool TupleType::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kTupleType;
}

bool TupleType::implements(Interface i) {
	if (Node::implements(i)) return true;
	return false;
}

NodePtr TupleType::copy() {
	Ptr c (new TupleType);
	Node::copy(this->args, c->args);
	return c;
}

bool TupleType::equalTo(const NodePtr& o) {
	const shared_ptr<TupleType>& other = boost::dynamic_pointer_cast<TupleType>(o);
	if (!other) return false;
	if (!equal(this->args, other->args)) return false;
	return true;
}

std::string TupleType::describe(int depth) {
	std::stringstream str, b;
				bool first = true;			str << "(";			for (NodeVector::iterator it = args.begin(); it != args.end(); it++) {				if (!first) str << ", ";				first = false;				str << (*it)->describe(depth-1);			}			str << ")";
	return str.str();
}


void TupleType::setArgs(const NodeVector& v) {
	if (!equal(v, args)) {
		modify("args");
		args = v;
	}
}

const NodeVector& TupleType::getArgs(bool required) {
	const NodeVector& v = args;
	return v;
}


void TupleType::encode(Encoder& e) {
	e.encode(this->args);
}

void TupleType::decode(Decoder& d) {
	d.decode(this->args);
}


void TupleType::updateHierarchyOfChildren() {
	for (unsigned i = 0; i < this->args.size(); i++) {
		char buf[32]; snprintf(buf, 31, "%i", i);
		this->args[i]->updateHierarchy((id + "args") + buf, repository, this);
	}
}

const NodePtr& TupleType::resolvePath(const std::string& path) {
	size_t size = path.size();
	// args.*
	if (size >= 4 && path[0] == 'a' && path[1] == 'r' && path[2] == 'g' && path[3] == 's') {
		// args
		if (size == 4) {
			throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
		} else if (path[4] == '.') {
			size_t dot = path.find(".", 5);
			string idx_str = path.substr(5, dot);
			int idx = atoi(idx_str.c_str());
			const NodeVector& a = getArgs();
			if (idx < 0 || idx >= (int)a.size()) {
				throw std::runtime_error("Index into array '" + path.substr(0, 4) + "' is out of bounds.");
			}
			if (dot == string::npos) {
				return a[idx];
			} else {
				return a[idx]->resolvePath(path.substr(dot + 1));
			}
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector TupleType::getChildren() {
	NodeVector v;
	v.insert(v.end(), this->args.begin(), this->args.end());
	return v;
}

