#include <iostream>
#include <set>
#include "analyzer.h"
#include "structure/node.h"
#include "match/match.h"


/*RootMatch * Analyzer::getRootMatch()
{
	return rootMatch;
}*/



Analyzer::Analyzer()
{
	//rootMatch = NULL;
}

Analyzer::~Analyzer()
{
	/*if (rootMatch)
		delete rootMatch;*/
}



void Analyzer::process(Token * token)
{
	//Delete the existing root match.
	/*if (rootMatch)
		delete rootMatch;
	rootMatch = NULL;*/
	
	//Abort if we don't have a valid token.
	if (!token) return;
	
	//Debug stuff.
	StructureNode class_super("class_super");
	class_super.fork()
	.add(new StructureToken(StructureToken::Symbol, "{"))
	.add(new StructureToken(StructureToken::Symbol, "}"))
	.safe();
	class_super.fork()
	.add(new StructureToken(StructureToken::Symbol, ":"))
	.add(new StructureToken(StructureToken::Identifier))
	.add(new StructureToken(StructureToken::Symbol, "{"))
	.add(new StructureToken(StructureToken::Symbol, "}"))
	.safe();
	
	StructureNode root("root");
	root.fork()
	.add(new StructureToken(StructureToken::Keyword, "class"))
	.add(new StructureToken(StructureToken::Identifier))
	.add(new StructureToken(StructureToken::Reference, &class_super));
	
	std::cout << (std::string)root;
	std::cout << (std::string)class_super;
	
	//Create a new matcher, just for testing.
	Match rootMatch(NULL, 0, 0);
	rootMatch.setSafe(true);
	rootMatch.setToken(token);
	rootMatch.makeNextMatch(&root);
	
	//Keep a set of current leading ends.
	std::set<Match *> leadingEnds;
	leadingEnds.insert(&rootMatch);
	while (!leadingEnds.empty()) {
		
		//Duplicate the set of matches since we need to iterate over them while modifying the
		//content.
		std::set<Match *> currentEnds = leadingEnds;
		leadingEnds.clear();
		
		//Iterate over the current ends, make the next matches for each and move all of them into
		//the leading ends set.
		for (std::set<Match *>::iterator m = currentEnds.begin(); m != currentEnds.end(); m++) {
			(*m)->makeNextMatch();
			Match * nm = (*m)->getNext();
			while (nm) {
				std::cout << (std::string)*(nm->getStructureToken()) << " = " << nm->getUnsafeMatch() * 100 << "%" << std::endl;
				leadingEnds.insert(nm);
				nm = nm->getNextSibling();
			}
		}
		//std::cout << leadingEnds.size() << " leading ends" << std::endl << std::endl;
	}
}
