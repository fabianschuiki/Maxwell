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

class OneTupleMappedType : public Node
{
public:
	OneTupleMappedType() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kOneTupleMappedType;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		return false;
	}

	virtual string getClassName() const { return "OneTupleMappedType"; }

	void setTuple(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kNilType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType) && !v->isKindOf(kOneTupleMappedType) && !v->isKindOf(kCastType)) {
			throw runtime_error("'tuple' of " + id.str() + " needs to be of kind {GenericType, InvalidType, NilType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType, OneTupleMappedType, CastType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, tuple)) {
			modify("tuple");
			tuple = v;
		}
	}
	const NodePtr& getTuple(bool required = true)
	{
		const NodePtr& v = tuple;
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have tuple set to a non-null value.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		stringstream str, b;
		str << tuple->describe(depth-1) << ".0";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->tuple);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->tuple);
	}

	virtual void updateHierarchyOfChildren()
	{
		if (this->tuple) this->tuple->updateHierarchy(id + "tuple", repository, this);
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// tuple.*
		if (size >= 5 && path[0] == 't' && path[1] == 'u' && path[2] == 'p' && path[3] == 'l' && path[4] == 'e') {
			// tuple
			if (size == 5) {
				return getTuple();
			} else if (path[5] == '.') {
				return getTuple()->resolvePath(path.substr(6));
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		if (const NodePtr& n = this->getTuple(false)) v.push_back(n);
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<OneTupleMappedType>& other = boost::dynamic_pointer_cast<OneTupleMappedType>(o);
		if (!other) return false;
		if (!equal(this->tuple, other->tuple)) return false;
		return true;
	}

	typedef boost::shared_ptr<OneTupleMappedType> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<OneTupleMappedType>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<OneTupleMappedType>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to OneTupleMappedType."); return r; }
protected:
	NodePtr tuple;
};

} // namespace ast