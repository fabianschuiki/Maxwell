/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "maxwell/ast/nodes/DefinedType.hpp"
#include "maxwell/ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::DefinedType;
using ast::NodePtr;
using ast::NodeVector;

DefinedType::DefinedType() : Node() {}

bool DefinedType::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kDefinedType;
}

bool DefinedType::implements(Interface i) {
	if (Node::implements(i)) return true;
	return false;
}

NodePtr DefinedType::copy() {
	Ptr c (new DefinedType);
	Node::copy(this->definition, c->definition);
	return c;
}

bool DefinedType::equalTo(const NodePtr& o) {
	const shared_ptr<DefinedType>& other = boost::dynamic_pointer_cast<DefinedType>(o);
	if (!other) return false;
	if (!equal(this->definition, other->definition)) return false;
	return true;
}

std::string DefinedType::describe(int depth) {
	std::stringstream str, b;
	str << (getDefinition()->implements(kNamedInterface) ? getDefinition()->needNamed()->getName() : getDefinition()->getId().str());
	return str.str();
}


void DefinedType::setDefinition(const NodePtr& v) {
	if (!v && definition) {
		modify("definition");
		definition.reset();
	}
	if (!definition || v->getId() != definition.id) {
		modify("definition");
		definition.set(v);
	}
}

void DefinedType::setDefinition(const NodeId& v) {
	if (v != definition.id) {
		modify("definition");
		definition.set(v);
	}
}

const NodePtr& DefinedType::getDefinition(bool required) {
	const NodePtr& v = definition.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have definition set to a non-null value.");
	}
	return v;
}


void DefinedType::encode(Encoder& e) {
	e.encode(this->definition);
}

void DefinedType::decode(Decoder& d) {
	d.decode(this->definition);
}


void DefinedType::updateHierarchyOfChildren() {
}

const NodePtr& DefinedType::resolvePath(const std::string& path) {
	size_t size = path.size();
	// definition.*
	if (size >= 10 && path[0] == 'd' && path[1] == 'e' && path[2] == 'f' && path[3] == 'i' && path[4] == 'n' && path[5] == 'i' && path[6] == 't' && path[7] == 'i' && path[8] == 'o' && path[9] == 'n') {
		// definition
		if (size == 10) {
			return getDefinition();
		} else if (path[10] == '.') {
			return getDefinition()->resolvePath(path.substr(11));
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}
