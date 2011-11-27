#pragma once
#include <vector>
#include "lexer.h"


namespace Parser {
	typedef std::vector<Lexer::Node *> Nodes;
	
	struct Expr {
		virtual ~Expr() {}
	};
	
	struct FunctionArg : public Expr {
		std::string name;
		std::string type;
	};
	
	struct FunctionArgs : public Expr {
		std::vector<FunctionArg *> args;
	};
	
	struct Function : public Expr {
		std::string name;
		FunctionArgs * inputs;
		FunctionArgs * outputs;
	};
	
	void parse(Lexer::Group * root);
	Function * parseFunction(const Nodes & nodes);
	FunctionArgs * parseFunctionArgs(const Nodes & nodes);
	FunctionArg * parseFunctionArg(const Nodes & nodes);
	
	Nodes scan(Lexer::Node * start);
}