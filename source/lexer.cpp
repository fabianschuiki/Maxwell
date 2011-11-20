#include <sstream>
#include "lexer.h"
using namespace Lexer;


Node::Node(Type t) : type(t) {}
Group::Group(Subtype s) : Node(TypeGroup), subtype(s) {}
Identifier::Identifier() : Node(TypeIdentifier) {}

Group * Lexer::parse(std::istream * in)
{
	std::stringstream buffer;
	enum {
		ContextRoot,
	} context = ContextRoot;
	
	//Initialize the root group.
	Group * root = new Group(Group::SubtypeRoot);
	
	//Iterate through the input stream and accumulate nodes.
	char inc[2] = {0, 0};
	while (!in->eof())
	{
		//Read the next character and move the character archive.
		inc[0] = inc[1];
		inc[1] = in->getchar();
	}
	
	//Return the root.
	return root;
}
