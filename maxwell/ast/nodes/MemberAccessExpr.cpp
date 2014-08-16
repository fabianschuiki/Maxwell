/* Automatically generated by ast-gen. DO NOT MODIFY. */
#include "maxwell/ast/nodes/MemberAccessExpr.hpp"
#include "maxwell/ast/Coder.hpp"
#include <cstdio>
#include <sstream>
#include <stdexcept>
using ast::MemberAccessExpr;
using ast::NodePtr;
using ast::NodeVector;

MemberAccessExpr::MemberAccessExpr() : Node(),
	interfaceCall(this),
	interfaceCallArg(this),
	interfaceGraph(this),
	interfaceNamed(this),
	interfaceType(this) {}

bool MemberAccessExpr::isKindOf(Kind k) {
	if (Node::isKindOf(k)) return true;
	return k == kMemberAccessExpr;
}

bool MemberAccessExpr::implements(Interface i) {
	if (Node::implements(i)) return true;
	if (i == kCallInterface) return true;
	if (i == kCallArgInterface) return true;
	if (i == kGraphInterface) return true;
	if (i == kNamedInterface) return true;
	if (i == kTypeInterface) return true;
	return false;
}

NodePtr MemberAccessExpr::copy() {
	Ptr c (new MemberAccessExpr);
	Node::copy(this->graphPrev, c->graphPrev);
	Node::copy(this->expr, c->expr);
	Node::copy(this->name, c->name);
	Node::copy(this->possibleType, c->possibleType);
	Node::copy(this->requiredType, c->requiredType);
	Node::copy(this->actualType, c->actualType);
	Node::copy(this->callName, c->callName);
	Node::copy(this->callArgs, c->callArgs);
	Node::copy(this->callCandidates, c->callCandidates);
	Node::copy(this->selectedCallCandidate, c->selectedCallCandidate);
	return c;
}

bool MemberAccessExpr::equalTo(const NodePtr& o) {
	const shared_ptr<MemberAccessExpr>& other = boost::dynamic_pointer_cast<MemberAccessExpr>(o);
	if (!other) return false;
	if (!equal(this->graphPrev, other->graphPrev)) return false;
	if (!equal(this->expr, other->expr)) return false;
	if (!equal(this->name, other->name)) return false;
	if (!equal(this->possibleType, other->possibleType)) return false;
	if (!equal(this->requiredType, other->requiredType)) return false;
	if (!equal(this->actualType, other->actualType)) return false;
	if (!equal(this->callName, other->callName)) return false;
	if (!equal(this->callArgs, other->callArgs)) return false;
	if (!equal(this->callCandidates, other->callCandidates)) return false;
	if (!equal(this->selectedCallCandidate, other->selectedCallCandidate)) return false;
	return true;
}

std::string MemberAccessExpr::describe(int depth) {
	std::stringstream str, b;
	if (depth == 0) return "MemberAccessExpr{…}";
	str << "MemberAccessExpr{";
	if (this->graphPrev) b << "\n  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
	if (this->expr) b << "\n  \033[1mexpr\033[0m = " << indent(this->expr->describe(depth-1));
	if (!this->name.empty()) b << "\n  \033[1mname\033[0m = \033[33m\"" << this->name << "\"\033[0m";
	if (this->possibleType) b << "\n  \033[1mpossibleType\033[0m = " << indent(this->possibleType->describe(depth-1));
	if (this->requiredType) b << "\n  \033[1mrequiredType\033[0m = " << indent(this->requiredType->describe(depth-1));
	if (this->actualType) b << "\n  \033[1mactualType\033[0m = " << indent(this->actualType->describe(depth-1));
	if (!this->callName.empty()) b << "\n  \033[1mcallName\033[0m = \033[33m\"" << this->callName << "\"\033[0m";
	if (!this->callArgs.empty()) b << "\n  \033[1mcallArgs\033[0m = " << indent(describeVector(this->callArgs, depth-1));
	if (!this->callCandidates.empty()) b << "\n  \033[1mcallCandidates\033[0m = " << indent(describeVector(this->callCandidates, depth-1));
	if (this->selectedCallCandidate) b << "\n  \033[1mselectedCallCandidate\033[0m = \033[36m" << this->selectedCallCandidate.id << "\033[0m";
	string bs = b.str();
	if (!bs.empty()) str << bs << '\n';
	str << "}";
	return str.str();
}


void MemberAccessExpr::setGraphPrev(const NodePtr& v) {
	if (!v && graphPrev) {
		modify("graphPrev");
		graphPrev.reset();
	}
	if (!graphPrev || v->getId() != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

void MemberAccessExpr::setGraphPrev(const NodeId& v) {
	if (v != graphPrev.id) {
		modify("graphPrev");
		graphPrev.set(v);
	}
}

const NodePtr& MemberAccessExpr::getGraphPrev(bool required) {
	const NodePtr& v = graphPrev.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
	}
	return v;
}


void MemberAccessExpr::setExpr(const NodePtr& v) {
	if (!equal(v, expr)) {
		modify("expr");
		expr = v;
	}
}

const NodePtr& MemberAccessExpr::getExpr(bool required) {
	const NodePtr& v = expr;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have expr set to a non-null value.");
	}
	return v;
}


void MemberAccessExpr::setName(const std::string& v) {
	if (!equal(v, name)) {
		modify("name");
		name = v;
	}
}

const std::string& MemberAccessExpr::getName(bool required) {
	const std::string& v = name;
	if (required && v.empty()) {
		throw std::runtime_error("Node " + getId().str() + " is required to have a non-empty string name set.");
	}
	return v;
}


void MemberAccessExpr::setPossibleType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'possibleType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, possibleType)) {
		modify("possibleType");
		possibleType = v;
	}
}

const NodePtr& MemberAccessExpr::getPossibleType(bool required) {
	const NodePtr& v = possibleType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have possibleType set to a non-null value.");
	}
	return v;
}


void MemberAccessExpr::setRequiredType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'requiredType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, requiredType)) {
		modify("requiredType");
		requiredType = v;
	}
}

const NodePtr& MemberAccessExpr::getRequiredType(bool required) {
	const NodePtr& v = requiredType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have requiredType set to a non-null value.");
	}
	return v;
}


void MemberAccessExpr::setActualType(const NodePtr& v) {
	if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
		throw std::runtime_error("'actualType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!equal(v, actualType)) {
		modify("actualType");
		actualType = v;
	}
}

const NodePtr& MemberAccessExpr::getActualType(bool required) {
	const NodePtr& v = actualType;
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have actualType set to a non-null value.");
	}
	return v;
}


void MemberAccessExpr::setCallName(const std::string& v) {
	if (!equal(v, callName)) {
		modify("callName");
		callName = v;
	}
}

const std::string& MemberAccessExpr::getCallName(bool required) {
	const std::string& v = callName;
	if (required && v.empty()) {
		throw std::runtime_error("Node " + getId().str() + " is required to have a non-empty string callName set.");
	}
	return v;
}


void MemberAccessExpr::setCallArgs(const NodeVector& v) {
	if (!equal(v, callArgs)) {
		modify("callArgs");
		callArgs = v;
	}
}

const NodeVector& MemberAccessExpr::getCallArgs(bool required) {
	const NodeVector& v = callArgs;
	return v;
}


void MemberAccessExpr::setCallCandidates(const NodeVector& v) {
	if (!equal(v, callCandidates)) {
		modify("callCandidates");
		callCandidates = v;
	}
}

const NodeVector& MemberAccessExpr::getCallCandidates(bool required) {
	const NodeVector& v = callCandidates;
	return v;
}


void MemberAccessExpr::setSelectedCallCandidate(const NodePtr& v) {
	if (v && !v->isKindOf(kCallCandidate)) {
		throw std::runtime_error("'selectedCallCandidate' of " + id.str() + " needs to be of kind {CallCandidate} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
	}
	if (!v && selectedCallCandidate) {
		modify("selectedCallCandidate");
		selectedCallCandidate.reset();
	}
	if (!selectedCallCandidate || v->getId() != selectedCallCandidate.id) {
		modify("selectedCallCandidate");
		selectedCallCandidate.set(v);
	}
}

void MemberAccessExpr::setSelectedCallCandidate(const NodeId& v) {
	if (v != selectedCallCandidate.id) {
		modify("selectedCallCandidate");
		selectedCallCandidate.set(v);
	}
}

const NodePtr& MemberAccessExpr::getSelectedCallCandidate(bool required) {
	const NodePtr& v = selectedCallCandidate.get(repository);
	if (required && !v) {
		throw std::runtime_error("Node " + getId().str() + " is required to have selectedCallCandidate set to a non-null value.");
	}
	return v;
}


void MemberAccessExpr::encode(Encoder& e) {
	e.encode(this->graphPrev);
	e.encode(this->expr);
	e.encode(this->name);
	e.encode(this->possibleType);
	e.encode(this->requiredType);
	e.encode(this->actualType);
	e.encode(this->callName);
	e.encode(this->callArgs);
	e.encode(this->callCandidates);
	e.encode(this->selectedCallCandidate);
}

void MemberAccessExpr::decode(Decoder& d) {
	d.decode(this->graphPrev);
	d.decode(this->expr);
	d.decode(this->name);
	d.decode(this->possibleType);
	d.decode(this->requiredType);
	d.decode(this->actualType);
	d.decode(this->callName);
	d.decode(this->callArgs);
	d.decode(this->callCandidates);
	d.decode(this->selectedCallCandidate);
}


void MemberAccessExpr::updateHierarchyOfChildren() {
	if (this->expr) this->expr->updateHierarchy(id + "expr", repository, this);
	if (this->possibleType) this->possibleType->updateHierarchy(id + "possibleType", repository, this);
	if (this->requiredType) this->requiredType->updateHierarchy(id + "requiredType", repository, this);
	if (this->actualType) this->actualType->updateHierarchy(id + "actualType", repository, this);
	for (int i = 0; i < this->callArgs.size(); i++) {
		char buf[32]; snprintf(buf, 31, "%i", i);
		this->callArgs[i]->updateHierarchy((id + "callArgs") + buf, repository, this);
	}
	for (int i = 0; i < this->callCandidates.size(); i++) {
		char buf[32]; snprintf(buf, 31, "%i", i);
		this->callCandidates[i]->updateHierarchy((id + "callCandidates") + buf, repository, this);
	}
}

const NodePtr& MemberAccessExpr::resolvePath(const std::string& path) {
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
		// call.*
		if (size >= 4 && path[0] == 'c' && path[1] == 'a' && path[2] == 'l' && path[3] == 'l') {
			// callArgs.*
			if (size >= 8 && path[4] == 'A' && path[5] == 'r' && path[6] == 'g' && path[7] == 's') {
				// callArgs
				if (size == 8) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[8] == '.') {
					size_t dot = path.find(".", 9);
					string idx_str = path.substr(9, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getCallArgs();
					if (idx < 0 || idx >= a.size()) {
						throw std::runtime_error("Index into array '" + path.substr(0, 8) + "' is out of bounds.");
					}
					if (dot == string::npos) {
						return a[idx];
					} else {
						return a[idx]->resolvePath(path.substr(dot + 1));
					}
				}
			}
			// callCandidates.*
			if (size >= 14 && path[4] == 'C' && path[5] == 'a' && path[6] == 'n' && path[7] == 'd' && path[8] == 'i' && path[9] == 'd' && path[10] == 'a' && path[11] == 't' && path[12] == 'e' && path[13] == 's') {
				// callCandidates
				if (size == 14) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[14] == '.') {
					size_t dot = path.find(".", 15);
					string idx_str = path.substr(15, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getCallCandidates();
					if (idx < 0 || idx >= a.size()) {
						throw std::runtime_error("Index into array '" + path.substr(0, 14) + "' is out of bounds.");
					}
					if (dot == string::npos) {
						return a[idx];
					} else {
						return a[idx]->resolvePath(path.substr(dot + 1));
					}
				}
			}
		}
		// expr.*
		if (size >= 4 && path[0] == 'e' && path[1] == 'x' && path[2] == 'p' && path[3] == 'r') {
			// expr
			if (size == 4) {
				return getExpr();
			} else if (path[4] == '.') {
				return getExpr()->resolvePath(path.substr(5));
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
		// selectedCallCandidate.*
		if (size >= 21 && path[0] == 's' && path[1] == 'e' && path[2] == 'l' && path[3] == 'e' && path[4] == 'c' && path[5] == 't' && path[6] == 'e' && path[7] == 'd' && path[8] == 'C' && path[9] == 'a' && path[10] == 'l' && path[11] == 'l' && path[12] == 'C' && path[13] == 'a' && path[14] == 'n' && path[15] == 'd' && path[16] == 'i' && path[17] == 'd' && path[18] == 'a' && path[19] == 't' && path[20] == 'e') {
			// selectedCallCandidate
			if (size == 21) {
				return getSelectedCallCandidate();
			} else if (path[21] == '.') {
				return getSelectedCallCandidate()->resolvePath(path.substr(22));
			}
		}
	}
	throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
}

NodeVector MemberAccessExpr::getChildren() {
	NodeVector v;
	if (const NodePtr& n = this->getExpr(false)) v.push_back(n);
	v.insert(v.end(), this->callArgs.begin(), this->callArgs.end());
	v.insert(v.end(), this->callCandidates.begin(), this->callCandidates.end());
	return v;
}
