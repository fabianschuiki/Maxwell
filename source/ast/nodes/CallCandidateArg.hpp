/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
#include "interfaces.hpp"
#include "types.hpp"

namespace ast {

class Encoder;
class Decoder;

class CallCandidateArg : public Node
{
public:
	// constructor
	CallCandidateArg();

	// auxiliary functions
	virtual bool isKindOf(Kind k);
	virtual bool implements(Interface i);
	virtual std::string getClassName() const { return "CallCandidateArg"; }
	virtual NodePtr copy();
	virtual bool equalTo(const NodePtr& o);
	virtual std::string describe(int depth = -1);

	// accessor functions
	void setArg(const NodePtr& v);
	void setArg(const NodeId& v);
	const NodePtr& getArg(bool required = true);

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

	// interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual TypeInterface* asType() { return &this->interfaceType; }

	// shared_ptr convenience
	typedef boost::shared_ptr<CallCandidateArg> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<CallCandidateArg>(n); }
	template<typename T> static Ptr needFrom(const T& n) {
		Ptr r = boost::dynamic_pointer_cast<CallCandidateArg>(n);
		if (!r)
			throw std::runtime_error("Node " + n->getId().str() + " (a " + n->getClassName() + ") cannot be dynamically cast to CallCandidateArg.");
		return r;
	}

protected:
	NodeRef arg;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;
	NodeRef graphPrev;

	// interfaces
	GraphInterfaceImpl<CallCandidateArg> interfaceGraph;
	TypeInterfaceImpl<CallCandidateArg> interfaceType;
};

} // namespace ast
