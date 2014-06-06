/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
#include "interfaces.hpp"
#include "types.hpp"

namespace ast {

class Encoder;
class Decoder;

class NilTypeExpr : public Node
{
public:
	// constructor
	NilTypeExpr();

	// auxiliary functions
	virtual bool isKindOf(Kind k);
	virtual bool implements(Interface i);
	virtual std::string getClassName() const { return "NilTypeExpr"; }
	virtual NodePtr copy();
	virtual bool equalTo(const NodePtr& o);
	virtual std::string describe(int depth = -1);

	// accessor functions
	void setEvaluatedType(const NodePtr& v);
	const NodePtr& getEvaluatedType(bool required = true);

	// encoding and decoding
	virtual void encode(Encoder& e);
	virtual void decode(Decoder& d);

	// hierarchy functions
	virtual void updateHierarchyOfChildren();
	virtual const NodePtr& resolvePath(const std::string& path);
	virtual NodeVector getChildren();

	// interfaces
	virtual TypeExprInterface* asTypeExpr() { return &this->interfaceTypeExpr; }

	// shared_ptr convenience
	typedef boost::shared_ptr<NilTypeExpr> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<NilTypeExpr>(n); }
	template<typename T> static Ptr needFrom(const T& n) {
		Ptr r = boost::dynamic_pointer_cast<NilTypeExpr>(n);
		if (!r)
			throw std::runtime_error("Node " + n->getId().str() + " (a " + n->getClassName() + ") cannot be dynamically cast to NilTypeExpr.");
		return r;
	}

protected:
	NodePtr evaluatedType;

	// interfaces
	TypeExprInterfaceImpl<NilTypeExpr> interfaceTypeExpr;
};

} // namespace ast
