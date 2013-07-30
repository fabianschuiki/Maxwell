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

class SpecializedType : public Node
{
public:
	SpecializedType() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kSpecializedType;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		return false;
	}

	virtual string getClassName() const { return "SpecializedType"; }

	void setType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType) && !v->isKindOf(kSpecializedType) && !v->isKindOf(kUnionMappedType)) {
			throw runtime_error("'type' of " + id.str() + " needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType, SpecializedType, UnionMappedType} or implement interface {}, got " + v->getClassName() + " (" + v->getId().str() + ") instead.");
		}
		if (!equal(v, type)) {
			modify("type");
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

	void setSpecs(const NodeVector& v)
	{
		if (!equal(v, specs)) {
			modify("specs");
			specs = v;
		}
	}
	const NodeVector& getSpecs(bool required = true)
	{
		const NodeVector& v = specs;
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "SpecializedType{…}";
		stringstream str, b;
					str << type->describe(depth-1) << "[";			bool first = true;			for (NodeVector::iterator it = specs.begin(); it != specs.end(); it++) {				if (!first) str << ",";				first = false;				str << (*it)->describe(depth-1);			}			str << "]";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->type);
		e.encode(this->specs);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->type);
		d.decode(this->specs);
	}

	virtual void updateHierarchyOfChildren()
	{
		if (this->type) this->type->updateHierarchy(id + "type", repository, this);
		for (int i = 0; i < this->specs.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->specs[i]->updateHierarchy((id + "specs") + buf, repository, this);
		}
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// .*
		if (true) {
			// specs.*
			if (size >= 5 && path[0] == 's' && path[1] == 'p' && path[2] == 'e' && path[3] == 'c' && path[4] == 's') {
				// specs
				if (size == 5) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[5] == '.') {
					size_t dot = path.find(".", 6);
					string idx_str = path.substr(6, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getSpecs();
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
		v.insert(v.end(), this->specs.begin(), this->specs.end());
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<SpecializedType>& other = boost::dynamic_pointer_cast<SpecializedType>(o);
		if (!other) return false;
		if (!equal(this->type, other->type)) return false;
		if (!equal(this->specs, other->specs)) return false;
		return true;
	}

	typedef boost::shared_ptr<SpecializedType> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<SpecializedType>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<SpecializedType>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to SpecializedType."); return r; }
protected:
	NodePtr type;
	NodeVector specs;
};

} // namespace ast