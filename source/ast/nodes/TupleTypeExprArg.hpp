/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
#include "interfaces.hpp"
#include "types.hpp"

namespace ast {

class Encoder;
class Decoder;

class TupleTypeExprArg : public Node
{
public:
	// constructor
	TupleTypeExprArg();

	// auxiliary functions
	virtual bool isKindOf(Kind k);
	virtual bool implements(Interface i);
	virtual std::string getClassName() const { return "TupleTypeExprArg"; }
	virtual NodePtr copy();
	virtual bool equalTo(const NodePtr& o);
	virtual std::string describe(int depth = -1);

	// accessor functions
	void setGraphPrev(const NodePtr& v);
	void setGraphPrev(const NodeId& v);
	const NodePtr& getGraphPrev(bool required = true);

	void setName(const std::string& v);
	const std::string& getName(bool required = true);

	void setExpr(const NodePtr& v);
	const NodePtr& getExpr(bool required = true);

	// encoding and decoding
	virtual void encode(Encoder& e);
	virtual void decode(Decoder& d);

	// hierarchy functions
	virtual void updateHierarchyOfChildren();
	virtual const NodePtr& resolvePath(const std::string& path);
	virtual NodeVector getChildren();

	// interfaces
	virtual CallArgInterface* asCallArg() { return &this->interfaceCallArg; }
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }

	// shared_ptr convenience
	typedef boost::shared_ptr<TupleTypeExprArg> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<TupleTypeExprArg>(n); }
	template<typename T> static Ptr needFrom(const T& n) {
		Ptr r = boost::dynamic_pointer_cast<TupleTypeExprArg>(n);
		if (!r)
			throw std::runtime_error("Node " + n->getId().str() + " (a " + n->getClassName() + ") cannot be dynamically cast to TupleTypeExprArg.");
		return r;
	}

protected:
	NodeRef graphPrev;
	std::string name;
	NodePtr expr;

	// interfaces
	CallArgInterfaceImpl<TupleTypeExprArg> interfaceCallArg;
	GraphInterfaceImpl<TupleTypeExprArg> interfaceGraph;
	NamedInterfaceImpl<TupleTypeExprArg> interfaceNamed;
};

} // namespace ast
