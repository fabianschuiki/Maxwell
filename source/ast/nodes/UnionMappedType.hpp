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

class UnionMappedType : public Node
{
public:
	UnionMappedType() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kUnionMappedType;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		return false;
	}

	virtual string getClassName() const { return "UnionMappedType"; }

	virtual NodePtr copy()
	{
		Ptr c (new UnionMappedType);
		Node::copy(this->in, c->in);
		Node::copy(this->out, c->out);
		return c;
	}

	void setIn(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
			throw runtime_error("'in' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, in)) {
			modify("in");
			in = v;
		}
	}
	const NodePtr& getIn(bool required = true)
	{
		const NodePtr& v = in;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have in set to a non-null value.");
		}
		return v;
	}

	void setOut(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
			throw runtime_error("'out' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, out)) {
			modify("out");
			out = v;
		}
	}
	const NodePtr& getOut(bool required = true)
	{
		const NodePtr& v = out;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have out set to a non-null value.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		stringstream str, b;
		str << out->describe(depth-1) << '(' << in->describe(depth-1) << ')';
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->in);
		e.encode(this->out);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->in);
		d.decode(this->out);
	}

	virtual void updateHierarchyOfChildren()
	{
		if (this->in) this->in->updateHierarchy(id + "in", repository, this);
		if (this->out) this->out->updateHierarchy(id + "out", repository, this);
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// .*
		if (true) {
			// in.*
			if (size >= 2 && path[0] == 'i' && path[1] == 'n') {
				// in
				if (size == 2) {
					return getIn();
				} else if (path[2] == '.') {
					return getIn()->resolvePath(path.substr(3));
				}
			}
			// out.*
			if (size >= 3 && path[0] == 'o' && path[1] == 'u' && path[2] == 't') {
				// out
				if (size == 3) {
					return getOut();
				} else if (path[3] == '.') {
					return getOut()->resolvePath(path.substr(4));
				}
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		if (const NodePtr& n = this->getIn(false)) v.push_back(n);
		if (const NodePtr& n = this->getOut(false)) v.push_back(n);
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<UnionMappedType>& other = boost::dynamic_pointer_cast<UnionMappedType>(o);
		if (!other) return false;
		if (!equal(this->in, other->in)) return false;
		if (!equal(this->out, other->out)) return false;
		return true;
	}

	typedef boost::shared_ptr<UnionMappedType> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<UnionMappedType>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<UnionMappedType>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to UnionMappedType."); return r; }
protected:
	NodePtr in;
	NodePtr out;
};

} // namespace ast