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

class CallCandidateArg : public Node
{
public:
	CallCandidateArg() : Node(),
		interfaceType(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kCallCandidateArg;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kTypeInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "CallCandidateArg"; }

	void setArg(const NodePtr& v)
	{
		if (v && !v->implements(kCallArgInterface)) {
			throw runtime_error("'arg' of " + id.str() + " needs to be of kind {} or implement interface {CallArg}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!v && arg) {
			modify("arg");
			arg.reset();
		}
		if (!arg || v->getId() != arg.id) {
			modify("arg");
			arg.set(v);
		}
	}
	void setArg(const NodeId& v)
	{
		if (v != arg.id) {
			modify("arg");
			arg.set(v);
		}
	}
	const NodePtr& getArg(bool required = true)
	{
		const NodePtr& v = arg.get(repository);
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have arg set to a non-null value.");
		}
		return v;
	}

	void setPossibleType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType)) {
			throw runtime_error("'possibleType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType)) {
			throw runtime_error("'requiredType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType)) {
			throw runtime_error("'actualType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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
		if (depth == 0) return "CallCandidateArg{…}";
		stringstream str, b;
		str << "CallCandidateArg{";
		if (this->arg) b << endl << "  \033[1marg\033[0m = \033[36m" << this->arg.id << "\033[0m";
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
		e.encode(this->arg);
		e.encode(this->possibleType);
		e.encode(this->requiredType);
		e.encode(this->actualType);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->arg);
		d.decode(this->possibleType);
		d.decode(this->requiredType);
		d.decode(this->actualType);
	}

	virtual void updateHierarchyOfChildren()
	{
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
				// arg.*
				if (size >= 3 && path[1] == 'r' && path[2] == 'g') {
					// arg
					if (size == 3) {
						return getArg();
					} else if (path[3] == '.') {
						return getArg()->resolvePath(path.substr(4));
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

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<CallCandidateArg>& other = boost::dynamic_pointer_cast<CallCandidateArg>(o);
		if (!other) return false;
		if (!equal(this->arg, other->arg)) return false;
		if (!equal(this->possibleType, other->possibleType)) return false;
		if (!equal(this->requiredType, other->requiredType)) return false;
		if (!equal(this->actualType, other->actualType)) return false;
		return true;
	}

	// Interfaces
	virtual TypeInterface* asType() { return &this->interfaceType; }

	typedef boost::shared_ptr<CallCandidateArg> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<CallCandidateArg>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<CallCandidateArg>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to CallCandidateArg."); return r; }
protected:
	NodeRef arg;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;

	// Interfaces
	TypeInterfaceImpl<CallCandidateArg> interfaceType;
};

} // namespace ast