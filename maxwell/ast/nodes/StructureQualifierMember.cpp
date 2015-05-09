/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "maxwell/ast/nodes/StructureQualifierMember.hpp"
#include "maxwell/ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::StructureQualifierMember;
using ast::NodePtr;
using ast::NodeVector;

StructureQualifierMember::StructureQualifierMember() : Node(),
	interfaceCallable(this),
	interfaceGraph(this),
	interfaceNamed(this) {}

bool StructureQualifierMember::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kStructureQualifierMember;
}

bool StructureQualifierMember::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kCallableInterface) return true;
	if (i == kGraphInterface) return true;
	if (i == kNamedInterface) return true;
	return false;
}

NodePtr StructureQualifierMember::copy() {
	Ptr c (new StructureQualifierMember);
	Node::copy(this->graphPrev, c->graphPrev);
	Node::copy(this->name, c->name);
	Node::copy(this->type, c->type);
	Node::copy(this->implSetter, c->implSetter);
	Node::copy(this->implGetter, c->implGetter);
	return c;
}

bool StructureQualifierMember::equalTo(const NodePtr& o) {
	const shared_ptr<StructureQualifierMember>& other = boost::dynamic_pointer_cast<StructureQualifierMember>(o);
	if (!other) return false;
	if (!equal(this->graphPrev, other->graphPrev)) return false;
	if (!equal(this->name, other->name)) return false;
	if (!equal(this->type, other->type)) return false;
	if (!equal(this->implSetter, other->implSetter)) return false;
	if (!equal(this->implGetter, other->implGetter)) return false;
	return true;
}

std::string StructureQualifierMember::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "StructureQualifierMember{…}";
	str << "StructureQualifierMember{";
	if (this->graphPrev) b << "\n  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
	if (!this->name.empty()) b << "\n  \033[1mname\033[0m = \033[33m\"" << this->name << "\"\033[0m";
	if (this->type) b << "\n  \033[1mtype\033[0m = " << indent(this->type->describe(depth-1));
	if (this->implSetter) b << "\n  \033[1mimplSetter\033[0m = " << indent(this->implSetter->describe(depth-1));
	if (this->implGetter) b << "\n  \033[1mimplGetter\033[0m = " << indent(this->implGetter->describe(depth-1));
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void StructureQualifierMember::setGraphPrev(const NodePtr& v) {
	if (!v && graphPrev) {
		modify("graphPrev");
		graphPrev.reset();
	}
	if (!graphPrev || v->getId() != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

void StructureQualifierMember::setGraphPrev(const NodeId& v) {
	if (v != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

const NodePtr& StructureQualifierMember::getGraphPrev(bool required) {
	const NodePtr& v = graphPrev.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
	}
	return v;
}


void StructureQualifierMember::setName(const std::string& v) {
	if (!equal(v, name)) {
		modify("name");
		name = v;
	}
}

const std::string& StructureQualifierMember::getName(bool required) {
	const std::string& v = name;
	if (required && v.empty()) {
		throw std::runtime_error("Node " + getId().str() + " is required to have a non-empty string name set.");
	}
	return v;
}


void StructureQualifierMember::setType(const NodePtr& v) {
	if (v && !v->isKindOf(kNamedTypeExpr) && !v->isKindOf(kNilTypeExpr) && !v->isKindOf(kUnionTypeExpr) && !v->isKindOf(kTupleTypeExpr) && !v->isKindOf(kQualifiedTypeExpr) && !v->isKindOf(kSpecializedTypeExpr) && !v->isKindOf(kFuncTypeExpr) && !v->isKindOf(kNativeTypeExpr) && !v->isKindOf(kMutableTypeExpr)) {
		throw std::runtime_error("'type' of " + id.str() + " needs to be of kind {NamedTypeExpr, NilTypeExpr, UnionTypeExpr, TupleTypeExpr, QualifiedTypeExpr, SpecializedTypeExpr, FuncTypeExpr, NativeTypeExpr, MutableTypeExpr} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, type)) {
		modify("type");
		type = v;
	}
}

const NodePtr& StructureQualifierMember::getType(bool required) {
	const NodePtr& v = type;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have type set to a non-null value.");
	}
	return v;
}


void StructureQualifierMember::setImplSetter(const NodePtr& v) {
	if (v && !v->isKindOf(kImplAccessor)) {
		throw std::runtime_error("'implSetter' of " + id.str() + " needs to be of kind {ImplAccessor} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, implSetter)) {
		modify("implSetter");
		implSetter = v;
	}
}

const NodePtr& StructureQualifierMember::getImplSetter(bool required) {
	const NodePtr& v = implSetter;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have implSetter set to a non-null value.");
	}
	return v;
}


void StructureQualifierMember::setImplGetter(const NodePtr& v) {
	if (v && !v->isKindOf(kImplAccessor)) {
		throw std::runtime_error("'implGetter' of " + id.str() + " needs to be of kind {ImplAccessor} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, implGetter)) {
		modify("implGetter");
		implGetter = v;
	}
}

const NodePtr& StructureQualifierMember::getImplGetter(bool required) {
	const NodePtr& v = implGetter;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have implGetter set to a non-null value.");
	}
	return v;
}


void StructureQualifierMember::encode(Encoder& e) {
	e.encode(this->graphPrev);
	e.encode(this->name);
	e.encode(this->type);
	e.encode(this->implSetter);
	e.encode(this->implGetter);
}

void StructureQualifierMember::decode(Decoder& d) {
	d.decode(this->graphPrev);
	d.decode(this->name);
	d.decode(this->type);
	d.decode(this->implSetter);
	d.decode(this->implGetter);
}


void StructureQualifierMember::updateHierarchyOfChildren() {
	if (this->type) this->type->updateHierarchy(id + "type", repository, this);
	if (this->implSetter) this->implSetter->updateHierarchy(id + "implSetter", repository, this);
	if (this->implGetter) this->implGetter->updateHierarchy(id + "implGetter", repository, this);
}

const NodePtr& StructureQualifierMember::resolvePath(const std::string& path) {
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
		// impl.*
		if (size >= 4 && path[0] == 'i' && path[1] == 'm' && path[2] == 'p' && path[3] == 'l') {
			// implGetter.*
			if (size >= 10 && path[4] == 'G' && path[5] == 'e' && path[6] == 't' && path[7] == 't' && path[8] == 'e' && path[9] == 'r') {
				// implGetter
				if (size == 10) {
					return getImplGetter();
				} else if (path[10] == '.') {
					return getImplGetter()->resolvePath(path.substr(11));
				}
			}
			// implSetter.*
			if (size >= 10 && path[4] == 'S' && path[5] == 'e' && path[6] == 't' && path[7] == 't' && path[8] == 'e' && path[9] == 'r') {
				// implSetter
				if (size == 10) {
					return getImplSetter();
				} else if (path[10] == '.') {
					return getImplSetter()->resolvePath(path.substr(11));
				}
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

NodeVector StructureQualifierMember::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getType(false)) v.push_back(n);
	if (const NodePtr& n = this->getImplSetter(false)) v.push_back(n);
	if (const NodePtr& n = this->getImplGetter(false)) v.push_back(n);
	return v;
}

