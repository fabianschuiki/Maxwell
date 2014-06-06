/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "CastType.hpp"
#include "ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::CastType;
using ast::NodePtr;
using ast::NodeVector;

CastType::CastType() : Node() {}

bool CastType::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kCastType;
}

bool CastType::implements(Interface i) {
	if (Node::implements(i)) return true;
	return false;
}

NodePtr CastType::copy() {
	Ptr c (new CastType);
	Node::copy(this->func, c->func);
	Node::copy(this->in, c->in);
	Node::copy(this->out, c->out);
	return c;
}

bool CastType::equalTo(const NodePtr& o) {
	const shared_ptr<CastType>& other = boost::dynamic_pointer_cast<CastType>(o);
	if (!other) return false;
	if (!equal(this->func, other->func)) return false;
	if (!equal(this->in, other->in)) return false;
	if (!equal(this->out, other->out)) return false;
	return true;
}

std::string CastType::describe(int depth) {
	std::stringstream str, b;
	str << out->describe(depth-1) << '(' << func.id << '<' << in->describe(depth-1) << ')';
	return str.str();
}


void CastType::setFunc(const NodePtr& v) {
	if (v && !v->implements(kCallableInterface)) {
		throw std::runtime_error("'func' of " + id.str() + " needs to be of kind {} or implement interface {Callable}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!v && func) {
		modify("func");
		func.reset();
	}
	if (!func || v->getId() != func.id) {
		modify("func");
		func.set(v);
	}
}

void CastType::setFunc(const NodeId& v) {
	if (v != func.id) {
		modify("func");
		func.set(v);
	}
}

const NodePtr& CastType::getFunc(bool required) {
	const NodePtr& v = func.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have func set to a non-null value.");
	}
	return v;
}


void CastType::setIn(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'in' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, in)) {
		modify("in");
		in = v;
	}
}

const NodePtr& CastType::getIn(bool required) {
	const NodePtr& v = in;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have in set to a non-null value.");
	}
	return v;
}


void CastType::setOut(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'out' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, out)) {
		modify("out");
		out = v;
	}
}

const NodePtr& CastType::getOut(bool required) {
	const NodePtr& v = out;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have out set to a non-null value.");
	}
	return v;
}


void CastType::encode(Encoder& e) {
	e.encode(this->func);
	e.encode(this->in);
	e.encode(this->out);
}

void CastType::decode(Decoder& d) {
	d.decode(this->func);
	d.decode(this->in);
	d.decode(this->out);
}


void CastType::updateHierarchyOfChildren() {
	if (this->in) this->in->updateHierarchy(id + "in", repository, this);
	if (this->out) this->out->updateHierarchy(id + "out", repository, this);
}

const NodePtr& CastType::resolvePath(const std::string& path) {
	size_t size = path.size();
	// .*
	if (true) {
		// func.*
		if (size >= 4 && path[0] == 'f' && path[1] == 'u' && path[2] == 'n' && path[3] == 'c') {
			// func
			if (size == 4) {
				return getFunc();
			} else if (path[4] == '.') {
				return getFunc()->resolvePath(path.substr(5));
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

NodeVector CastType::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getFunc(false)) v.push_back(n);
	if (const NodePtr& n = this->getIn(false)) v.push_back(n);
	if (const NodePtr& n = this->getOut(false)) v.push_back(n);
	return v;
}

