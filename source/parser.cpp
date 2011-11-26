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


/** Parses the given root group of tokens. */
void Parser::parse(Lexer::Group * root)
{
	Lexer::Node * current = root->firstChild;
	
	//Process whatever is there.
	while (current) {
		Nodes nodes = scan(current);
		if (nodes.empty())
			break;
		
		//Dump the scanned nodes.
		std::cout << describeNodes(nodes) << std::endl;
		
		//Try to parse.
		parseFunction(nodes);
		
		//Fetch the last node we scanned and make its next node the current one
		//so parsing proceeds from there.
		Lexer::Node * last = nodes.back();
		current = last->next;
	}
}

/** Tries to parse the given nodes as function. */
bool Parser::parseFunction(const Nodes & nodes)
{
	//First of all check for the telltale sign this is a function which is the => symbol.
	int mapop = -1;
	for (int i = 0; i < nodes.size(); i++)
		if (nodes[i]->isSymbol("=>"))
			mapop = i;
	
	//The first token needs to be an identifier naming the function.
	Lexer::Node * name = nodes[0];
	if (!name->isIdentifier())
		return false;
	
	//Eat the input and output arguments.
	Nodes input, output;
	for (int i = 1; i < nodes.size() - 1; i++) {
		if (i < mapop)
			input.push_back(nodes[i]);
		if (i > mapop)
			output.push_back(nodes[i]);
	}
	
	//Dump stuff.
	std::cout << "function " << name->text << ", input " << describeNodes(input) << ", output " << describeNodes(output) << std::endl;
	return true;
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
		Lexer::Group * group = (Lexer::Group *)node;
		if (node->type == Lexer::Node::kGroup && group->subtype == Lexer::Group::kBraces)
			break;
		if (node->type == Lexer::Node::kSymbol && node->text == ";")
			break;
		node = node->next;
	}
	return nodes;
}
