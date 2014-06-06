/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "NamedTypeExpr.hpp"
#include "ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::NamedTypeExpr;
using ast::NodePtr;
using ast::NodeVector;

NamedTypeExpr::NamedTypeExpr() : Node(),
	interfaceGraph(this),
	interfaceNamed(this),
	interfaceTypeExpr(this) {}

bool NamedTypeExpr::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kNamedTypeExpr;
}

bool NamedTypeExpr::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kGraphInterface) return true;
	if (i == kNamedInterface) return true;
	if (i == kTypeExprInterface) return true;
	return false;
}

NodePtr NamedTypeExpr::copy() {
	Ptr c (new NamedTypeExpr);
	Node::copy(this->graphPrev, c->graphPrev);
	Node::copy(this->evaluatedType, c->evaluatedType);
	Node::copy(this->name, c->name);
	Node::copy(this->definition, c->definition);
	return c;
}

bool NamedTypeExpr::equalTo(const NodePtr& o) {
	const shared_ptr<NamedTypeExpr>& other = boost::dynamic_pointer_cast<NamedTypeExpr>(o);
	if (!other) return false;
	if (!equal(this->graphPrev, other->graphPrev)) return false;
	if (!equal(this->evaluatedType, other->evaluatedType)) return false;
	if (!equal(this->name, other->name)) return false;
	if (!equal(this->definition, other->definition)) return false;
	return true;
}

std::string NamedTypeExpr::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "NamedTypeExpr{…}";
	str << "NamedTypeExpr{";
	if (this->graphPrev) b << "\n  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
	if (this->evaluatedType) b << "\n  \033[1mevaluatedType\033[0m = " << indent(this->evaluatedType->describe(depth-1));
	if (!this->name.empty()) b << "\n  \033[1mname\033[0m = \033[33m\"" << this->name << "\"\033[0m";
	if (this->definition) b << "\n  \033[1mdefinition\033[0m = \033[36m" << this->definition.id << "\033[0m";
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void NamedTypeExpr::setGraphPrev(const NodePtr& v) {
	if (!v && graphPrev) {
		modify("graphPrev");
		graphPrev.reset();
	}
	if (!graphPrev || v->getId() != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

void NamedTypeExpr::setGraphPrev(const NodeId& v) {
	if (v != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

const NodePtr& NamedTypeExpr::getGraphPrev(bool required) {
	const NodePtr& v = graphPrev.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
	}
	return v;
}


void NamedTypeExpr::setEvaluatedType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'evaluatedType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, evaluatedType)) {
		modify("evaluatedType");
		evaluatedType = v;
	}
}

const NodePtr& NamedTypeExpr::getEvaluatedType(bool required) {
	const NodePtr& v = evaluatedType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have evaluatedType set to a non-null value.");
	}
	return v;
}


void NamedTypeExpr::setName(const std::string& v) {
	if (!equal(v, name)) {
		modify("name");
		name = v;
	}
}

const std::string& NamedTypeExpr::getName(bool required) {
	const std::string& v = name;
	if (required && v.empty()) {
		throw std::runtime_error("Node " + getId().str() + " is required to have a non-empty string name set.");
	}
	return v;
}


void NamedTypeExpr::setDefinition(const NodePtr& v) {
	if (!v && definition) {
		modify("definition");
		definition.reset();
	}
	if (!definition || v->getId() != definition.id) {
		modify("definition");
		definition.set(v);
	}
}

void NamedTypeExpr::setDefinition(const NodeId& v) {
	if (v != definition.id) {
		modify("definition");
		definition.set(v);
	}
}

const NodePtr& NamedTypeExpr::getDefinition(bool required) {
	const NodePtr& v = definition.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have definition set to a non-null value.");
	}
	return v;
}


void NamedTypeExpr::encode(Encoder& e) {
	e.encode(this->graphPrev);
	e.encode(this->evaluatedType);
	e.encode(this->name);
	e.encode(this->definition);
}

void NamedTypeExpr::decode(Decoder& d) {
	d.decode(this->graphPrev);
	d.decode(this->evaluatedType);
	d.decode(this->name);
	d.decode(this->definition);
}


void NamedTypeExpr::updateHierarchyOfChildren() {
	if (this->evaluatedType) this->evaluatedType->updateHierarchy(id + "evaluatedType", repository, this);
}

const NodePtr& NamedTypeExpr::resolvePath(const std::string& path) {
	size_t size = path.size();
	// .*
	if (true) {
		// definition.*
		if (size >= 10 && path[0] == 'd' && path[1] == 'e' && path[2] == 'f' && path[3] == 'i' && path[4] == 'n' && path[5] == 'i' && path[6] == 't' && path[7] == 'i' && path[8] == 'o' && path[9] == 'n') {
			// definition
			if (size == 10) {
				return getDefinition();
			} else if (path[10] == '.') {
				return getDefinition()->resolvePath(path.substr(11));
			}
		}
		// evaluatedType.*
		if (size >= 13 && path[0] == 'e' && path[1] == 'v' && path[2] == 'a' && path[3] == 'l' && path[4] == 'u' && path[5] == 'a' && path[6] == 't' && path[7] == 'e' && path[8] == 'd' && path[9] == 'T' && path[10] == 'y' && path[11] == 'p' && path[12] == 'e') {
			// evaluatedType
			if (size == 13) {
				return getEvaluatedType();
			} else if (path[13] == '.') {
				return getEvaluatedType()->resolvePath(path.substr(14));
			}
		}
		// graphPrev.*
		if (size >= 9 && path[0] == 'g' && path[1] == 'r' && path[2] == 'a' && path[3] == 'p' && path[4] == 'h' && path[5] == 'P' && path[6] == 'r' && path[7] == 'e' && path[8] == 'v') {
			// graphPrev
			if (size == 9) {
				return getGraphPrev();
			} else if (path[9] == '.') {
				return getGraphPrev()->resolvePath(path.substr(10));
			}
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector NamedTypeExpr::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getEvaluatedType(false)) v.push_back(n);
	return v;
}

