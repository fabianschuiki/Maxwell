#pragma once
#include <vector>
#include "lexer.h"


namespace Parser {
	typedef std::vector<Lexer::Node *> Nodes;
	
	void parse(Lexer::Group * root);
	bool parseFunction(const Nodes & nodes);
	
	Nodes scan(Lexer::Node * start);
}