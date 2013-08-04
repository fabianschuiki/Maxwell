/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "BuiltinNode.hpp"
#include "../nodes/interfaces.hpp"
#include <string>

namespace ast {

class BuiltinRepository;

namespace builtin {

using std::string;

class FuncDef : public BuiltinNode
{
public:
	FuncDef() :
		interfaceNamed(this),
		interfaceCallable(this),
		BuiltinNode() {}

	const string& getName(bool required = true) const { return name; }
	const NodeVector& getIn(bool required = true) { return in; }
	const NodeVector& getOut(bool required = true) { return out; }
	const NodePtr& getType(bool required = true) { return type; }

	void setName(const string& s) { throw std::runtime_error("Cannot set name of builtin function " + name + "."); }	
	void setIn(const NodeVector& v) { throw std::runtime_error("Cannot set input of builtin function " + name + "."); }
	void setOut(const NodeVector& v) { throw std::runtime_error("Cannot set output of builtin function " + name + "."); }
	void setType(const NodePtr& v) { throw std::runtime_error("Cannot set type of builtin function " + name + "."); }

	virtual bool equalTo(const NodePtr& other)
	{
		FuncDef* nt = dynamic_cast<FuncDef*>(other.get());
		if (!nt) return false;
		return (name == nt->name);
	}
	virtual bool implements(Interface i)
	{
		if (BuiltinNode::implements(i)) return true;
		if (i == kCallableInterface) return true;
		if (i == kNamedInterface) return true;
		return false;
	}

	// Interfaces
	virtual CallableInterface* asCallable() { return &this->interfaceCallable; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }
	
	typedef boost::shared_ptr<FuncDef> Ptr;

protected:
	friend class BuiltinRepository;
	string name;
	NodeVector in;
	NodeVector out;
	NodePtr type;

	// Interfaces
	NamedInterfaceImpl<FuncDef> interfaceNamed;
	CallableInterfaceImpl<FuncDef> interfaceCallable;
};

} // namespace builtin
} // namespace ast