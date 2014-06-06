/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
#include "interfaces.hpp"
#include "types.hpp"

namespace ast {

class Encoder;
class Decoder;

class NamedTypeExpr : public Node
{
public:
	// constructor
	NamedTypeExpr();

	// auxiliary functions
	virtual bool isKindOf(Kind k);
	virtual bool implements(Interface i);
	virtual std::string getClassName() const { return "NamedTypeExpr"; }
	virtual NodePtr copy();
	virtual bool equalTo(const NodePtr& o);
	virtual std::string describe(int depth = -1);

	// accessor functions
	void setGraphPrev(const NodePtr& v);
	void setGraphPrev(const NodeId& v);
	const NodePtr& getGraphPrev(bool required = true);

	void setEvaluatedType(const NodePtr& v);
	const NodePtr& getEvaluatedType(bool required = true);

	void setName(const std::string& v);
	const std::string& getName(bool required = true);

	void setDefinition(const NodePtr& v);
	void setDefinition(const NodeId& v);
	const NodePtr& getDefinition(bool required = true);

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
	virtual TypeExprInterface* asTypeExpr() { return &this->interfaceTypeExpr; }

	// shared_ptr convenience
	typedef boost::shared_ptr<NamedTypeExpr> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<NamedTypeExpr>(n); }
	template<typename T> static Ptr needFrom(const T& n) {
		Ptr r = boost::dynamic_pointer_cast<NamedTypeExpr>(n);
		if (!r)
			throw std::runtime_error("Node " + n->getId().str() + " (a " + n->getClassName() + ") cannot be dynamically cast to NamedTypeExpr.");
		return r;
	}

protected:
	NodeRef graphPrev;
	NodePtr evaluatedType;
	std::string name;
	NodeRef definition;

	// interfaces
	GraphInterfaceImpl<NamedTypeExpr> interfaceGraph;
	NamedInterfaceImpl<NamedTypeExpr> interfaceNamed;
	TypeExprInterfaceImpl<NamedTypeExpr> interfaceTypeExpr;
};

} // namespace ast
