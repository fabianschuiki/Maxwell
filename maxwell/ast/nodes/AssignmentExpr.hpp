/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "maxwell/ast/Node.hpp"
#include "maxwell/ast/nodes/interfaces.hpp"
#include "maxwell/ast/nodes/types.hpp"

namespace ast {

class Encoder;
class Decoder;

class AssignmentExpr : public Node
{
public:
	// constructor
	AssignmentExpr();

	// auxiliary functions
	virtual bool isKindOf(Kind k);
	virtual bool implements(Interface i);
	virtual std::string getClassName() const { return "AssignmentExpr"; }
	virtual NodePtr copy();
	virtual bool equalTo(const NodePtr& o);
	virtual std::string describe(int depth = -1);

	// accessor functions
	void setRhs(const NodePtr& v);
	const NodePtr& getRhs(bool required = true);

	void setLhs(const NodePtr& v);
	const NodePtr& getLhs(bool required = true);

	void setGraphPrev(const NodePtr& v);
	void setGraphPrev(const NodeId& v);
	const NodePtr& getGraphPrev(bool required = true);

	void setPossibleType(const NodePtr& v);
	const NodePtr& getPossibleType(bool required = true);

	void setRequiredType(const NodePtr& v);
	const NodePtr& getRequiredType(bool required = true);

	void setActualType(const NodePtr& v);
	const NodePtr& getActualType(bool required = true);

	// encoding and decoding
	virtual void encode(Encoder& e);
	virtual void decode(Decoder& d);

	// hierarchy functions
	virtual void updateHierarchyOfChildren();
	virtual const NodePtr& resolvePath(const std::string& path);
	virtual NodeVector getChildren();

	// interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual TypeInterface* asType() { return &this->interfaceType; }

	// shared_ptr convenience
	typedef boost::shared_ptr<AssignmentExpr> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<AssignmentExpr>(n); }
	template<typename T> static Ptr needFrom(const T& n) {
		Ptr r = boost::dynamic_pointer_cast<AssignmentExpr>(n);
		if (!r)
			throw std::runtime_error("Node " + n->getId().str() + " (a " + n->getClassName() + ") cannot be dynamically cast to AssignmentExpr.");
		return r;
	}

protected:
	NodePtr rhs;
	NodePtr lhs;
	NodeRef graphPrev;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;

	// interfaces
	GraphInterfaceImpl<AssignmentExpr> interfaceGraph;
	TypeInterfaceImpl<AssignmentExpr> interfaceType;
};

} // namespace ast