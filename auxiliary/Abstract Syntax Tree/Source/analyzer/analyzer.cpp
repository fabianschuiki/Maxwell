#include <iostream>
#include "analyzer.h"
#include "structure/node.h"


RootMatch * Analyzer::getRootMatch()
{
	return rootMatch;
}



Analyzer::Analyzer()
{
	rootMatch = NULL;
}

Analyzer::~Analyzer()
{
	if (rootMatch)
		delete rootMatch;
}



void Analyzer::process(Token * token)
{
	//Delete the existing root match.
	if (rootMatch)
		delete rootMatch;
	rootMatch = NULL;
	
	//Abort if we don't have a valid token.
	if (!token) return;
	
	//Debug stuff.
	StructureNode root("root");
	root.fork()
	.add(new StructureToken(StructureToken::Keyword, "class"))
	.add(new StructureToken(StructureToken::Identifier))
	.add(new StructureToken(StructureToken::Symbol, ":"));
	
	std::cout << (std::string)root;
}
