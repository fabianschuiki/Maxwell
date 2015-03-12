/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "maxwell/ast/nodes/AssignmentExpr.hpp"
#include "maxwell/ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::AssignmentExpr;
using ast::NodePtr;
using ast::NodeVector;

AssignmentExpr::AssignmentExpr() : Node(),
	interfaceGraph(this),
	interfaceType(this) {}

bool AssignmentExpr::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kAssignmentExpr;
}

bool AssignmentExpr::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kGraphInterface) return true;
	if (i == kTypeInterface) return true;
	return false;
}

NodePtr AssignmentExpr::copy() {
	Ptr c (new AssignmentExpr);
	Node::copy(this->rhs, c->rhs);
	Node::copy(this->lhs, c->lhs);
	Node::copy(this->graphPrev, c->graphPrev);
	Node::copy(this->possibleType, c->possibleType);
	Node::copy(this->requiredType, c->requiredType);
	Node::copy(this->actualType, c->actualType);
	return c;
}

bool AssignmentExpr::equalTo(const NodePtr& o) {
	const shared_ptr<AssignmentExpr>& other = boost::dynamic_pointer_cast<AssignmentExpr>(o);
	if (!other) return false;
	if (!equal(this->rhs, other->rhs)) return false;
	if (!equal(this->lhs, other->lhs)) return false;
	if (!equal(this->graphPrev, other->graphPrev)) return false;
	if (!equal(this->possibleType, other->possibleType)) return false;
	if (!equal(this->requiredType, other->requiredType)) return false;
	if (!equal(this->actualType, other->actualType)) return false;
	return true;
}

std::string AssignmentExpr::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "AssignmentExpr{…}";
	str << "AssignmentExpr{";
	if (this->rhs) b << "\n  \033[1mrhs\033[0m = " << indent(this->rhs->describe(depth-1));
	if (this->lhs) b << "\n  \033[1mlhs\033[0m = " << indent(this->lhs->describe(depth-1));
	if (this->graphPrev) b << "\n  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
	if (this->possibleType) b << "\n  \033[1mpossibleType\033[0m = " << indent(this->possibleType->describe(depth-1));
	if (this->requiredType) b << "\n  \033[1mrequiredType\033[0m = " << indent(this->requiredType->describe(depth-1));
	if (this->actualType) b << "\n  \033[1mactualType\033[0m = " << indent(this->actualType->describe(depth-1));
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void AssignmentExpr::setRhs(const NodePtr& v) {
	if (!equal(v, rhs)) {
		modify("rhs");
		rhs = v;
	}
}

const NodePtr& AssignmentExpr::getRhs(bool required) {
	const NodePtr& v = rhs;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have rhs set to a non-null value.");
	}
	return v;
}


void AssignmentExpr::setLhs(const NodePtr& v) {
	if (!equal(v, lhs)) {
		modify("lhs");
		lhs = v;
	}
}

const NodePtr& AssignmentExpr::getLhs(bool required) {
	const NodePtr& v = lhs;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have lhs set to a non-null value.");
	}
	return v;
}


void AssignmentExpr::setGraphPrev(const NodePtr& v) {
	if (!v && graphPrev) {
		modify("graphPrev");
		graphPrev.reset();
	}
	if (!graphPrev || v->getId() != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

void AssignmentExpr::setGraphPrev(const NodeId& v) {
	if (v != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

const NodePtr& AssignmentExpr::getGraphPrev(bool required) {
	const NodePtr& v = graphPrev.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
	}
	return v;
}


void AssignmentExpr::setPossibleType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType) && !v->isKindOf(kNativeType)) {
		throw std::runtime_error("'possibleType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType, NativeType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, possibleType)) {
		modify("possibleType");
		possibleType = v;
	}
}

const NodePtr& AssignmentExpr::getPossibleType(bool required) {
	const NodePtr& v = possibleType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have possibleType set to a non-null value.");
	}
	return v;
}


void AssignmentExpr::setRequiredType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType) && !v->isKindOf(kNativeType)) {
		throw std::runtime_error("'requiredType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType, NativeType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, requiredType)) {
		modify("requiredType");
		requiredType = v;
	}
}

const NodePtr& AssignmentExpr::getRequiredType(bool required) {
	const NodePtr& v = requiredType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have requiredType set to a non-null value.");
	}
	return v;
}


void AssignmentExpr::setActualType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType) && !v->isKindOf(kNativeType)) {
		throw std::runtime_error("'actualType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType, NativeType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, actualType)) {
		modify("actualType");
		actualType = v;
	}
}

const NodePtr& AssignmentExpr::getActualType(bool required) {
	const NodePtr& v = actualType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have actualType set to a non-null value.");
	}
	return v;
}


void AssignmentExpr::encode(Encoder& e) {
	e.encode(this->rhs);
	e.encode(this->lhs);
	e.encode(this->graphPrev);
	e.encode(this->possibleType);
	e.encode(this->requiredType);
	e.encode(this->actualType);
}

void AssignmentExpr::decode(Decoder& d) {
	d.decode(this->rhs);
	d.decode(this->lhs);
	d.decode(this->graphPrev);
	d.decode(this->possibleType);
	d.decode(this->requiredType);
	d.decode(this->actualType);
}


void AssignmentExpr::updateHierarchyOfChildren() {
	if (this->rhs) this->rhs->updateHierarchy(id + "rhs", repository, this);
	if (this->lhs) this->lhs->updateHierarchy(id + "lhs", repository, this);
	if (this->possibleType) this->possibleType->updateHierarchy(id + "possibleType", repository, this);
	if (this->requiredType) this->requiredType->updateHierarchy(id + "requiredType", repository, this);
	if (this->actualType) this->actualType->updateHierarchy(id + "actualType", repository, this);
}

const NodePtr& AssignmentExpr::resolvePath(const std::string& path) {
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
		// graphPrev.*
		if (size >= 9 && path[0] == 'g' && path[1] == 'r' && path[2] == 'a' && path[3] == 'p' && path[4] == 'h' && path[5] == 'P' && path[6] == 'r' && path[7] == 'e' && path[8] == 'v') {
			// graphPrev
			if (size == 9) {
				return getGraphPrev();
			} else if (path[9] == '.') {
				return getGraphPrev()->resolvePath(path.substr(10));
			}
		}
		// lhs.*
		if (size >= 3 && path[0] == 'l' && path[1] == 'h' && path[2] == 's') {
			// lhs
			if (size == 3) {
				return getLhs();
			} else if (path[3] == '.') {
				return getLhs()->resolvePath(path.substr(4));
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
		// r.*
		if (size >= 1 && path[0] == 'r') {
			// requiredType.*
			if (size >= 12 && path[1] == 'e' && path[2] == 'q' && path[3] == 'u' && path[4] == 'i' && path[5] == 'r' && path[6] == 'e' && path[7] == 'd' && path[8] == 'T' && path[9] == 'y' && path[10] == 'p' && path[11] == 'e') {
				// requiredType
				if (size == 12) {
					return getRequiredType();
				} else if (path[12] == '.') {
					return getRequiredType()->resolvePath(path.substr(13));
				}
			}
			// rhs.*
			if (size >= 3 && path[1] == 'h' && path[2] == 's') {
				// rhs
				if (size == 3) {
					return getRhs();
				} else if (path[3] == '.') {
					return getRhs()->resolvePath(path.substr(4));
				}
			}
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector AssignmentExpr::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getRhs(false)) v.push_back(n);
	if (const NodePtr& n = this->getLhs(false)) v.push_back(n);
	return v;
}

