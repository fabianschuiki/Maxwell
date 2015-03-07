/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "maxwell/ast/Node.hpp"
#include <boost/function.hpp>

namespace ast {

class CallInterface
{
public:
	virtual Node* getNode() = 0;

	virtual void setCallName(const std::string& v) = 0;
	virtual const std::string& getCallName(bool required = true) = 0;

	virtual void setCallArgs(const NodeVector& v) = 0;
	virtual const NodeVector& getCallArgs(bool required = true) = 0;

	virtual void setCallCandidates(const NodeVector& v) = 0;
	virtual const NodeVector& getCallCandidates(bool required = true) = 0;

	virtual void setSelectedCallCandidate(const NodePtr& v) = 0;
	virtual const NodePtr& getSelectedCallCandidate(bool required = true) = 0;
};
template <typename T> class CallInterfaceImpl : public CallInterface
{
public:
	Node* getNode() { return node; }
	CallInterfaceImpl(T* node) : node(node) {}

	const std::string& getCallName(bool required = true) { return node->getCallName(required); }
	void setCallName(const std::string& v) { node->setCallName(v); }
	const NodeVector& getCallArgs(bool required = true) { return node->getCallArgs(required); }
	void setCallArgs(const NodeVector& v) { node->setCallArgs(v); }
	const NodeVector& getCallCandidates(bool required = true) { return node->getCallCandidates(required); }
	void setCallCandidates(const NodeVector& v) { node->setCallCandidates(v); }
	const NodePtr& getSelectedCallCandidate(bool required = true) { return node->getSelectedCallCandidate(required); }
	void setSelectedCallCandidate(const NodePtr& v) { node->setSelectedCallCandidate(v); }

protected:
	T* const node;
};

class CallArgInterface
{
public:
	virtual Node* getNode() = 0;

	virtual void setName(const std::string& v) = 0;
	virtual const std::string& getName(bool required = true) = 0;

	virtual void setExpr(const NodePtr& v) = 0;
	virtual const NodePtr& getExpr(bool required = true) = 0;
};
template <typename T> class CallArgInterfaceImpl : public CallArgInterface
{
public:
	Node* getNode() { return node; }
	CallArgInterfaceImpl(T* node) : node(node) {}

	const std::string& getName(bool required = true) { return node->getName(required); }
	void setName(const std::string& v) { node->setName(v); }
	const NodePtr& getExpr(bool required = true) { return node->getExpr(required); }
	void setExpr(const NodePtr& v) { node->setExpr(v); }

protected:
	T* const node;
};

class CallableInterface
{
public:
	virtual Node* getNode() = 0;

	virtual void setName(const std::string& v) = 0;
	virtual const std::string& getName(bool required = true) = 0;

	virtual void setType(const NodePtr& v) = 0;
	virtual const NodePtr& getType(bool required = true) = 0;
};
template <typename T> class CallableInterfaceImpl : public CallableInterface
{
public:
	Node* getNode() { return node; }
	CallableInterfaceImpl(T* node) : node(node) {}

	const std::string& getName(bool required = true) { return node->getName(required); }
	void setName(const std::string& v) { node->setName(v); }
	const NodePtr& getType(bool required = true) { return node->getType(required); }
	void setType(const NodePtr& v) { node->setType(v); }

protected:
	T* const node;
};

class GraphInterface
{
public:
	virtual Node* getNode() = 0;

	virtual void setGraphPrev(const NodePtr& v) = 0;
	virtual const NodePtr& getGraphPrev(bool required = true) = 0;
};
template <typename T> class GraphInterfaceImpl : public GraphInterface
{
public:
	Node* getNode() { return node; }
	GraphInterfaceImpl(T* node) : node(node) {}

	const NodePtr& getGraphPrev(bool required = true) { return node->getGraphPrev(required); }
	void setGraphPrev(const NodePtr& v) { node->setGraphPrev(v); }

protected:
	T* const node;
};

class NamedInterface
{
public:
	virtual Node* getNode() = 0;

	virtual void setName(const std::string& v) = 0;
	virtual const std::string& getName(bool required = true) = 0;
};
template <typename T> class NamedInterfaceImpl : public NamedInterface
{
public:
	Node* getNode() { return node; }
	NamedInterfaceImpl(T* node) : node(node) {}

	const std::string& getName(bool required = true) { return node->getName(required); }
	void setName(const std::string& v) { node->setName(v); }

protected:
	T* const node;
};

class NativeInterface
{
public:
	virtual Node* getNode() = 0;

	virtual void setLanguage(const std::string& v) = 0;
	virtual const std::string& getLanguage(bool required = true) = 0;

	virtual void setDependencies(const std::vector<std::string>& v) = 0;
	virtual const std::vector<std::string>& getDependencies(bool required = true) = 0;
};
template <typename T> class NativeInterfaceImpl : public NativeInterface
{
public:
	Node* getNode() { return node; }
	NativeInterfaceImpl(T* node) : node(node) {}

	const std::string& getLanguage(bool required = true) { return node->getLanguage(required); }
	void setLanguage(const std::string& v) { node->setLanguage(v); }
	const std::vector<std::string>& getDependencies(bool required = true) { return node->getDependencies(required); }
	void setDependencies(const std::vector<std::string>& v) { node->setDependencies(v); }

protected:
	T* const node;
};

class TypeInterface
{
public:
	virtual Node* getNode() = 0;

	virtual void setPossibleType(const NodePtr& v) = 0;
	virtual const NodePtr& getPossibleType(bool required = true) = 0;

	virtual void setRequiredType(const NodePtr& v) = 0;
	virtual const NodePtr& getRequiredType(bool required = true) = 0;

	virtual void setActualType(const NodePtr& v) = 0;
	virtual const NodePtr& getActualType(bool required = true) = 0;
};
template <typename T> class TypeInterfaceImpl : public TypeInterface
{
public:
	Node* getNode() { return node; }
	TypeInterfaceImpl(T* node) : node(node) {}

	const NodePtr& getPossibleType(bool required = true) { return node->getPossibleType(required); }
	void setPossibleType(const NodePtr& v) { node->setPossibleType(v); }
	const NodePtr& getRequiredType(bool required = true) { return node->getRequiredType(required); }
	void setRequiredType(const NodePtr& v) { node->setRequiredType(v); }
	const NodePtr& getActualType(bool required = true) { return node->getActualType(required); }
	void setActualType(const NodePtr& v) { node->setActualType(v); }

protected:
	T* const node;
};

class TypeExprInterface
{
public:
	virtual Node* getNode() = 0;

	virtual void setEvaluatedType(const NodePtr& v) = 0;
	virtual const NodePtr& getEvaluatedType(bool required = true) = 0;
};
template <typename T> class TypeExprInterfaceImpl : public TypeExprInterface
{
public:
	Node* getNode() { return node; }
	TypeExprInterfaceImpl(T* node) : node(node) {}

	const NodePtr& getEvaluatedType(bool required = true) { return node->getEvaluatedType(required); }
	void setEvaluatedType(const NodePtr& v) { node->setEvaluatedType(v); }

protected:
	T* const node;
};

class VariableInterface
{
public:
	virtual Node* getNode() = 0;

	virtual void setPossibleType(const NodePtr& v) = 0;
	virtual const NodePtr& getPossibleType(bool required = true) = 0;

	virtual void setRequiredType(const NodePtr& v) = 0;
	virtual const NodePtr& getRequiredType(bool required = true) = 0;

	virtual void setActualType(const NodePtr& v) = 0;
	virtual const NodePtr& getActualType(bool required = true) = 0;

	virtual void setName(const std::string& v) = 0;
	virtual const std::string& getName(bool required = true) = 0;

	virtual void setTypeExpr(const NodePtr& v) = 0;
	virtual const NodePtr& getTypeExpr(bool required = true) = 0;
};
template <typename T> class VariableInterfaceImpl : public VariableInterface
{
public:
	Node* getNode() { return node; }
	VariableInterfaceImpl(T* node) : node(node) {}

	const NodePtr& getPossibleType(bool required = true) { return node->getPossibleType(required); }
	void setPossibleType(const NodePtr& v) { node->setPossibleType(v); }
	const NodePtr& getRequiredType(bool required = true) { return node->getRequiredType(required); }
	void setRequiredType(const NodePtr& v) { node->setRequiredType(v); }
	const NodePtr& getActualType(bool required = true) { return node->getActualType(required); }
	void setActualType(const NodePtr& v) { node->setActualType(v); }
	const std::string& getName(bool required = true) { return node->getName(required); }
	void setName(const std::string& v) { node->setName(v); }
	const NodePtr& getTypeExpr(bool required = true) { return node->getTypeExpr(required); }
	void setTypeExpr(const NodePtr& v) { node->setTypeExpr(v); }

protected:
	T* const node;
};

} // namespace ast
