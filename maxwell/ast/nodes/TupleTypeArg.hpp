/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "maxwell/ast/Node.hpp"
#include "maxwell/ast/nodes/interfaces.hpp"
#include "maxwell/ast/nodes/types.hpp"

namespace ast {

class Encoder;
class Decoder;

class TupleTypeArg : public Node
{
public:
	// constructor
	TupleTypeArg();

	// auxiliary functions
	virtual bool isKindOf(Kind k);
	virtual bool implements(Interface i);
	virtual std::string getClassName() const { return "TupleTypeArg"; }
	virtual NodePtr copy();
	virtual bool equalTo(const NodePtr& o);
	virtual std::string describe(int depth = -1);

	// accessor functions
	void setName(const std::string& v);
	const std::string& getName(bool required = true);

	void setType(const NodePtr& v);
	const NodePtr& getType(bool required = true);

	// encoding and decoding
	virtual void encode(Encoder& e);
	virtual void decode(Decoder& d);

	// hierarchy functions
	virtual void updateHierarchyOfChildren();
	virtual const NodePtr& resolvePath(const std::string& path);
	virtual NodeVector getChildren();

	// interfaces
	virtual CallableInterface* asCallable() { return &this->interfaceCallable; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }

	// shared_ptr convenience
	typedef boost::shared_ptr<TupleTypeArg> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<TupleTypeArg>(n); }
	template<typename T> static Ptr needFrom(const T& n) {
		Ptr r = boost::dynamic_pointer_cast<TupleTypeArg>(n);
		if (!r)
			throw std::runtime_error("Node " + n->getId().str() + " (a " + n->getClassName() + ") cannot be dynamically cast to TupleTypeArg.");
		return r;
	}

protected:
	std::string name;
	NodePtr type;

	// interfaces
	CallableInterfaceImpl<TupleTypeArg> interfaceCallable;
	NamedInterfaceImpl<TupleTypeArg> interfaceNamed;
};

} // namespace ast