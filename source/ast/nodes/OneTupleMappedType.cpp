/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "OneTupleMappedType.hpp"
#include "ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::OneTupleMappedType;
using ast::NodePtr;
using ast::NodeVector;

OneTupleMappedType::OneTupleMappedType() : Node() {}

bool OneTupleMappedType::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kOneTupleMappedType;
}

bool OneTupleMappedType::implements(Interface i) {
	if (Node::implements(i)) return true;
	return false;
}

NodePtr OneTupleMappedType::copy() {
	Ptr c (new OneTupleMappedType);
	Node::copy(this->tuple, c->tuple);
	return c;
}

bool OneTupleMappedType::equalTo(const NodePtr& o) {
	const shared_ptr<OneTupleMappedType>& other = boost::dynamic_pointer_cast<OneTupleMappedType>(o);
	if (!other) return false;
	if (!equal(this->tuple, other->tuple)) return false;
	return true;
}

std::string OneTupleMappedType::describe(int depth) {
	std::stringstream str, b;
	str << tuple->describe(depth-1) << ".0";
	return str.str();
}


void OneTupleMappedType::setTuple(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'tuple' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, tuple)) {
		modify("tuple");
		tuple = v;
	}
}

const NodePtr& OneTupleMappedType::getTuple(bool required) {
	const NodePtr& v = tuple;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have tuple set to a non-null value.");
	}
	return v;
}


void OneTupleMappedType::encode(Encoder& e) {
	e.encode(this->tuple);
}

void OneTupleMappedType::decode(Decoder& d) {
	d.decode(this->tuple);
}


void OneTupleMappedType::updateHierarchyOfChildren() {
	if (this->tuple) this->tuple->updateHierarchy(id + "tuple", repository, this);
}

const NodePtr& OneTupleMappedType::resolvePath(const std::string& path) {
	size_t size = path.size();
	// tuple.*
	if (size >= 5 && path[0] == 't' && path[1] == 'u' && path[2] == 'p' && path[3] == 'l' && path[4] == 'e') {
		// tuple
		if (size == 5) {
			return getTuple();
		} else if (path[5] == '.') {
			return getTuple()->resolvePath(path.substr(6));
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector OneTupleMappedType::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getTuple(false)) v.push_back(n);
	return v;
}

