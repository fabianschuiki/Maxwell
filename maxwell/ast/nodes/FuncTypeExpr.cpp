/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "maxwell/ast/nodes/FuncTypeExpr.hpp"
#include "maxwell/ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::FuncTypeExpr;
using ast::NodePtr;
using ast::NodeVector;

FuncTypeExpr::FuncTypeExpr() : Node(),
	interfaceGraph(this),
	interfaceTypeExpr(this) {}

bool FuncTypeExpr::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kFuncTypeExpr;
}

bool FuncTypeExpr::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kGraphInterface) return true;
	if (i == kTypeExprInterface) return true;
	return false;
}

NodePtr FuncTypeExpr::copy() {
	Ptr c (new FuncTypeExpr);
	Node::copy(this->graphPrev, c->graphPrev);
	Node::copy(this->evaluatedType, c->evaluatedType);
	Node::copy(this->in, c->in);
	Node::copy(this->out, c->out);
	return c;
}

bool FuncTypeExpr::equalTo(const NodePtr& o) {
	const shared_ptr<FuncTypeExpr>& other = boost::dynamic_pointer_cast<FuncTypeExpr>(o);
	if (!other) return false;
	if (!equal(this->graphPrev, other->graphPrev)) return false;
	if (!equal(this->evaluatedType, other->evaluatedType)) return false;
	if (!equal(this->in, other->in)) return false;
	if (!equal(this->out, other->out)) return false;
	return true;
}

std::string FuncTypeExpr::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "FuncTypeExpr{…}";
	str << "FuncTypeExpr{";
	if (this->graphPrev) b << "\n  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
	if (this->evaluatedType) b << "\n  \033[1mevaluatedType\033[0m = " << indent(this->evaluatedType->describe(depth-1));
	if (this->in) b << "\n  \033[1min\033[0m = " << indent(this->in->describe(depth-1));
	if (this->out) b << "\n  \033[1mout\033[0m = " << indent(this->out->describe(depth-1));
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void FuncTypeExpr::setGraphPrev(const NodePtr& v) {
	if (!v && graphPrev) {
		modify("graphPrev");
		graphPrev.reset();
	}
	if (!graphPrev || v->getId() != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

void FuncTypeExpr::setGraphPrev(const NodeId& v) {
	if (v != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

const NodePtr& FuncTypeExpr::getGraphPrev(bool required) {
	const NodePtr& v = graphPrev.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
	}
	return v;
}


void FuncTypeExpr::setEvaluatedType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType) && !v->isKindOf(kNativeType) && !v->isKindOf(kMutableType) && !v->isKindOf(kMutableCastType) && !v->isKindOf(kImmutableCastType)) {
		throw std::runtime_error("'evaluatedType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType, NativeType, MutableType, MutableCastType, ImmutableCastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, evaluatedType)) {
		modify("evaluatedType");
		evaluatedType = v;
	}
}

const NodePtr& FuncTypeExpr::getEvaluatedType(bool required) {
	const NodePtr& v = evaluatedType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have evaluatedType set to a non-null value.");
	}
	return v;
}


void FuncTypeExpr::setIn(const NodePtr& v) {
	if (v && !v->isKindOf(kNamedTypeExpr) && !v->isKindOf(kNilTypeExpr) && !v->isKindOf(kUnionTypeExpr) && !v->isKindOf(kTupleTypeExpr) && !v->isKindOf(kQualifiedTypeExpr) && !v->isKindOf(kSpecializedTypeExpr) && !v->isKindOf(kFuncTypeExpr) && !v->isKindOf(kNativeTypeExpr) && !v->isKindOf(kMutableTypeExpr)) {
		throw std::runtime_error("'in' of " + id.str() + " needs to be of kind {NamedTypeExpr, NilTypeExpr, UnionTypeExpr, TupleTypeExpr, QualifiedTypeExpr, SpecializedTypeExpr, FuncTypeExpr, NativeTypeExpr, MutableTypeExpr} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, in)) {
		modify("in");
		in = v;
	}
}

const NodePtr& FuncTypeExpr::getIn(bool required) {
	const NodePtr& v = in;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have in set to a non-null value.");
	}
	return v;
}


void FuncTypeExpr::setOut(const NodePtr& v) {
	if (v && !v->isKindOf(kNamedTypeExpr) && !v->isKindOf(kNilTypeExpr) && !v->isKindOf(kUnionTypeExpr) && !v->isKindOf(kTupleTypeExpr) && !v->isKindOf(kQualifiedTypeExpr) && !v->isKindOf(kSpecializedTypeExpr) && !v->isKindOf(kFuncTypeExpr) && !v->isKindOf(kNativeTypeExpr) && !v->isKindOf(kMutableTypeExpr)) {
		throw std::runtime_error("'out' of " + id.str() + " needs to be of kind {NamedTypeExpr, NilTypeExpr, UnionTypeExpr, TupleTypeExpr, QualifiedTypeExpr, SpecializedTypeExpr, FuncTypeExpr, NativeTypeExpr, MutableTypeExpr} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, out)) {
		modify("out");
		out = v;
	}
}

const NodePtr& FuncTypeExpr::getOut(bool required) {
	const NodePtr& v = out;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have out set to a non-null value.");
	}
	return v;
}


void FuncTypeExpr::encode(Encoder& e) {
	e.encode(this->graphPrev);
	e.encode(this->evaluatedType);
	e.encode(this->in);
	e.encode(this->out);
}

void FuncTypeExpr::decode(Decoder& d) {
	d.decode(this->graphPrev);
	d.decode(this->evaluatedType);
	d.decode(this->in);
	d.decode(this->out);
}


void FuncTypeExpr::updateHierarchyOfChildren() {
	if (this->evaluatedType) this->evaluatedType->updateHierarchy(id + "evaluatedType", repository, this);
	if (this->in) this->in->updateHierarchy(id + "in", repository, this);
	if (this->out) this->out->updateHierarchy(id + "out", repository, this);
}

const NodePtr& FuncTypeExpr::resolvePath(const std::string& path) {
	size_t size = path.size();
	// .*
	if (true) {
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
		// in.*
		if (size >= 2 && path[0] == 'i' && path[1] == 'n') {
			// in
			if (size == 2) {
				return getIn();
			} else if (path[2] == '.') {
				return getIn()->resolvePath(path.substr(3));
			}
		}
		// out.*
		if (size >= 3 && path[0] == 'o' && path[1] == 'u' && path[2] == 't') {
			// out
			if (size == 3) {
				return getOut();
			} else if (path[3] == '.') {
				return getOut()->resolvePath(path.substr(4));
			}
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector FuncTypeExpr::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getEvaluatedType(false)) v.push_back(n);
	if (const NodePtr& n = this->getIn(false)) v.push_back(n);
	if (const NodePtr& n = this->getOut(false)) v.push_back(n);
	return v;
}

