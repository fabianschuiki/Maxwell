/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "BuiltinNode.hpp"
#include "../nodes/interfaces.hpp"
#include <string>

namespace ast {

class BuiltinRepository;

namespace builtin {

using std::string;

class FuncArg : public BuiltinNode
{
public:
	FuncArg() :
		interfaceNamed(this),
		interfaceCallableArg(this),
		interfaceType(this),
		BuiltinNode() {}

	const string& getName(bool required = true) const { return name; }
	const NodePtr& getPossibleType(bool required = true) const { return type; }
	const NodePtr& getRequiredType(bool required = true) const { return type; }
	const NodePtr& getActualType(bool required = true) const { return type; }

	void setName(const string& s) { throw std::runtime_error("Cannot set name of builtin function " + name + "."); }
	void setPossibleType(const NodePtr& v) { throw std::runtime_error("Cannot set type of builtin function " + name + "."); }
	void setRequiredType(const NodePtr& v) { throw std::runtime_error("Cannot set type of builtin function " + name + "."); }
	void setActualType(const NodePtr& v) { throw std::runtime_error("Cannot set type of builtin function " + name + "."); }

	virtual bool equalTo(const NodePtr& other)
	{
		FuncArg* nt = dynamic_cast<FuncArg*>(other.get());
		if (!nt) return false;
		return (name == nt->name);
	}
	virtual bool implements(Interface i)
	{
		if (BuiltinNode::implements(i)) return true;
		if (i == kCallableArgInterface) return true;
		if (i == kNamedInterface) return true;
		if (i == kTypeInterface) return true;
		return false;
	}

	// Interfaces
	virtual CallableArgInterface* asCallableArg() { return &this->interfaceCallableArg; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }
	virtual TypeInterface* asType() { return &this->interfaceType; }

	typedef boost::shared_ptr<FuncArg> Ptr;

protected:
	friend class BuiltinRepository;
	string name;
	NodePtr type;

	// Interfaces
	NamedInterfaceImpl<FuncArg> interfaceNamed;
	CallableArgInterfaceImpl<FuncArg> interfaceCallableArg;
	TypeInterfaceImpl<FuncArg> interfaceType;
};

} // namespace builtin
} // namespace ast