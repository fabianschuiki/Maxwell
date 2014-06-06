/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "BlockExpr.hpp"
#include "ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::BlockExpr;
using ast::NodePtr;
using ast::NodeVector;

BlockExpr::BlockExpr() : Node(),
	interfaceGraph(this),
	interfaceType(this) {}

bool BlockExpr::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kBlockExpr;
}

bool BlockExpr::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kGraphInterface) return true;
	if (i == kTypeInterface) return true;
	return false;
}

NodePtr BlockExpr::copy() {
	Ptr c (new BlockExpr);
	Node::copy(this->graphPrev, c->graphPrev);
	Node::copy(this->possibleType, c->possibleType);
	Node::copy(this->requiredType, c->requiredType);
	Node::copy(this->actualType, c->actualType);
	Node::copy(this->exprs, c->exprs);
	return c;
}

bool BlockExpr::equalTo(const NodePtr& o) {
	const shared_ptr<BlockExpr>& other = boost::dynamic_pointer_cast<BlockExpr>(o);
	if (!other) return false;
	if (!equal(this->graphPrev, other->graphPrev)) return false;
	if (!equal(this->possibleType, other->possibleType)) return false;
	if (!equal(this->requiredType, other->requiredType)) return false;
	if (!equal(this->actualType, other->actualType)) return false;
	if (!equal(this->exprs, other->exprs)) return false;
	return true;
}

std::string BlockExpr::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "BlockExpr{…}";
	str << "BlockExpr{";
	if (this->graphPrev) b << "\n  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
	if (this->possibleType) b << "\n  \033[1mpossibleType\033[0m = " << indent(this->possibleType->describe(depth-1));
	if (this->requiredType) b << "\n  \033[1mrequiredType\033[0m = " << indent(this->requiredType->describe(depth-1));
	if (this->actualType) b << "\n  \033[1mactualType\033[0m = " << indent(this->actualType->describe(depth-1));
	if (!this->exprs.empty()) b << "\n  \033[1mexprs\033[0m = " << indent(describeVector(this->exprs, depth-1));
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void BlockExpr::setGraphPrev(const NodePtr& v) {
	if (!v && graphPrev) {
		modify("graphPrev");
		graphPrev.reset();
	}
	if (!graphPrev || v->getId() != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

void BlockExpr::setGraphPrev(const NodeId& v) {
	if (v != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

const NodePtr& BlockExpr::getGraphPrev(bool required) {
	const NodePtr& v = graphPrev.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
	}
	return v;
}


void BlockExpr::setPossibleType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'possibleType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, possibleType)) {
		modify("possibleType");
		possibleType = v;
	}
}

const NodePtr& BlockExpr::getPossibleType(bool required) {
	const NodePtr& v = possibleType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have possibleType set to a non-null value.");
	}
	return v;
}


void BlockExpr::setRequiredType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'requiredType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, requiredType)) {
		modify("requiredType");
		requiredType = v;
	}
}

const NodePtr& BlockExpr::getRequiredType(bool required) {
	const NodePtr& v = requiredType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have requiredType set to a non-null value.");
	}
	return v;
}


void BlockExpr::setActualType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'actualType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, actualType)) {
		modify("actualType");
		actualType = v;
	}
}

const NodePtr& BlockExpr::getActualType(bool required) {
	const NodePtr& v = actualType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have actualType set to a non-null value.");
	}
	return v;
}


void BlockExpr::setExprs(const NodeVector& v) {
	if (!equal(v, exprs)) {
		modify("exprs");
		exprs = v;
	}
}

const NodeVector& BlockExpr::getExprs(bool required) {
	const NodeVector& v = exprs;
	return v;
}


void BlockExpr::encode(Encoder& e) {
	e.encode(this->graphPrev);
	e.encode(this->possibleType);
	e.encode(this->requiredType);
	e.encode(this->actualType);
	e.encode(this->exprs);
}

void BlockExpr::decode(Decoder& d) {
	d.decode(this->graphPrev);
	d.decode(this->possibleType);
	d.decode(this->requiredType);
	d.decode(this->actualType);
	d.decode(this->exprs);
}


void BlockExpr::updateHierarchyOfChildren() {
	if (this->possibleType) this->possibleType->updateHierarchy(id + "possibleType", repository, this);
	if (this->requiredType) this->requiredType->updateHierarchy(id + "requiredType", repository, this);
	if (this->actualType) this->actualType->updateHierarchy(id + "actualType", repository, this);
	for (int i = 0; i < this->exprs.size(); i++) {
		char buf[32]; snprintf(buf, 31, "%i", i);
		this->exprs[i]->updateHierarchy((id + "exprs") + buf, repository, this);
	}
}

const NodePtr& BlockExpr::resolvePath(const std::string& path) {
	size_t size = path.size();
	// .*
	if (true) {
		// actualType.*
		if (size >= 10 && path[0] == 'a' && path[1] == 'c' && path[2] == 't' && path[3] == 'u' && path[4] == 'a' && path[5] == 'l' && path[6] == 'T' && path[7] == 'y' && path[8] == 'p' && path[9] == 'e') {
			// actualType
			if (size == 10) {
				return getActualType();
			} else if (path[10] == '.') {
				return getActualType()->resolvePath(path.substr(11));
			}
		}
		// exprs.*
		if (size >= 5 && path[0] == 'e' && path[1] == 'x' && path[2] == 'p' && path[3] == 'r' && path[4] == 's') {
			// exprs
			if (size == 5) {
				throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
			} else if (path[5] == '.') {
				size_t dot = path.find(".", 6);
				string idx_str = path.substr(6, dot);
				int idx = atoi(idx_str.c_str());
				const NodeVector& a = getExprs();
				if (idx < 0 || idx >= a.size()) {
					throw std::runtime_error("Index into array '" + path.substr(0, 5) + "' is out of bounds.");
				}
				if (dot == string::npos) {
					return a[idx];
				} else {
					return a[idx]->resolvePath(path.substr(dot + 1));
				}
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
		// possibleType.*
		if (size >= 12 && path[0] == 'p' && path[1] == 'o' && path[2] == 's' && path[3] == 's' && path[4] == 'i' && path[5] == 'b' && path[6] == 'l' && path[7] == 'e' && path[8] == 'T' && path[9] == 'y' && path[10] == 'p' && path[11] == 'e') {
			// possibleType
			if (size == 12) {
				return getPossibleType();
			} else if (path[12] == '.') {
				return getPossibleType()->resolvePath(path.substr(13));
			}
		}
		// requiredType.*
		if (size >= 12 && path[0] == 'r' && path[1] == 'e' && path[2] == 'q' && path[3] == 'u' && path[4] == 'i' && path[5] == 'r' && path[6] == 'e' && path[7] == 'd' && path[8] == 'T' && path[9] == 'y' && path[10] == 'p' && path[11] == 'e') {
			// requiredType
			if (size == 12) {
				return getRequiredType();
			} else if (path[12] == '.') {
				return getRequiredType()->resolvePath(path.substr(13));
			}
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector BlockExpr::getChildren() {
	NodeVector v;
	v.insert(v.end(), this->exprs.begin(), this->exprs.end());
	return v;
}

