/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
#include "interfaces.hpp"
#include "types.hpp"

namespace ast {

class Encoder;
class Decoder;

class UnaryOpExpr : public Node
{
public:
	// constructor
	UnaryOpExpr();

	// auxiliary functions
	virtual bool isKindOf(Kind k);
	virtual bool implements(Interface i);
	virtual std::string getClassName() const { return "UnaryOpExpr"; }
	virtual NodePtr copy();
	virtual bool equalTo(const NodePtr& o);
	virtual std::string describe(int depth = -1);

	// accessor functions
	void setGraphPrev(const NodePtr& v);
	void setGraphPrev(const NodeId& v);
	const NodePtr& getGraphPrev(bool required = true);

	void setOperatorName(const std::string& v);
	const std::string& getOperatorName(bool required = true);

	void setPostfix(const bool& v);
	const bool& getPostfix(bool required = true);

	void setExpr(const NodePtr& v);
	const NodePtr& getExpr(bool required = true);

	void setCallName(const std::string& v);
	const std::string& getCallName(bool required = true);

	void setCallArgs(const NodeVector& v);
	const NodeVector& getCallArgs(bool required = true);

	void setCallCandidates(const NodeVector& v);
	const NodeVector& getCallCandidates(bool required = true);

	void setSelectedCallCandidate(const NodePtr& v);
	void setSelectedCallCandidate(const NodeId& v);
	const NodePtr& getSelectedCallCandidate(bool required = true);

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
	virtual CallInterface* asCall() { return &this->interfaceCall; }
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual TypeInterface* asType() { return &this->interfaceType; }

	// shared_ptr convenience
	typedef boost::shared_ptr<UnaryOpExpr> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<UnaryOpExpr>(n); }
	template<typename T> static Ptr needFrom(const T& n) {
		Ptr r = boost::dynamic_pointer_cast<UnaryOpExpr>(n);
		if (!r)
			throw std::runtime_error("Node " + n->getId().str() + " (a " + n->getClassName() + ") cannot be dynamically cast to UnaryOpExpr.");
		return r;
	}

protected:
	NodeRef graphPrev;
	std::string operatorName;
	bool postfix;
	NodePtr expr;
	std::string callName;
	NodeVector callArgs;
	NodeVector callCandidates;
	NodeRef selectedCallCandidate;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;

	// interfaces
	CallInterfaceImpl<UnaryOpExpr> interfaceCall;
	GraphInterfaceImpl<UnaryOpExpr> interfaceGraph;
	TypeInterfaceImpl<UnaryOpExpr> interfaceType;
};

} // namespace ast
