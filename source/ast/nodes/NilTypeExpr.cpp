/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "NilTypeExpr.hpp"
#include "ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::NilTypeExpr;
using ast::NodePtr;
using ast::NodeVector;

NilTypeExpr::NilTypeExpr() : Node(),
	interfaceTypeExpr(this) {}

bool NilTypeExpr::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kNilTypeExpr;
}

bool NilTypeExpr::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kTypeExprInterface) return true;
	return false;
}

NodePtr NilTypeExpr::copy() {
	Ptr c (new NilTypeExpr);
	Node::copy(this->evaluatedType, c->evaluatedType);
	return c;
}

bool NilTypeExpr::equalTo(const NodePtr& o) {
	const shared_ptr<NilTypeExpr>& other = boost::dynamic_pointer_cast<NilTypeExpr>(o);
	if (!other) return false;
	if (!equal(this->evaluatedType, other->evaluatedType)) return false;
	return true;
}

std::string NilTypeExpr::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "NilTypeExpr{…}";
	str << "NilTypeExpr{";
	if (this->evaluatedType) b << "\n  \033[1mevaluatedType\033[0m = " << indent(this->evaluatedType->describe(depth-1));
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void NilTypeExpr::setEvaluatedType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'evaluatedType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, evaluatedType)) {
		modify("evaluatedType");
		evaluatedType = v;
	}
}

const NodePtr& NilTypeExpr::getEvaluatedType(bool required) {
	const NodePtr& v = evaluatedType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have evaluatedType set to a non-null value.");
	}
	return v;
}


void NilTypeExpr::encode(Encoder& e) {
	e.encode(this->evaluatedType);
}

void NilTypeExpr::decode(Decoder& d) {
	d.decode(this->evaluatedType);
}


void NilTypeExpr::updateHierarchyOfChildren() {
	if (this->evaluatedType) this->evaluatedType->updateHierarchy(id + "evaluatedType", repository, this);
}

const NodePtr& NilTypeExpr::resolvePath(const std::string& path) {
	size_t size = path.size();
	// evaluatedType.*
	if (size >= 13 && path[0] == 'e' && path[1] == 'v' && path[2] == 'a' && path[3] == 'l' && path[4] == 'u' && path[5] == 'a' && path[6] == 't' && path[7] == 'e' && path[8] == 'd' && path[9] == 'T' && path[10] == 'y' && path[11] == 'p' && path[12] == 'e') {
		// evaluatedType
		if (size == 13) {
			return getEvaluatedType();
		} else if (path[13] == '.') {
			return getEvaluatedType()->resolvePath(path.substr(14));
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector NilTypeExpr::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getEvaluatedType(false)) v.push_back(n);
	return v;
}

