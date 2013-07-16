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

class QualifiedTypeMember : public Node
{
public:
	QualifiedTypeMember() : Node(),
		interfaceNamed(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kQualifiedTypeMember;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kNamedInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "QualifiedTypeMember"; }

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

	void setType(const NodePtr& v)
	{
		if (v && !v->isKindOf(kGenericType) && !v->isKindOf(kInvalidType) && !v->isKindOf(kDefinedType) && !v->isKindOf(kUnionType) && !v->isKindOf(kTupleType) && !v->isKindOf(kFuncType) && !v->isKindOf(kTypeSet) && !v->isKindOf(kQualifiedType)) {
			throw runtime_error("'type' needs to be of kind {GenericType, InvalidType, DefinedType, UnionType, TupleType, FuncType, TypeSet, QualifiedType} or implement interface {}, got " + v->getClassName() + " instead.");
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

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "QualifiedTypeMember{…}";
		stringstream str, b;
		str << "QualifiedTypeMember{";
		if (!this->name.empty()) b << endl << "  \033[1mname\033[0m = \033[33m\"" << this->name << "\"\033[0m";
		if (this->type) b << endl << "  \033[1mtype\033[0m = " << indent(this->type->describe(depth-1));
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->name);
		e.encode(this->type);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->name);
		d.decode(this->type);
	}

	virtual void updateHierarchyOfChildren()
	{
		if (this->type) this->type->updateHierarchy(id + "type", repository, this);
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// type.*
		if (size >= 4 && path[0] == 't' && path[1] == 'y' && path[2] == 'p' && path[3] == 'e') {
			// type
			if (size == 4) {
				return getType();
			} else if (path[4] == '.') {
				return getType()->resolvePath(path.substr(5));
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		if (const NodePtr& n = this->getType(false)) v.push_back(n);
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<QualifiedTypeMember>& other = boost::dynamic_pointer_cast<QualifiedTypeMember>(o);
		if (!other) return false;
		if (!equal(this->name, other->name)) return false;
		if (!equal(this->type, other->type)) return false;
		return true;
	}

	// Interfaces
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }

	typedef boost::shared_ptr<QualifiedTypeMember> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<QualifiedTypeMember>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<QualifiedTypeMember>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to QualifiedTypeMember."); return r; }
protected:
	string name;
	NodePtr type;

	// Interfaces
	NamedInterfaceImpl<QualifiedTypeMember> interfaceNamed;
};

} // namespace ast