/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "maxwell/ast/nodes/FuncArg.hpp"
#include "maxwell/ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::FuncArg;
using ast::NodePtr;
using ast::NodeVector;

FuncArg::FuncArg() : Node(),
	interfaceGraph(this),
	interfaceNamed(this),
	interfaceType(this),
	interfaceVariable(this) {}

bool FuncArg::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kFuncArg;
}

bool FuncArg::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kGraphInterface) return true;
	if (i == kNamedInterface) return true;
	if (i == kTypeInterface) return true;
	if (i == kVariableInterface) return true;
	return false;
}

NodePtr FuncArg::copy() {
	Ptr c (new FuncArg);
	Node::copy(this->graphPrev, c->graphPrev);
	Node::copy(this->possibleType, c->possibleType);
	Node::copy(this->requiredType, c->requiredType);
	Node::copy(this->actualType, c->actualType);
	Node::copy(this->name, c->name);
	Node::copy(this->typeExpr, c->typeExpr);
	return c;
}

bool FuncArg::equalTo(const NodePtr& o) {
	const shared_ptr<FuncArg>& other = boost::dynamic_pointer_cast<FuncArg>(o);
	if (!other) return false;
	if (!equal(this->graphPrev, other->graphPrev)) return false;
	if (!equal(this->possibleType, other->possibleType)) return false;
	if (!equal(this->requiredType, other->requiredType)) return false;
	if (!equal(this->actualType, other->actualType)) return false;
	if (!equal(this->name, other->name)) return false;
	if (!equal(this->typeExpr, other->typeExpr)) return false;
	return true;
}

std::string FuncArg::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "FuncArg{…}";
	str << "FuncArg{";
	if (this->graphPrev) b << "\n  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
	if (this->possibleType) b << "\n  \033[1mpossibleType\033[0m = " << indent(this->possibleType->describe(depth-1));
	if (this->requiredType) b << "\n  \033[1mrequiredType\033[0m = " << indent(this->requiredType->describe(depth-1));
	if (this->actualType) b << "\n  \033[1mactualType\033[0m = " << indent(this->actualType->describe(depth-1));
	if (!this->name.empty()) b << "\n  \033[1mname\033[0m = \033[33m\"" << this->name << "\"\033[0m";
	if (this->typeExpr) b << "\n  \033[1mtypeExpr\033[0m = " << indent(this->typeExpr->describe(depth-1));
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void FuncArg::setGraphPrev(const NodePtr& v) {
	if (!v && graphPrev) {
		modify("graphPrev");
		graphPrev.reset();
	}
	if (!graphPrev || v->getId() != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

void FuncArg::setGraphPrev(const NodeId& v) {
	if (v != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

const NodePtr& FuncArg::getGraphPrev(bool required) {
	const NodePtr& v = graphPrev.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
	}
	return v;
}


void FuncArg::setPossibleType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType) && !v->isKindOf(kNativeType)) {
		throw std::runtime_error("'possibleType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType, NativeType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, possibleType)) {
		modify("possibleType");
		possibleType = v;
	}
}

const NodePtr& FuncArg::getPossibleType(bool required) {
	const NodePtr& v = possibleType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have possibleType set to a non-null value.");
	}
	return v;
}


void FuncArg::setRequiredType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType) && !v->isKindOf(kNativeType)) {
		throw std::runtime_error("'requiredType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType, NativeType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, requiredType)) {
		modify("requiredType");
		requiredType = v;
	}
}

const NodePtr& FuncArg::getRequiredType(bool required) {
	const NodePtr& v = requiredType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have requiredType set to a non-null value.");
	}
	return v;
}


void FuncArg::setActualType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType) && !v->isKindOf(kNativeType)) {
		throw std::runtime_error("'actualType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType, NativeType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, actualType)) {
		modify("actualType");
		actualType = v;
	}
}

const NodePtr& FuncArg::getActualType(bool required) {
	const NodePtr& v = actualType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have actualType set to a non-null value.");
	}
	return v;
}


void FuncArg::setName(const std::string& v) {
	if (!equal(v, name)) {
		modify("name");
		name = v;
	}
}

const std::string& FuncArg::getName(bool required) {
	const std::string& v = name;
	if (required && v.empty()) {
		throw std::runtime_error("Node " + getId().str() + " is required to have a non-empty string name set.");
	}
	return v;
}


void FuncArg::setTypeExpr(const NodePtr& v) {
	if (v && !v->isKindOf(kNamedTypeExpr) && !v->isKindOf(kNilTypeExpr) && !v->isKindOf(kUnionTypeExpr) && !v->isKindOf(kTupleTypeExpr) && !v->isKindOf(kQualifiedTypeExpr) && !v->isKindOf(kSpecializedTypeExpr) && !v->isKindOf(kFuncTypeExpr) && !v->isKindOf(kNativeTypeExpr)) {
		throw std::runtime_error("'typeExpr' of " + id.str() + " needs to be of kind {NamedTypeExpr, NilTypeExpr, UnionTypeExpr, TupleTypeExpr, QualifiedTypeExpr, SpecializedTypeExpr, FuncTypeExpr, NativeTypeExpr} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, typeExpr)) {
		modify("typeExpr");
		typeExpr = v;
	}
}

const NodePtr& FuncArg::getTypeExpr(bool required) {
	const NodePtr& v = typeExpr;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have typeExpr set to a non-null value.");
	}
	return v;
}


void FuncArg::encode(Encoder& e) {
	e.encode(this->graphPrev);
	e.encode(this->possibleType);
	e.encode(this->requiredType);
	e.encode(this->actualType);
	e.encode(this->name);
	e.encode(this->typeExpr);
}

void FuncArg::decode(Decoder& d) {
	d.decode(this->graphPrev);
	d.decode(this->possibleType);
	d.decode(this->requiredType);
	d.decode(this->actualType);
	d.decode(this->name);
	d.decode(this->typeExpr);
}


void FuncArg::updateHierarchyOfChildren() {
	if (this->possibleType) this->possibleType->updateHierarchy(id + "possibleType", repository, this);
	if (this->requiredType) this->requiredType->updateHierarchy(id + "requiredType", repository, this);
	if (this->actualType) this->actualType->updateHierarchy(id + "actualType", repository, this);
	if (this->typeExpr) this->typeExpr->updateHierarchy(id + "typeExpr", repository, this);
}

const NodePtr& FuncArg::resolvePath(const std::string& path) {
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
		// typeExpr.*
		if (size >= 8 && path[0] == 't' && path[1] == 'y' && path[2] == 'p' && path[3] == 'e' && path[4] == 'E' && path[5] == 'x' && path[6] == 'p' && path[7] == 'r') {
			// typeExpr
			if (size == 8) {
				return getTypeExpr();
			} else if (path[8] == '.') {
				return getTypeExpr()->resolvePath(path.substr(9));
			}
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector FuncArg::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getTypeExpr(false)) v.push_back(n);
	return v;
}

