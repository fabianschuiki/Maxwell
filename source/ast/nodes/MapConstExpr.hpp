/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
#include "interfaces.hpp"
#include "types.hpp"

namespace ast {

class Encoder;
class Decoder;

class MapConstExpr : public Node
{
public:
	// constructor
	MapConstExpr();

	// auxiliary functions
	virtual bool isKindOf(Kind k);
	virtual bool implements(Interface i);
	virtual std::string getClassName() const { return "MapConstExpr"; }
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

	void setPairs(const NodeVector& v);
	const NodeVector& getPairs(bool required = true);

	void setKeysType(const NodePtr& v);
	const NodePtr& getKeysType(bool required = true);

	void setValuesType(const NodePtr& v);
	const NodePtr& getValuesType(bool required = true);

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
	typedef boost::shared_ptr<MapConstExpr> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<MapConstExpr>(n); }
	template<typename T> static Ptr needFrom(const T& n) {
		Ptr r = boost::dynamic_pointer_cast<MapConstExpr>(n);
		if (!r)
			throw std::runtime_error("Node " + n->getId().str() + " (a " + n->getClassName() + ") cannot be dynamically cast to MapConstExpr.");
		return r;
	}

protected:
	NodeRef graphPrev;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;
	NodeVector pairs;
	NodePtr keysType;
	NodePtr valuesType;

	// interfaces
	GraphInterfaceImpl<MapConstExpr> interfaceGraph;
	TypeInterfaceImpl<MapConstExpr> interfaceType;
};

} // namespace ast
