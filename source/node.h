#pragma once
#include <vector>
#include <string>
#include <sstream>


namespace Maxwell {
	
	class Node {
	public:
		virtual ~Node() {}
		virtual std::string describe(int indent = 0) const = 0;
		std::string pad(int indent) const { return std::string(indent * 4, ' '); }
	};
	
	class Statement : public Node {
	};
	
	class Expression : public Node {
	};
	
	typedef std::vector<Statement *> Statements;
	typedef std::vector<Expression *> Expressions;
	
	
	
	class Identifier : public Expression {
	public:
		std::string name;
		Identifier() {}
		Identifier(const std::string & name) : name(name) {}
		virtual std::string describe(int indent = 0) const { return pad(indent) + name; }
	};
	
	typedef std::vector<Identifier *> Identifiers;
	
	
	
	//Forward declarations.
	class ClassDefinition;
	class FunctionDefinition;
	class VariableDefinition;
	
	
	
	/* A block groups a bunch of statements together in curly braces. */
	class Block : public Expression {
	public:
		Statements statements;
		virtual std::string describe(int indent = 0) const;
	};
	
	class ClassDefinition : public Statement {
	public:
		Identifier * name;
		Identifier * super;
		Identifiers * interfaces;
		Block * statements;
		
		ClassDefinition() {
			name = NULL;
			super = NULL;
			interfaces = NULL;
			statements = NULL;
		}
		
		virtual std::string describe(int indent = 0) const;
	};
	
	class Type : public Expression {
	public:
	};
	
	typedef std::vector<Type *> Types;
	
	
	
	class FunctionArgument : public Expression {
	public:
		Identifier * name;
		VariableDefinition * argument;
		
		FunctionArgument() {
			name = NULL;
			argument = NULL;
		}
		
		virtual std::string describe(int indent = 0) const;
	};
	
	typedef std::vector<FunctionArgument *> FunctionArguments;
	
	class FunctionDefinition : public Statement {
	public:
		bool shared;
		Type * returnType;
		FunctionArguments * arguments;
		Block * statements;
		
		FunctionDefinition() {
			shared = false;
			returnType = NULL;
			arguments = NULL;
			statements = NULL;
		}
		
		virtual std::string describe(int indent = 0) const;
	};
	
	
	
	class VariableDefinition : public Statement {
	public:
		Type * type;
		Identifier * name;
		
		VariableDefinition() {
			type = NULL;
			name = NULL;
		}
		
		virtual std::string describe(int indent = 0) const;
	};
	
	
	
	class ConcreteType : public Type {
	public:
		Identifier * name;
		ConcreteType() {
			name = NULL;
		}
		virtual std::string describe(int indent = 0) const;
	};
	
	class TupleType : public Type {
	public:
		Types * types;
		TupleType() {
			types = NULL;
		}
		virtual std::string describe(int indent = 0) const;
	};
}
