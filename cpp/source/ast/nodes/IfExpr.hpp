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

class IfExpr : public Node
{
public:
	IfExpr() : Node(),
		interfaceGraph(this),
		interfaceType(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kIfExpr;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kGraphInterface) return true;
		if (i == kTypeInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "IfExpr"; }

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

	void setPossibleType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType)) {
			throw runtime_error("'possibleType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType)) {
			throw runtime_error("'requiredType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType)) {
			throw runtime_error("'actualType' of " + id.str() + " needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
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

	void setCond(const NodePtr& v)
	{
		if (v && !v->implements(kTypeInterface)) {
			throw runtime_error("'cond' of " + id.str() + " needs to be of kind {} or implement interface {Type}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, cond)) {
			modify("cond");
			cond = v;
		}
	}
	const NodePtr& getCond(bool required = true)
	{
		const NodePtr& v = cond;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have cond set to a non-null value.");
		}
		return v;
	}

	void setBody(const NodePtr& v)
	{
		if (v && !v->implements(kTypeInterface)) {
			throw runtime_error("'body' of " + id.str() + " needs to be of kind {} or implement interface {Type}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, body)) {
			modify("body");
			body = v;
		}
	}
	const NodePtr& getBody(bool required = true)
	{
		const NodePtr& v = body;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have body set to a non-null value.");
		}
		return v;
	}

	void setElseExpr(const NodePtr& v)
	{
		if (v && !v->implements(kTypeInterface)) {
			throw runtime_error("'elseExpr' of " + id.str() + " needs to be of kind {} or implement interface {Type}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, elseExpr)) {
			modify("elseExpr");
			elseExpr = v;
		}
	}
	const NodePtr& getElseExpr(bool required = true)
	{
		const NodePtr& v = elseExpr;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have elseExpr set to a non-null value.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "IfExpr{…}";
		stringstream str, b;
		str << "IfExpr{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
		if (this->possibleType) b << endl << "  \033[1mpossibleType\033[0m = " << indent(this->possibleType->describe(depth-1));
		if (this->requiredType) b << endl << "  \033[1mrequiredType\033[0m = " << indent(this->requiredType->describe(depth-1));
		if (this->actualType) b << endl << "  \033[1mactualType\033[0m = " << indent(this->actualType->describe(depth-1));
		if (this->cond) b << endl << "  \033[1mcond\033[0m = " << indent(this->cond->describe(depth-1));
		if (this->body) b << endl << "  \033[1mbody\033[0m = " << indent(this->body->describe(depth-1));
		if (this->elseExpr) b << endl << "  \033[1melseExpr\033[0m = " << indent(this->elseExpr->describe(depth-1));
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
		e.encode(this->cond);
		e.encode(this->body);
		e.encode(this->elseExpr);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->possibleType);
		d.decode(this->requiredType);
		d.decode(this->actualType);
		d.decode(this->cond);
		d.decode(this->body);
		d.decode(this->elseExpr);
	}

	virtual void updateHierarchyOfChildren()
	{
		if (this->possibleType) this->possibleType->updateHierarchy(id + "possibleType", repository, this);
		if (this->requiredType) this->requiredType->updateHierarchy(id + "requiredType", repository, this);
		if (this->actualType) this->actualType->updateHierarchy(id + "actualType", repository, this);
		if (this->cond) this->cond->updateHierarchy(id + "cond", repository, this);
		if (this->body) this->body->updateHierarchy(id + "body", repository, this);
		if (this->elseExpr) this->elseExpr->updateHierarchy(id + "elseExpr", repository, this);
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
			// body.*
			if (size >= 4 && path[0] == 'b' && path[1] == 'o' && path[2] == 'd' && path[3] == 'y') {
				// body
				if (size == 4) {
					return getBody();
				} else if (path[4] == '.') {
					return getBody()->resolvePath(path.substr(5));
				}
			}
			// cond.*
			if (size >= 4 && path[0] == 'c' && path[1] == 'o' && path[2] == 'n' && path[3] == 'd') {
				// cond
				if (size == 4) {
					return getCond();
				} else if (path[4] == '.') {
					return getCond()->resolvePath(path.substr(5));
				}
			}
			// elseExpr.*
			if (size >= 8 && path[0] == 'e' && path[1] == 'l' && path[2] == 's' && path[3] == 'e' && path[4] == 'E' && path[5] == 'x' && path[6] == 'p' && path[7] == 'r') {
				// elseExpr
				if (size == 8) {
					return getElseExpr();
				} else if (path[8] == '.') {
					return getElseExpr()->resolvePath(path.substr(9));
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
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		if (const NodePtr& n = this->getCond(false)) v.push_back(n);
		if (const NodePtr& n = this->getBody(false)) v.push_back(n);
		if (const NodePtr& n = this->getElseExpr(false)) v.push_back(n);
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<IfExpr>& other = boost::dynamic_pointer_cast<IfExpr>(o);
		if (!other) return false;
		if (!equal(this->graphPrev, other->graphPrev)) return false;
		if (!equal(this->possibleType, other->possibleType)) return false;
		if (!equal(this->requiredType, other->requiredType)) return false;
		if (!equal(this->actualType, other->actualType)) return false;
		if (!equal(this->cond, other->cond)) return false;
		if (!equal(this->body, other->body)) return false;
		if (!equal(this->elseExpr, other->elseExpr)) return false;
		return true;
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual TypeInterface* asType() { return &this->interfaceType; }

	typedef boost::shared_ptr<IfExpr> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<IfExpr>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<IfExpr>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to IfExpr."); return r; }
protected:
	NodeRef graphPrev;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;
	NodePtr cond;
	NodePtr body;
	NodePtr elseExpr;

	// Interfaces
	GraphInterfaceImpl<IfExpr> interfaceGraph;
	TypeInterfaceImpl<IfExpr> interfaceType;
};

} // namespace ast