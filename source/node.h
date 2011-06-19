#pragma once
#include <vector>


namespace Maxwell {
	
	class Node {
	public:
		virtual ~Node() {}
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
	};
	
	
	
	/* A block groups a bunch of statements together in curly braces. */
	class Block : public Expression {
	public:
		Statements statements;
	};
	
	class ClassDeclaration : public Statement {
	public:
		const Identifier name;
		const Identifier super;
		
		ClassDeclaration(const Identifier & name) : name(name) {}
		ClassDeclaration(const Identifier & name, const Identifier & super)
		: name(name), super(super) {}
	};
}
