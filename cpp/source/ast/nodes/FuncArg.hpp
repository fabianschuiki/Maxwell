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

class FuncArg : public Node
{
public:
	FuncArg() : Node(),
		interfaceGraph(this),
		interfaceType(this),
		interfaceVariable(this),
		interfaceCallableArg(this),
		interfaceNamed(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kFuncArg;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kGraphInterface) return true;
		if (i == kTypeInterface) return true;
		if (i == kVariableInterface) return true;
		if (i == kCallableArgInterface) return true;
		if (i == kNamedInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "FuncArg"; }

	void setGraphPrev(const NodePtr& v)
	{
		if (!v && graphPrev) {
			modify("graphPrev");
			graphPrev.reset();
		}
		if (!graphPrev || v->getId() != graphPrev.id) {
			modify("graphPrev");
			graphPrev.set(v);
		}
	}
	void setGraphPrev(const NodeId& v)
	{
		if (v != graphPrev.id) {
			modify("graphPrev");
			graphPrev.set(v);
		}
	}
	const NodePtr& getGraphPrev(bool required = true)
	{
		const NodePtr& v = graphPrev.get(repository);
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
		}
		return v;
	}

	void setTypeExpr(const NodePtr& v)
	{
		if (v && !v->isKindOf(kNamedTypeExpr) && !v->isKindOf(kNilTypeExpr) && !v->isKindOf(kUnionTypeExpr) && !v->isKindOf(kTupleTypeExpr) && !v->isKindOf(kQualifiedTypeExpr) && !v->isKindOf(kSpecializedTypeExpr)) {
			throw runtime_error("'typeExpr' of " + id.str() + " needs to be of kind {NamedTypeExpr, NilTypeExpr, UnionTypeExpr, TupleTypeExpr, QualifiedTypeExpr, SpecializedTypeExpr} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, typeExpr)) {
			modify("typeExpr");
			typeExpr = v;
		}
	}
	const NodePtr& getTypeExpr(bool required = true)
	{
		const NodePtr& v = typeExpr;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have typeExpr set to a non-null value.");
		}
		return v;
	}

	void setPossibleType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType)) {
			throw runtime_error("'possibleType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType)) {
			throw runtime_error("'requiredType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType)) {
			throw runtime_error("'actualType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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

	void setName(const string& v)
	{
		if (!equal(v, name)) {
			modify("name");
			name = v;
		}
	}
	const string& getName(bool required = true)
	{
		const string& v = name;
		if (required && v.empty()) {
			throw runtime_error("Node " + getId().str() + " is required to have a non-empty string name set.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		stringstream str, b;
		if (depth == 0) return "FuncArg{…}";
		str << "FuncArg{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
		if (this->typeExpr) b << endl << "  \033[1mtypeExpr\033[0m = " << indent(this->typeExpr->describe(depth-1));
		if (this->possibleType) b << endl << "  \033[1mpossibleType\033[0m = " << indent(this->possibleType->describe(depth-1));
		if (this->requiredType) b << endl << "  \033[1mrequiredType\033[0m = " << indent(this->requiredType->describe(depth-1));
		if (this->actualType) b << endl << "  \033[1mactualType\033[0m = " << indent(this->actualType->describe(depth-1));
		if (!this->name.empty()) b << endl << "  \033[1mname\033[0m = \033[33m\"" << this->name << "\"\033[0m";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
		e.encode(this->typeExpr);
		e.encode(this->possibleType);
		e.encode(this->requiredType);
		e.encode(this->actualType);
		e.encode(this->name);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->typeExpr);
		d.decode(this->possibleType);
		d.decode(this->requiredType);
		d.decode(this->actualType);
		d.decode(this->name);
	}

	virtual void updateHierarchyOfChildren()
	{
		if (this->typeExpr) this->typeExpr->updateHierarchy(id + "typeExpr", repository, this);
		if (this->possibleType) this->possibleType->updateHierarchy(id + "possibleType", repository, this);
		if (this->requiredType) this->requiredType->updateHierarchy(id + "requiredType", repository, this);
		if (this->actualType) this->actualType->updateHierarchy(id + "actualType", repository, this);
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
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

	virtual NodeVector getChildren()
	{
		NodeVector v;
		if (const NodePtr& n = this->getTypeExpr(false)) v.push_back(n);
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<FuncArg>& other = boost::dynamic_pointer_cast<FuncArg>(o);
		if (!other) return false;
		if (!equal(this->graphPrev, other->graphPrev)) return false;
		if (!equal(this->typeExpr, other->typeExpr)) return false;
		if (!equal(this->possibleType, other->possibleType)) return false;
		if (!equal(this->requiredType, other->requiredType)) return false;
		if (!equal(this->actualType, other->actualType)) return false;
		if (!equal(this->name, other->name)) return false;
		return true;
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual TypeInterface* asType() { return &this->interfaceType; }
	virtual VariableInterface* asVariable() { return &this->interfaceVariable; }
	virtual CallableArgInterface* asCallableArg() { return &this->interfaceCallableArg; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }

	typedef boost::shared_ptr<FuncArg> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<FuncArg>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<FuncArg>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to FuncArg."); return r; }
protected:
	NodeRef graphPrev;
	NodePtr typeExpr;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;
	string name;

	// Interfaces
	GraphInterfaceImpl<FuncArg> interfaceGraph;
	TypeInterfaceImpl<FuncArg> interfaceType;
	VariableInterfaceImpl<FuncArg> interfaceVariable;
	CallableArgInterfaceImpl<FuncArg> interfaceCallableArg;
	NamedInterfaceImpl<FuncArg> interfaceNamed;
};

} // namespace ast