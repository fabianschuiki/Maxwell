/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "maxwell/ast/nodes/IndexOpExpr.hpp"
#include "maxwell/ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::IndexOpExpr;
using ast::NodePtr;
using ast::NodeVector;

IndexOpExpr::IndexOpExpr() : Node(),
	interfaceGraph(this),
	interfaceType(this) {}

bool IndexOpExpr::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kIndexOpExpr;
}

bool IndexOpExpr::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kGraphInterface) return true;
	if (i == kTypeInterface) return true;
	return false;
}

NodePtr IndexOpExpr::copy() {
	Ptr c (new IndexOpExpr);
	Node::copy(this->graphPrev, c->graphPrev);
	Node::copy(this->indexee, c->indexee);
	Node::copy(this->index, c->index);
	Node::copy(this->possibleType, c->possibleType);
	Node::copy(this->requiredType, c->requiredType);
	Node::copy(this->actualType, c->actualType);
	return c;
}

bool IndexOpExpr::equalTo(const NodePtr& o) {
	const shared_ptr<IndexOpExpr>& other = boost::dynamic_pointer_cast<IndexOpExpr>(o);
	if (!other) return false;
	if (!equal(this->graphPrev, other->graphPrev)) return false;
	if (!equal(this->indexee, other->indexee)) return false;
	if (!equal(this->index, other->index)) return false;
	if (!equal(this->possibleType, other->possibleType)) return false;
	if (!equal(this->requiredType, other->requiredType)) return false;
	if (!equal(this->actualType, other->actualType)) return false;
	return true;
}

std::string IndexOpExpr::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "IndexOpExpr{…}";
	str << "IndexOpExpr{";
	if (this->graphPrev) b << "\n  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
	if (this->indexee) b << "\n  \033[1mindexee\033[0m = " << indent(this->indexee->describe(depth-1));
	if (this->index) b << "\n  \033[1mindex\033[0m = " << indent(this->index->describe(depth-1));
	if (this->possibleType) b << "\n  \033[1mpossibleType\033[0m = " << indent(this->possibleType->describe(depth-1));
	if (this->requiredType) b << "\n  \033[1mrequiredType\033[0m = " << indent(this->requiredType->describe(depth-1));
	if (this->actualType) b << "\n  \033[1mactualType\033[0m = " << indent(this->actualType->describe(depth-1));
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void IndexOpExpr::setGraphPrev(const NodePtr& v) {
	if (!v && graphPrev) {
		modify("graphPrev");
		graphPrev.reset();
	}
	if (!graphPrev || v->getId() != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

void IndexOpExpr::setGraphPrev(const NodeId& v) {
	if (v != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

const NodePtr& IndexOpExpr::getGraphPrev(bool required) {
	const NodePtr& v = graphPrev.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
	}
	return v;
}


void IndexOpExpr::setIndexee(const NodePtr& v) {
	if (v && !v->implements(kTypeInterface)) {
		throw std::runtime_error("'indexee' of " + id.str() + " needs to be of kind {} or implement interface {Type}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, indexee)) {
		modify("indexee");
		indexee = v;
	}
}

const NodePtr& IndexOpExpr::getIndexee(bool required) {
	const NodePtr& v = indexee;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have indexee set to a non-null value.");
	}
	return v;
}


void IndexOpExpr::setIndex(const NodePtr& v) {
	if (v && !v->implements(kTypeInterface)) {
		throw std::runtime_error("'index' of " + id.str() + " needs to be of kind {} or implement interface {Type}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, index)) {
		modify("index");
		index = v;
	}
}

const NodePtr& IndexOpExpr::getIndex(bool required) {
	const NodePtr& v = index;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have index set to a non-null value.");
	}
	return v;
}


void IndexOpExpr::setPossibleType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType) && !v->isKindOf(kNativeType)) {
		throw std::runtime_error("'possibleType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType, NativeType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, possibleType)) {
		modify("possibleType");
		possibleType = v;
	}
}

const NodePtr& IndexOpExpr::getPossibleType(bool required) {
	const NodePtr& v = possibleType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have possibleType set to a non-null value.");
	}
	return v;
}


void IndexOpExpr::setRequiredType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType) && !v->isKindOf(kNativeType)) {
		throw std::runtime_error("'requiredType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType, NativeType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, requiredType)) {
		modify("requiredType");
		requiredType = v;
	}
}

const NodePtr& IndexOpExpr::getRequiredType(bool required) {
	const NodePtr& v = requiredType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have requiredType set to a non-null value.");
	}
	return v;
}


void IndexOpExpr::setActualType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType) && !v->isKindOf(kNativeType)) {
		throw std::runtime_error("'actualType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType, NativeType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, actualType)) {
		modify("actualType");
		actualType = v;
	}
}

const NodePtr& IndexOpExpr::getActualType(bool required) {
	const NodePtr& v = actualType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have actualType set to a non-null value.");
	}
	return v;
}


void IndexOpExpr::encode(Encoder& e) {
	e.encode(this->graphPrev);
	e.encode(this->indexee);
	e.encode(this->index);
	e.encode(this->possibleType);
	e.encode(this->requiredType);
	e.encode(this->actualType);
}

void IndexOpExpr::decode(Decoder& d) {
	d.decode(this->graphPrev);
	d.decode(this->indexee);
	d.decode(this->index);
	d.decode(this->possibleType);
	d.decode(this->requiredType);
	d.decode(this->actualType);
}


void IndexOpExpr::updateHierarchyOfChildren() {
	if (this->indexee) this->indexee->updateHierarchy(id + "indexee", repository, this);
	if (this->index) this->index->updateHierarchy(id + "index", repository, this);
	if (this->possibleType) this->possibleType->updateHierarchy(id + "possibleType", repository, this);
	if (this->requiredType) this->requiredType->updateHierarchy(id + "requiredType", repository, this);
	if (this->actualType) this->actualType->updateHierarchy(id + "actualType", repository, this);
}

const NodePtr& IndexOpExpr::resolvePath(const std::string& path) {
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
		// index.*
		if (size >= 5 && path[0] == 'i' && path[1] == 'n' && path[2] == 'd' && path[3] == 'e' && path[4] == 'x') {
			// index
			if (size == 5) {
				return getIndex();
			} else if (path[5] == '.') {
				return getIndex()->resolvePath(path.substr(6));
			}
			// indexee.*
			if (size >= 7 && path[5] == 'e' && path[6] == 'e') {
				// indexee
				if (size == 7) {
					return getIndexee();
				} else if (path[7] == '.') {
					return getIndexee()->resolvePath(path.substr(8));
				}
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

NodeVector IndexOpExpr::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getIndexee(false)) v.push_back(n);
	if (const NodePtr& n = this->getIndex(false)) v.push_back(n);
	return v;
}

