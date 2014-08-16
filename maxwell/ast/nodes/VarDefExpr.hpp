/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "maxwell/ast/Node.hpp"
#include "maxwell/ast/nodes/interfaces.hpp"
#include "maxwell/ast/nodes/types.hpp"

namespace ast {

class Encoder;
class Decoder;

class VarDefExpr : public Node
{
public:
	// constructor
	VarDefExpr();

	// auxiliary functions
	virtual bool isKindOf(Kind k);
	virtual bool implements(Interface i);
	virtual std::string getClassName() const { return "VarDefExpr"; }
	virtual NodePtr copy();
	virtual bool equalTo(const NodePtr& o);
	virtual std::string describe(int depth = -1);

	// accessor functions
	void setGraphPrev(const NodePtr& v);
	void setGraphPrev(const NodeId& v);
	const NodePtr& getGraphPrev(bool required = true);

	void setPossibleType(const NodePtr& v);
	const NodePtr& getPossibleType(bool required = true);

	void setRequiredType(const NodePtr& v);
	const NodePtr& getRequiredType(bool required = true);

	void setActualType(const NodePtr& v);
	const NodePtr& getActualType(bool required = true);

	void setName(const std::string& v);
	const std::string& getName(bool required = true);

	void setTypeExpr(const NodePtr& v);
	const NodePtr& getTypeExpr(bool required = true);

	void setInitialExpr(const NodePtr& v);
	const NodePtr& getInitialExpr(bool required = true);

	// encoding and decoding
	virtual void encode(Encoder& e);
	virtual void decode(Decoder& d);

	// hierarchy functions
	virtual void updateHierarchyOfChildren();
	virtual const NodePtr& resolvePath(const std::string& path);
	virtual NodeVector getChildren();

	// interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }
	virtual TypeInterface* asType() { return &this->interfaceType; }
	virtual VariableInterface* asVariable() { return &this->interfaceVariable; }

	// shared_ptr convenience
	typedef boost::shared_ptr<VarDefExpr> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<VarDefExpr>(n); }
	template<typename T> static Ptr needFrom(const T& n) {
		Ptr r = boost::dynamic_pointer_cast<VarDefExpr>(n);
		if (!r)
			throw std::runtime_error("Node " + n->getId().str() + " (a " + n->getClassName() + ") cannot be dynamically cast to VarDefExpr.");
		return r;
	}

protected:
	NodeRef graphPrev;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;
	std::string name;
	NodePtr typeExpr;
	NodePtr initialExpr;

	// interfaces
	GraphInterfaceImpl<VarDefExpr> interfaceGraph;
	NamedInterfaceImpl<VarDefExpr> interfaceNamed;
	TypeInterfaceImpl<VarDefExpr> interfaceType;
	VariableInterfaceImpl<VarDefExpr> interfaceVariable;
};

} // namespace ast