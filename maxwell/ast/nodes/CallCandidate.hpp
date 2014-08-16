/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "maxwell/ast/Node.hpp"
#include "maxwell/ast/nodes/interfaces.hpp"
#include "maxwell/ast/nodes/types.hpp"

namespace ast {

class Encoder;
class Decoder;

class CallCandidate : public Node
{
public:
	// constructor
	CallCandidate();

	// auxiliary functions
	virtual bool isKindOf(Kind k);
	virtual bool implements(Interface i);
	virtual std::string getClassName() const { return "CallCandidate"; }
	virtual NodePtr copy();
	virtual bool equalTo(const NodePtr& o);
	virtual std::string describe(int depth = -1);

	// accessor functions
	void setFunc(const NodePtr& v);
	void setFunc(const NodeId& v);
	const NodePtr& getFunc(bool required = true);

	void setArgs(const NodeVector& v);
	const NodeVector& getArgs(bool required = true);

	void setFeasible(const bool& v);
	const bool& getFeasible(bool required = true);

	void setCost(const int& v);
	const int& getCost(bool required = true);

	void setPossibleType(const NodePtr& v);
	const NodePtr& getPossibleType(bool required = true);

	void setRequiredType(const NodePtr& v);
	const NodePtr& getRequiredType(bool required = true);

	void setActualType(const NodePtr& v);
	const NodePtr& getActualType(bool required = true);

	void setGraphPrev(const NodePtr& v);
	void setGraphPrev(const NodeId& v);
	const NodePtr& getGraphPrev(bool required = true);

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
	typedef boost::shared_ptr<CallCandidate> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<CallCandidate>(n); }
	template<typename T> static Ptr needFrom(const T& n) {
		Ptr r = boost::dynamic_pointer_cast<CallCandidate>(n);
		if (!r)
			throw std::runtime_error("Node " + n->getId().str() + " (a " + n->getClassName() + ") cannot be dynamically cast to CallCandidate.");
		return r;
	}

protected:
	NodeRef func;
	NodeVector args;
	bool feasible;
	int cost;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;
	NodeRef graphPrev;

	// interfaces
	GraphInterfaceImpl<CallCandidate> interfaceGraph;
	TypeInterfaceImpl<CallCandidate> interfaceType;
};

} // namespace ast