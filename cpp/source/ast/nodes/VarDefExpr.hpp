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

class VarDefExpr : public Node
{
public:
	VarDefExpr() : Node(),
		interfaceGraph(this),
		interfaceType(this),
		interfaceVariable(this),
		interfaceNamed(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kVarDefExpr;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kGraphInterface) return true;
		if (i == kTypeInterface) return true;
		if (i == kVariableInterface) return true;
		if (i == kNamedInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "VarDefExpr"; }

	void setGraphPrev(const NodePtr& v)
	{
		if (!v && graphPrev) {
			modify();
			graphPrev.reset();
		}
		if (!graphPrev || v->getId() != graphPrev.id) {
			modify();
			graphPrev.set(v);
		}
	}
	void setGraphPrev(const NodeId& v)
	{
		if (v != graphPrev.id) {
			modify();
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

	void setPossibleType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType)) {
			throw runtime_error("'possibleType' needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType} or implement interface {}, got " + v->getClassName() + " instead.");
		}
		if (v != possibleType) {
			modify();
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
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType)) {
			throw runtime_error("'requiredType' needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType} or implement interface {}, got " + v->getClassName() + " instead.");
		}
		if (v != requiredType) {
			modify();
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
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType)) {
			throw runtime_error("'actualType' needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType} or implement interface {}, got " + v->getClassName() + " instead.");
		}
		if (v != actualType) {
			modify();
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
		if (v != name) {
			modify();
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

	void setType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kNamedTypeExpr) && !v->isKindOf(kUnionTypeExpr) && !v->isKindOf(kTupleTypeExpr)) {
			throw runtime_error("'type' needs to be of kind {NamedTypeExpr, UnionTypeExpr, TupleTypeExpr} or implement interface {}, got " + v->getClassName() + " instead.");
		}
		if (v != type) {
			modify();
			type = v;
		}
	}
	const NodePtr& getType(bool required = true)
	{
		const NodePtr& v = type;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have type set to a non-null value.");
		}
		return v;
	}

	void setInitialExpr(const NodePtr& v)
	{
		if (v && !v->implements(kTypeInterface)) {
			throw runtime_error("'initialExpr' needs to be of kind {} or implement interface {Type}, got " + v->getClassName() + " instead.");
		}
		if (v != initialExpr) {
			modify();
			initialExpr = v;
		}
	}
	const NodePtr& getInitialExpr(bool required = true)
	{
		const NodePtr& v = initialExpr;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have initialExpr set to a non-null value.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "VarDefExpr{…}";
		stringstream str, b;
		str << "VarDefExpr{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = " << "\033[36m" << this->graphPrev.id << "\033[0m";
		if (this->possibleType) b << endl << "  \033[1mpossibleType\033[0m = " << indent(this->possibleType->describe(depth-1));
		if (this->requiredType) b << endl << "  \033[1mrequiredType\033[0m = " << indent(this->requiredType->describe(depth-1));
		if (this->actualType) b << endl << "  \033[1mactualType\033[0m = " << indent(this->actualType->describe(depth-1));
		if (!this->name.empty()) b << endl << "  \033[1mname\033[0m = '\033[33m" << this->name << "\033[0m'";
		if (this->type) b << endl << "  \033[1mtype\033[0m = " << indent(this->type->describe(depth-1));
		if (this->initialExpr) b << endl << "  \033[1minitialExpr\033[0m = " << indent(this->initialExpr->describe(depth-1));
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
		e.encode(this->possibleType);
		e.encode(this->requiredType);
		e.encode(this->actualType);
		e.encode(this->name);
		e.encode(this->type);
		e.encode(this->initialExpr);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->possibleType);
		d.decode(this->requiredType);
		d.decode(this->actualType);
		d.decode(this->name);
		d.decode(this->type);
		d.decode(this->initialExpr);
	}

	virtual void updateHierarchyOfChildren()
	{
		if (this->possibleType) this->possibleType->updateHierarchy(id + "possibleType", repository, this);
		if (this->requiredType) this->requiredType->updateHierarchy(id + "requiredType", repository, this);
		if (this->actualType) this->actualType->updateHierarchy(id + "actualType", repository, this);
		if (this->type) this->type->updateHierarchy(id + "type", repository, this);
		if (this->initialExpr) this->initialExpr->updateHierarchy(id + "initialExpr", repository, this);
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
			// initialExpr.*
			if (size >= 11 && path[0] == 'i' && path[1] == 'n' && path[2] == 'i' && path[3] == 't' && path[4] == 'i' && path[5] == 'a' && path[6] == 'l' && path[7] == 'E' && path[8] == 'x' && path[9] == 'p' && path[10] == 'r') {
				// initialExpr
				if (size == 11) {
					return getInitialExpr();
				} else if (path[11] == '.') {
					return getInitialExpr()->resolvePath(path.substr(12));
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
			// type.*
			if (size >= 4 && path[0] == 't' && path[1] == 'y' && path[2] == 'p' && path[3] == 'e') {
				// type
				if (size == 4) {
					return getType();
				} else if (path[4] == '.') {
					return getType()->resolvePath(path.substr(5));
				}
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		if (const NodePtr& n = this->getType(false)) v.push_back(n);
		if (const NodePtr& n = this->getInitialExpr(false)) v.push_back(n);
		return v;
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual TypeInterface* asType() { return &this->interfaceType; }
	virtual VariableInterface* asVariable() { return &this->interfaceVariable; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }

protected:
	NodeRef graphPrev;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;
	string name;
	NodePtr type;
	NodePtr initialExpr;

	// Interfaces
	GraphInterfaceImpl<VarDefExpr> interfaceGraph;
	TypeInterfaceImpl<VarDefExpr> interfaceType;
	VariableInterfaceImpl<VarDefExpr> interfaceVariable;
	NamedInterfaceImpl<VarDefExpr> interfaceNamed;
};

} // namespace ast