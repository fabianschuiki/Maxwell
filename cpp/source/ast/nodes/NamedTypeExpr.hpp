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

class NamedTypeExpr : public Node
{
public:
	NamedTypeExpr() : Node(),
		interfaceGraph(this),
		interfaceTypeExpr(this),
		interfaceNamed(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kNamedTypeExpr;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kGraphInterface) return true;
		if (i == kTypeExprInterface) return true;
		if (i == kNamedInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "NamedTypeExpr"; }

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

	void setEvaluatedType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet)) {
			throw runtime_error("'evaluatedType' needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType, FuncType, TypeSet} or implement interface {}, got " + v->getClassName() + " instead.");
		}
		if (v != evaluatedType) {
			modify();
			evaluatedType = v;
		}
	}
	const NodePtr& getEvaluatedType(bool required = true)
	{
		const NodePtr& v = evaluatedType;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have evaluatedType set to a non-null value.");
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

	void setDefinition(const NodePtr& v)
	{
		if (!v && definition) {
			modify();
			definition.reset();
		}
		if (!definition || v->getId() != definition.id) {
			modify();
			definition.set(v);
		}
	}
	void setDefinition(const NodeId& v)
	{
		if (v != definition.id) {
			modify();
			definition.set(v);
		}
	}
	const NodePtr& getDefinition(bool required = true)
	{
		const NodePtr& v = definition.get(repository);
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have definition set to a non-null value.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "NamedTypeExpr{…}";
		stringstream str, b;
		str << "NamedTypeExpr{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = " << "\033[36m" << this->graphPrev.id << "\033[0m";
		if (this->evaluatedType) b << endl << "  \033[1mevaluatedType\033[0m = " << indent(this->evaluatedType->describe(depth-1));
		if (!this->name.empty()) b << endl << "  \033[1mname\033[0m = '\033[33m" << this->name << "\033[0m'";
		if (this->definition) b << endl << "  \033[1mdefinition\033[0m = " << "\033[36m" << this->definition.id << "\033[0m";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
		e.encode(this->evaluatedType);
		e.encode(this->name);
		e.encode(this->definition);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->evaluatedType);
		d.decode(this->name);
		d.decode(this->definition);
	}

	virtual void updateHierarchyOfChildren()
	{
		if (this->evaluatedType) this->evaluatedType->updateHierarchy(id + "evaluatedType", repository, this);
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// .*
		if (true) {
			// definition.*
			if (size >= 10 && path[0] == 'd' && path[1] == 'e' && path[2] == 'f' && path[3] == 'i' && path[4] == 'n' && path[5] == 'i' && path[6] == 't' && path[7] == 'i' && path[8] == 'o' && path[9] == 'n') {
				// definition
				if (size == 10) {
					return getDefinition();
				} else if (path[10] == '.') {
					return getDefinition()->resolvePath(path.substr(11));
				}
			}
			// evaluatedType.*
			if (size >= 13 && path[0] == 'e' && path[1] == 'v' && path[2] == 'a' && path[3] == 'l' && path[4] == 'u' && path[5] == 'a' && path[6] == 't' && path[7] == 'e' && path[8] == 'd' && path[9] == 'T' && path[10] == 'y' && path[11] == 'p' && path[12] == 'e') {
				// evaluatedType
				if (size == 13) {
					return getEvaluatedType();
				} else if (path[13] == '.') {
					return getEvaluatedType()->resolvePath(path.substr(14));
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
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		if (const NodePtr& n = this->getEvaluatedType(false)) v.push_back(n);
		return v;
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual TypeExprInterface* asTypeExpr() { return &this->interfaceTypeExpr; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }

	typedef boost::shared_ptr<NamedTypeExpr> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<NamedTypeExpr>(n); }
protected:
	NodeRef graphPrev;
	NodePtr evaluatedType;
	string name;
	NodeRef definition;

	// Interfaces
	GraphInterfaceImpl<NamedTypeExpr> interfaceGraph;
	TypeExprInterfaceImpl<NamedTypeExpr> interfaceTypeExpr;
	NamedInterfaceImpl<NamedTypeExpr> interfaceNamed;
};

} // namespace ast