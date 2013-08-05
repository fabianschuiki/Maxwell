/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
#include "../Coder.hpp"
#include "interfaces.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <boost/smart_ptr.hpp>
#include <stdexcept>

namespace ast {

using std::vector;
using std::string;
using std::stringstream;
using std::endl;
using std::runtime_error;

class CallCandidate : public Node
{
public:
	CallCandidate() : Node(),
		interfaceType(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kCallCandidate;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kTypeInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "CallCandidate"; }

	void setFunc(const NodePtr& v)
	{
		if (v && !v->implements(kCallableInterface)) {
			throw runtime_error("'func' of " + id.str() + " needs to be of kind {} or implement interface {Callable}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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
	void setFunc(const NodeId& v)
	{
		if (v != func.id) {
			modify("func");
			func.set(v);
		}
	}
	const NodePtr& getFunc(bool required = true)
	{
		const NodePtr& v = func.get(repository);
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have func set to a non-null value.");
		}
		return v;
	}

	void setArgs(const NodeVector& v)
	{
		if (!equal(v, args)) {
			modify("args");
			args = v;
		}
	}
	const NodeVector& getArgs(bool required = true)
	{
		const NodeVector& v = args;
		return v;
	}

	void setFeasible(const bool& v)
	{
		if (!equal(v, feasible)) {
			modify("feasible");
			feasible = v;
		}
	}
	const bool& getFeasible(bool required = true)
	{
		const bool& v = feasible;
		return v;
	}

	void setCost(const int& v)
	{
		if (!equal(v, cost)) {
			modify("cost");
			cost = v;
		}
	}
	const int& getCost(bool required = true)
	{
		const int& v = cost;
		return v;
	}

	void setPossibleType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType)) {
			throw runtime_error("'possibleType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, possibleType)) {
			modify("possibleType");
			possibleType = v;
		}
	}
	const NodePtr& getPossibleType(bool required = true)
	{
		const NodePtr& v = possibleType;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have possibleType set to a non-null value.");
		}
		return v;
	}

	void setRequiredType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType)) {
			throw runtime_error("'requiredType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, requiredType)) {
			modify("requiredType");
			requiredType = v;
		}
	}
	const NodePtr& getRequiredType(bool required = true)
	{
		const NodePtr& v = requiredType;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have requiredType set to a non-null value.");
		}
		return v;
	}

	void setActualType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType)) {
			throw runtime_error("'actualType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, actualType)) {
			modify("actualType");
			actualType = v;
		}
	}
	const NodePtr& getActualType(bool required = true)
	{
		const NodePtr& v = actualType;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have actualType set to a non-null value.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		stringstream str, b;
		if (depth == 0) return "CallCandidate{…}";
		str << "CallCandidate{";
		if (this->func) b << endl << "  \033[1mfunc\033[0m = \033[36m" << this->func.id << "\033[0m";
		if (!this->args.empty()) b << endl << "  \033[1margs\033[0m = " << indent(describeVector(this->args, depth-1));
		b << endl << "  \033[1mfeasible\033[0m = \033[34m" << (this->feasible ? "true" : "false") << "\033[0m";
		b << endl << "  \033[1mcost\033[0m = \033[35m" << this->cost << "\033[0m";
		if (this->possibleType) b << endl << "  \033[1mpossibleType\033[0m = " << indent(this->possibleType->describe(depth-1));
		if (this->requiredType) b << endl << "  \033[1mrequiredType\033[0m = " << indent(this->requiredType->describe(depth-1));
		if (this->actualType) b << endl << "  \033[1mactualType\033[0m = " << indent(this->actualType->describe(depth-1));
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->func);
		e.encode(this->args);
		e.encode(this->feasible);
		e.encode(this->cost);
		e.encode(this->possibleType);
		e.encode(this->requiredType);
		e.encode(this->actualType);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->func);
		d.decode(this->args);
		d.decode(this->feasible);
		d.decode(this->cost);
		d.decode(this->possibleType);
		d.decode(this->requiredType);
		d.decode(this->actualType);
	}

	virtual void updateHierarchyOfChildren()
	{
		for (int i = 0; i < this->args.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->args[i]->updateHierarchy((id + "args") + buf, repository, this);
		}
		if (this->possibleType) this->possibleType->updateHierarchy(id + "possibleType", repository, this);
		if (this->requiredType) this->requiredType->updateHierarchy(id + "requiredType", repository, this);
		if (this->actualType) this->actualType->updateHierarchy(id + "actualType", repository, this);
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// .*
		if (true) {
			// a.*
			if (size >= 1 && path[0] == 'a') {
				// actualType.*
				if (size >= 10 && path[1] == 'c' && path[2] == 't' && path[3] == 'u' && path[4] == 'a' && path[5] == 'l' && path[6] == 'T' && path[7] == 'y' && path[8] == 'p' && path[9] == 'e') {
					// actualType
					if (size == 10) {
						return getActualType();
					} else if (path[10] == '.') {
						return getActualType()->resolvePath(path.substr(11));
					}
				}
				// args.*
				if (size >= 4 && path[1] == 'r' && path[2] == 'g' && path[3] == 's') {
					// args
					if (size == 4) {
						throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
					} else if (path[4] == '.') {
						size_t dot = path.find(".", 5);
						string idx_str = path.substr(5, dot);
						int idx = atoi(idx_str.c_str());
						const NodeVector& a = getArgs();
						if (idx < 0 || idx >= a.size()) {
							throw std::runtime_error("Index into array '" + path.substr(0, 4) + "' is out of bounds.");
						}
						if (dot == string::npos) {
							return a[idx];
						} else {
							return a[idx]->resolvePath(path.substr(dot + 1));
						}
					}
				}
			}
			// func.*
			if (size >= 4 && path[0] == 'f' && path[1] == 'u' && path[2] == 'n' && path[3] == 'c') {
				// func
				if (size == 4) {
					return getFunc();
				} else if (path[4] == '.') {
					return getFunc()->resolvePath(path.substr(5));
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

	virtual NodeVector getChildren()
	{
		NodeVector v;
		v.insert(v.end(), this->args.begin(), this->args.end());
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<CallCandidate>& other = boost::dynamic_pointer_cast<CallCandidate>(o);
		if (!other) return false;
		if (!equal(this->func, other->func)) return false;
		if (!equal(this->args, other->args)) return false;
		if (!equal(this->feasible, other->feasible)) return false;
		if (!equal(this->cost, other->cost)) return false;
		if (!equal(this->possibleType, other->possibleType)) return false;
		if (!equal(this->requiredType, other->requiredType)) return false;
		if (!equal(this->actualType, other->actualType)) return false;
		return true;
	}

	// Interfaces
	virtual TypeInterface* asType() { return &this->interfaceType; }

	typedef boost::shared_ptr<CallCandidate> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<CallCandidate>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<CallCandidate>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to CallCandidate."); return r; }
protected:
	NodeRef func;
	NodeVector args;
	bool feasible;
	int cost;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;

	// Interfaces
	TypeInterfaceImpl<CallCandidate> interfaceType;
};

} // namespace ast