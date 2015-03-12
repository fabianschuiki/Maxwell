/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "maxwell/ast/nodes/TypeDef.hpp"
#include "maxwell/ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::TypeDef;
using ast::NodePtr;
using ast::NodeVector;

TypeDef::TypeDef() : Node(),
	interfaceCallable(this),
	interfaceGraph(this),
	interfaceNamed(this) {}

bool TypeDef::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kTypeDef;
}

bool TypeDef::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kCallableInterface) return true;
	if (i == kGraphInterface) return true;
	if (i == kNamedInterface) return true;
	return false;
}

NodePtr TypeDef::copy() {
	Ptr c (new TypeDef);
	Node::copy(this->graphPrev, c->graphPrev);
	Node::copy(this->name, c->name);
	Node::copy(this->type, c->type);
	return c;
}

bool TypeDef::equalTo(const NodePtr& o) {
	const shared_ptr<TypeDef>& other = boost::dynamic_pointer_cast<TypeDef>(o);
	if (!other) return false;
	if (!equal(this->graphPrev, other->graphPrev)) return false;
	if (!equal(this->name, other->name)) return false;
	if (!equal(this->type, other->type)) return false;
	return true;
}

std::string TypeDef::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "TypeDef{…}";
	str << "TypeDef{";
	if (this->graphPrev) b << "\n  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
	if (!this->name.empty()) b << "\n  \033[1mname\033[0m = \033[33m\"" << this->name << "\"\033[0m";
	if (this->type) b << "\n  \033[1mtype\033[0m = " << indent(this->type->describe(depth-1));
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void TypeDef::setGraphPrev(const NodePtr& v) {
	if (!v && graphPrev) {
		modify("graphPrev");
		graphPrev.reset();
	}
	if (!graphPrev || v->getId() != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

void TypeDef::setGraphPrev(const NodeId& v) {
	if (v != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

const NodePtr& TypeDef::getGraphPrev(bool required) {
	const NodePtr& v = graphPrev.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
	}
	return v;
}


void TypeDef::setName(const std::string& v) {
	if (!equal(v, name)) {
		modify("name");
		name = v;
	}
}

const std::string& TypeDef::getName(bool required) {
	const std::string& v = name;
	if (required && v.empty()) {
		throw std::runtime_error("Node " + getId().str() + " is required to have a non-empty string name set.");
	}
	return v;
}


void TypeDef::setType(const NodePtr& v) {
	if (v && !v->isKindOf(kNamedTypeExpr) && !v->isKindOf(kNilTypeExpr) && !v->isKindOf(kUnionTypeExpr) && !v->isKindOf(kTupleTypeExpr) && !v->isKindOf(kQualifiedTypeExpr) && !v->isKindOf(kSpecializedTypeExpr) && !v->isKindOf(kFuncTypeExpr) && !v->isKindOf(kNativeTypeExpr)) {
		throw std::runtime_error("'type' of " + id.str() + " needs to be of kind {NamedTypeExpr, NilTypeExpr, UnionTypeExpr, TupleTypeExpr, QualifiedTypeExpr, SpecializedTypeExpr, FuncTypeExpr, NativeTypeExpr} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, type)) {
		modify("type");
		type = v;
	}
}

const NodePtr& TypeDef::getType(bool required) {
	const NodePtr& v = type;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have type set to a non-null value.");
	}
	return v;
}


void TypeDef::encode(Encoder& e) {
	e.encode(this->graphPrev);
	e.encode(this->name);
	e.encode(this->type);
}

void TypeDef::decode(Decoder& d) {
	d.decode(this->graphPrev);
	d.decode(this->name);
	d.decode(this->type);
}


void TypeDef::updateHierarchyOfChildren() {
	if (this->type) this->type->updateHierarchy(id + "type", repository, this);
}

const NodePtr& TypeDef::resolvePath(const std::string& path) {
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
		// type.*
		if (size >= 4 && path[0] == 't' && path[1] == 'y' && path[2] == 'p' && path[3] == 'e') {
			// type
			if (size == 4) {
				return getType();
			} else if (path[4] == '.') {
				return getType()->resolvePath(path.substr(5));
			}
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector TypeDef::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getType(false)) v.push_back(n);
	return v;
}

