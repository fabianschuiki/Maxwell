/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include <stdexcept>
#include "../NodeId.hpp"

namespace ast {

class CallInterface;
class CallArgInterface;
class CallableInterface;
class GraphInterface;
class NamedInterface;
class TypeInterface;
class TypeExprInterface;
class VariableInterface;

class BaseNode
{
public:
	virtual string getClassName() const = 0;
	virtual const NodeId& getId() const = 0;
	virtual CallInterface* asCall() { return NULL; }
	CallInterface* needCall() { CallInterface* i = asCall(); if (i) return i; throw std::runtime_error("Node " + getId().str() + " (a " + getClassName() + ") does not implement Call interface."); }
	virtual CallArgInterface* asCallArg() { return NULL; }
	CallArgInterface* needCallArg() { CallArgInterface* i = asCallArg(); if (i) return i; throw std::runtime_error("Node " + getId().str() + " (a " + getClassName() + ") does not implement CallArg interface."); }
	virtual CallableInterface* asCallable() { return NULL; }
	CallableInterface* needCallable() { CallableInterface* i = asCallable(); if (i) return i; throw std::runtime_error("Node " + getId().str() + " (a " + getClassName() + ") does not implement Callable interface."); }
	virtual GraphInterface* asGraph() { return NULL; }
	GraphInterface* needGraph() { GraphInterface* i = asGraph(); if (i) return i; throw std::runtime_error("Node " + getId().str() + " (a " + getClassName() + ") does not implement Graph interface."); }
	virtual NamedInterface* asNamed() { return NULL; }
	NamedInterface* needNamed() { NamedInterface* i = asNamed(); if (i) return i; throw std::runtime_error("Node " + getId().str() + " (a " + getClassName() + ") does not implement Named interface."); }
	virtual TypeInterface* asType() { return NULL; }
	TypeInterface* needType() { TypeInterface* i = asType(); if (i) return i; throw std::runtime_error("Node " + getId().str() + " (a " + getClassName() + ") does not implement Type interface."); }
	virtual TypeExprInterface* asTypeExpr() { return NULL; }
	TypeExprInterface* needTypeExpr() { TypeExprInterface* i = asTypeExpr(); if (i) return i; throw std::runtime_error("Node " + getId().str() + " (a " + getClassName() + ") does not implement TypeExpr interface."); }
	virtual VariableInterface* asVariable() { return NULL; }
	VariableInterface* needVariable() { VariableInterface* i = asVariable(); if (i) return i; throw std::runtime_error("Node " + getId().str() + " (a " + getClassName() + ") does not implement Variable interface."); }
};

} // namespace ast
