/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "QualifiedTypeNative.hpp"
#include "ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::QualifiedTypeNative;
using ast::NodePtr;
using ast::NodeVector;

QualifiedTypeNative::QualifiedTypeNative() : Node(),
	interfaceNamed(this) {}

bool QualifiedTypeNative::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kQualifiedTypeNative;
}

bool QualifiedTypeNative::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kNamedInterface) return true;
	return false;
}

NodePtr QualifiedTypeNative::copy() {
	Ptr c (new QualifiedTypeNative);
	Node::copy(this->name, c->name);
	return c;
}

bool QualifiedTypeNative::equalTo(const NodePtr& o) {
	const shared_ptr<QualifiedTypeNative>& other = boost::dynamic_pointer_cast<QualifiedTypeNative>(o);
	if (!other) return false;
	if (!equal(this->name, other->name)) return false;
	return true;
}

std::string QualifiedTypeNative::describe(int depth) {
	std::stringstream str, b;
	str << "native " << name;
	return str.str();
}


void QualifiedTypeNative::setName(const std::string& v) {
	if (!equal(v, name)) {
		modify("name");
		name = v;
	}
}

const std::string& QualifiedTypeNative::getName(bool required) {
	const std::string& v = name;
	if (required && v.empty()) {
		throw std::runtime_error("Node " + getId().str() + " is required to have a non-empty string name set.");
	}
	return v;
}


void QualifiedTypeNative::encode(Encoder& e) {
	e.encode(this->name);
}

void QualifiedTypeNative::decode(Decoder& d) {
	d.decode(this->name);
}


void QualifiedTypeNative::updateHierarchyOfChildren() {
}

const NodePtr& QualifiedTypeNative::resolvePath(const std::string& path) {
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

