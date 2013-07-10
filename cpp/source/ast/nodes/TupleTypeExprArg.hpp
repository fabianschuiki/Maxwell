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

class TupleTypeExprArg : public Node
{
public:
	TupleTypeExprArg() : Node(),
		interfaceGraph(this),
		interfaceTypeExpr(this),
		interfaceNamed(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kTupleTypeExprArg;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kGraphInterface) return true;
		if (i == kTypeExprInterface) return true;
		if (i == kNamedInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "TupleTypeExprArg"; }

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
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType)) {
			throw runtime_error("'evaluatedType' needs to be of kind {GenericType, DefinedType, UnionType, TupleType} or implement interface {}, got " + v->getClassName() + " instead.");
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

	void setExpr(const NodePtr& v)
	{
		if (v && !v->isKindOf(kNamedTypeExpr) && !v->isKindOf(kUnionTypeExpr) && !v->isKindOf(kTupleTypeExpr)) {
			throw runtime_error("'expr' needs to be of kind {NamedTypeExpr, UnionTypeExpr, TupleTypeExpr} or implement interface {}, got " + v->getClassName() + " instead.");
		}
		if (v != expr) {
			modify();
			expr = v;
		}
	}
	const NodePtr& getExpr(bool required = true)
	{
		const NodePtr& v = expr;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have expr set to a non-null value.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "TupleTypeExprArg{…}";
		stringstream str, b;
		str << "TupleTypeExprArg{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = " << "\033[36m" << this->graphPrev.id << "\033[0m";
		if (this->evaluatedType) b << endl << "  \033[1mevaluatedType\033[0m = " << indent(this->evaluatedType->describe(depth-1));
		if (!this->name.empty()) b << endl << "  \033[1mname\033[0m = '\033[33m" << this->name << "\033[0m'";
		if (this->expr) b << endl << "  \033[1mexpr\033[0m = " << indent(this->expr->describe(depth-1));
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
		e.encode(this->expr);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->evaluatedType);
		d.decode(this->name);
		d.decode(this->expr);
	}

	virtual void updateHierarchy(const NodeId& id, Repository* repository = NULL, Node* parent = NULL)
	{
		Node::updateHierarchy(id, repository, parent);
		if (this->evaluatedType) this->evaluatedType->updateHierarchy(id + "evaluatedType", repository, this);
		if (this->expr) this->expr->updateHierarchy(id + "expr", repository, this);
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// .*
		if (true) {
			// e.*
			if (size >= 1 && path[0] == 'e') {
				// evaluatedType.*
				if (size >= 13 && path[1] == 'v' && path[2] == 'a' && path[3] == 'l' && path[4] == 'u' && path[5] == 'a' && path[6] == 't' && path[7] == 'e' && path[8] == 'd' && path[9] == 'T' && path[10] == 'y' && path[11] == 'p' && path[12] == 'e') {
					// evaluatedType
					if (size == 13) {
						return getEvaluatedType();
					} else if (path[13] == '.') {
						return getEvaluatedType()->resolvePath(path.substr(14));
					}
				}
				// expr.*
				if (size >= 4 && path[1] == 'x' && path[2] == 'p' && path[3] == 'r') {
					// expr
					if (size == 4) {
						return getExpr();
					} else if (path[4] == '.') {
						return getExpr()->resolvePath(path.substr(5));
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
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		if (const NodePtr& n = this->getExpr(false)) v.push_back(n);
		return v;
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual TypeExprInterface* asTypeExpr() { return &this->interfaceTypeExpr; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }

protected:
	NodeRef graphPrev;
	NodePtr evaluatedType;
	string name;
	NodePtr expr;

	// Interfaces
	GraphInterfaceImpl<TupleTypeExprArg> interfaceGraph;
	TypeExprInterfaceImpl<TupleTypeExprArg> interfaceTypeExpr;
	NamedInterfaceImpl<TupleTypeExprArg> interfaceNamed;
};

} // namespace ast