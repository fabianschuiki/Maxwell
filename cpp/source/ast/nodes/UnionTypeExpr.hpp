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

class UnionTypeExpr : public Node
{
public:
	UnionTypeExpr() : Node(),
		interfaceGraph(this),
		interfaceTypeExpr(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kUnionTypeExpr;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kGraphInterface) return true;
		if (i == kTypeExprInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "UnionTypeExpr"; }

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
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType)) {
			throw runtime_error("'evaluatedType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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

	void setTypes(const NodeVector& v)
	{
		if (!equal(v, types)) {
			modify("types");
			types = v;
		}
	}
	const NodeVector& getTypes(bool required = true)
	{
		const NodeVector& v = types;
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "UnionTypeExpr{…}";
		stringstream str, b;
		str << "UnionTypeExpr{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
		if (this->evaluatedType) b << endl << "  \033[1mevaluatedType\033[0m = " << indent(this->evaluatedType->describe(depth-1));
		if (!this->types.empty()) b << endl << "  \033[1mtypes\033[0m = " << indent(describeVector(this->types, depth-1));
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
		e.encode(this->evaluatedType);
		e.encode(this->types);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->evaluatedType);
		d.decode(this->types);
	}

	virtual void updateHierarchyOfChildren()
	{
		if (this->evaluatedType) this->evaluatedType->updateHierarchy(id + "evaluatedType", repository, this);
		for (int i = 0; i < this->types.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->types[i]->updateHierarchy((id + "types") + buf, repository, this);
		}
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// .*
		if (true) {
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
			// types.*
			if (size >= 5 && path[0] == 't' && path[1] == 'y' && path[2] == 'p' && path[3] == 'e' && path[4] == 's') {
				// types
				if (size == 5) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[5] == '.') {
					size_t dot = path.find(".", 6);
					string idx_str = path.substr(6, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getTypes();
					if (idx < 0 || idx >= a.size()) {
						throw std::runtime_error("Index into array '" + path.substr(0, 5) + "' is out of bounds.");
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
		v.insert(v.end(), this->types.begin(), this->types.end());
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<UnionTypeExpr>& other = boost::dynamic_pointer_cast<UnionTypeExpr>(o);
		if (!other) return false;
		if (!equal(this->graphPrev, other->graphPrev)) return false;
		if (!equal(this->evaluatedType, other->evaluatedType)) return false;
		if (!equal(this->types, other->types)) return false;
		return true;
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual TypeExprInterface* asTypeExpr() { return &this->interfaceTypeExpr; }

	typedef boost::shared_ptr<UnionTypeExpr> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<UnionTypeExpr>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<UnionTypeExpr>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to UnionTypeExpr."); return r; }
protected:
	NodeRef graphPrev;
	NodePtr evaluatedType;
	NodeVector types;

	// Interfaces
	GraphInterfaceImpl<UnionTypeExpr> interfaceGraph;
	TypeExprInterfaceImpl<UnionTypeExpr> interfaceTypeExpr;
};

} // namespace ast