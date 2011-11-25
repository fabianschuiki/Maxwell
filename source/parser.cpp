#include "parser.h"
#include <iostream>
using namespace Parser;


std::string describeNodes(const Parser::Nodes & n)
{
	std::stringstream s;
	bool first = true;
	for (Parser::Nodes::const_iterator i = n.begin(); i != n.end(); i++) {
		if (!first)
			s << " ";
		first = false;
		s << (*i)->describe(0);
	}
	return s.str();
}


void Parser::parse(Lexer::Group * root)
{
	Lexer::Node * current = root->firstChild;
	std::cout << describeNodes(scan(current)) << std::endl;
}

/** Scans through the nodes up to the next group or ';' and accumulates the
 * scanned tokens in a vector, which is returned at the end. */
Parser::Nodes Parser::scan(Lexer::Node * start)
{
	//Start at the given node and scan forward, accumulating the consumed nodes
	//in the vector. Once we encounter a delimiter, stop scanning and return
	//whatever we've consumed.
	Nodes nodes;
	Lexer::Node * node = start;
	while (node) {
		nodes.push_back(node);
		if (node->type == Lexer::Node::kGroup)
			break;
		if (node->type == Lexer::Node::kSymbol && node->text == ";")
			break;
		node = node->next;
	}
	return nodes;
}
