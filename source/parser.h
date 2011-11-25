#pragma once
#include <vector>
#include "lexer.h"


namespace Parser {
	typedef std::vector<Lexer::Node *> Nodes;
	
	void parse(Lexer::Group * root);
	
	Nodes scan(Lexer::Node * start);
}