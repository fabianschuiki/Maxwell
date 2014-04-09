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
#include <cstdio>

namespace ast {

using std::vector;
using std::string;
using std::stringstream;
using std::endl;
using std::runtime_error;

class SpecializedTypeExpr : public Node
{
public:
	SpecializedTypeExpr() : Node(),
		interfaceTypeExpr(this),
		interfaceGraph(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kSpecializedTypeExpr;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kTypeExprInterface) return true;
		if (i == kGraphInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "SpecializedTypeExpr"; }

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

	void setEvaluatedType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
			throw runtime_error("'evaluatedType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, evaluatedType)) {
			modify("evaluatedType");
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

	void setExpr(const NodePtr& v)
	{
		if (v && !v->isKindOf(kNamedTypeExpr) && !v->isKindOf(kNilTypeExpr) && !v->isKindOf(kUnionTypeExpr) && !v->isKindOf(kTupleTypeExpr) && !v->isKindOf(kQualifiedTypeExpr) && !v->isKindOf(kSpecializedTypeExpr)) {
			throw runtime_error("'expr' of " + id.str() + " needs to be of kind {NamedTypeExpr, NilTypeExpr, UnionTypeExpr, TupleTypeExpr, QualifiedTypeExpr, SpecializedTypeExpr} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, expr)) {
			modify("expr");
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

	void setSpecExprs(const NodeVector& v)
	{
		if (!equal(v, specExprs)) {
			modify("specExprs");
			specExprs = v;
		}
	}
	const NodeVector& getSpecExprs(bool required = true)
	{
		const NodeVector& v = specExprs;
		return v;
	}

	virtual string describe(int depth = -1)
	{
		stringstream str, b;
		if (depth == 0) return "SpecializedTypeExpr{…}";
		str << "SpecializedTypeExpr{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
		if (this->evaluatedType) b << endl << "  \033[1mevaluatedType\033[0m = " << indent(this->evaluatedType->describe(depth-1));
		if (this->expr) b << endl << "  \033[1mexpr\033[0m = " << indent(this->expr->describe(depth-1));
		if (!this->specExprs.empty()) b << endl << "  \033[1mspecExprs\033[0m = " << indent(describeVector(this->specExprs, depth-1));
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
		e.encode(this->evaluatedType);
		e.encode(this->expr);
		e.encode(this->specExprs);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->evaluatedType);
		d.decode(this->expr);
		d.decode(this->specExprs);
	}

	virtual void updateHierarchyOfChildren()
	{
		if (this->evaluatedType) this->evaluatedType->updateHierarchy(id + "evaluatedType", repository, this);
		if (this->expr) this->expr->updateHierarchy(id + "expr", repository, this);
		for (int i = 0; i < this->specExprs.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->specExprs[i]->updateHierarchy((id + "specExprs") + buf, repository, this);
		}
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
			// specExprs.*
			if (size >= 9 && path[0] == 's' && path[1] == 'p' && path[2] == 'e' && path[3] == 'c' && path[4] == 'E' && path[5] == 'x' && path[6] == 'p' && path[7] == 'r' && path[8] == 's') {
				// specExprs
				if (size == 9) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[9] == '.') {
					size_t dot = path.find(".", 10);
					string idx_str = path.substr(10, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getSpecExprs();
					if (idx < 0 || idx >= a.size()) {
						throw std::runtime_error("Index into array '" + path.substr(0, 9) + "' is out of bounds.");
					}
					if (dot == string::npos) {
						return a[idx];
					} else {
						return a[idx]->resolvePath(path.substr(dot + 1));
					}
				}
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		if (const NodePtr& n = this->getEvaluatedType(false)) v.push_back(n);
		if (const NodePtr& n = this->getExpr(false)) v.push_back(n);
		v.insert(v.end(), this->specExprs.begin(), this->specExprs.end());
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<SpecializedTypeExpr>& other = boost::dynamic_pointer_cast<SpecializedTypeExpr>(o);
		if (!other) return false;
		if (!equal(this->graphPrev, other->graphPrev)) return false;
		if (!equal(this->evaluatedType, other->evaluatedType)) return false;
		if (!equal(this->expr, other->expr)) return false;
		if (!equal(this->specExprs, other->specExprs)) return false;
		return true;
	}

	// Interfaces
	virtual TypeExprInterface* asTypeExpr() { return &this->interfaceTypeExpr; }
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }

	typedef boost::shared_ptr<SpecializedTypeExpr> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<SpecializedTypeExpr>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<SpecializedTypeExpr>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to SpecializedTypeExpr."); return r; }
protected:
	NodeRef graphPrev;
	NodePtr evaluatedType;
	NodePtr expr;
	NodeVector specExprs;

	// Interfaces
	TypeExprInterfaceImpl<SpecializedTypeExpr> interfaceTypeExpr;
	GraphInterfaceImpl<SpecializedTypeExpr> interfaceGraph;
};

} // namespace ast