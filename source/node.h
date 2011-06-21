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
	
	
	
	class TextualExpression : public Expression {
	public:
		const std::string name;
		TextualExpression() {}
		TextualExpression(const std::string & name) : name(name) {}
		virtual std::string describe(int indent = 0) const;
	};
	
	class Identifier : public TextualExpression {
	public:
		Identifier(const std::string & name) : TextualExpression(name) {}
	};
	typedef std::vector<Identifier *> Identifiers;
	
	class Numeric : public TextualExpression {
	public:
		Numeric(const std::string & name) : TextualExpression(name) {}
	};
	
	class String : public TextualExpression {
	public:
		String(const std::string & name) : TextualExpression(name) {}
		virtual std::string describe(int indent = 0) const;
	};
	
	
	
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
	
	
	
	/*** Classes ***/
	
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
	
	
	
	/*** Functions ***/
	
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
		Expression * returnType;
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
	
	
	
	/*** Variables ***/
	
	class VariableDefinition : public Statement {
	public:
		Expression * type;
		Identifier * name;
		Expression * initial;
		
		VariableDefinition() {
			type = NULL;
			name = NULL;
			initial = NULL;
		}
		
		virtual std::string describe(int indent = 0) const;
	};
	
	
	
	/*** Expressions ***/
	
	class Tuple : public Expression {
	public:
		Expressions * expressions;
		
		Tuple() {
			expressions = NULL;
		}
		
		virtual std::string describe(int indent = 0) const;
	};
	
	class MemberAccess : public Expression {
	public:
		Expression * subject;
		Identifier * member;
		
		MemberAccess() {
			subject = NULL;
			member = NULL;
		}
		
		virtual std::string describe(int indent = 0) const;
	};
	
	class FunctionCallArgument;
	typedef std::vector<FunctionCallArgument *> FunctionCallArguments;
	
	class FunctionCall : public Expression {
	public:
		Expression * receiver;
		FunctionCallArguments * arguments;
		
		FunctionCall() {
			receiver = NULL;
			arguments = NULL;
		}
		
		virtual std::string describe(int indent = 0) const;
	};
	
	class FunctionCallArgument : public Expression {
	public:
		Identifier * name;
		Expression * argument;
		
		FunctionCallArgument() {
			name = NULL;
			argument = NULL;
		}
		
		virtual std::string describe(int indent = 0) const;
	};
}
