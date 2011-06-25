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
	std::cout << "------------------------------------------------------------" << std::endl;
	
	//Debug stuff.
	/*StructureNode class_super("class_super");
	class_super.fork().add(new StructureToken(StructureToken::Empty));
	class_super.fork()
	.add(new StructureToken(StructureToken::Symbol, ":")).safe()
	.add(new StructureToken(StructureToken::Identifier))
	;*/
	
	/*StructureNode class_intf("class_intf");
	class_intf.fork()
	.add(new StructureToken(StructureToken::Identifier))
	;
	
	StructureNode class_intfs("class_intfs");
	class_intfs.fork()
	.add(new StructureToken(StructureToken::Reference, &class_intf))
	;
	class_intfs.fork()
	.add(new StructureToken(StructureToken::Reference, &class_intf))
	.add(new StructureToken(StructureToken::Symbol, ",")).safe()
	.add(new StructureToken(StructureToken::Reference, &class_intfs))
	;
	
	StructureNode class_intf_decl("class_intf_decl");
	class_intf_decl.fork().add(new StructureToken(StructureToken::Empty));
	class_intf_decl.fork()
	.add(new StructureToken(StructureToken::Symbol, "<")).safe()
	.add(new StructureToken(StructureToken::Reference, &class_intfs))
	.add(new StructureToken(StructureToken::Symbol, ">")).safe()
	;*/
	
	StructureNode class_decl("class_decl");
	class_decl.fork()
	.add(new StructureToken(StructureToken::Keyword, "class"))
	.add(new StructureToken(StructureToken::Identifier))
	.add(new StructureToken(StructureToken::Symbol, ":"))
	.opt()
	.add(new StructureToken(StructureToken::Identifier))
	.done()
	//.add(new StructureToken(StructureToken::Reference, &class_super))
	//.add(new StructureToken(StructureToken::Reference, &class_intf_decl))
	.add(new StructureToken(StructureToken::Symbol, ";")).safe()
	;
	
	/*StructureNode class_decls("class_decls");
	class_decls.fork()
	.add(new StructureToken(StructureToken::Reference, &class_decl))
	;
	class_decls.fork()
	.add(new StructureToken(StructureToken::Reference, &class_decl))
	.add(new StructureToken(StructureToken::Reference, &class_decls))
	;*/
	
	StructureNode root("root");
	root.fork().add(new StructureToken(StructureToken::Reference, &class_decl/*s*/));
	
	std::cout << (std::string)root;
	//std::cout << (std::string)class_super;
	
	//Create a new matcher, just for testing.
	Match rootMatch(NULL, 0, 0);
	rootMatch.setSafe(true);
	rootMatch.setToken(token);
	rootMatch.makeNextMatch(&root);
	
	//Keep a set of current leading ends.
	std::set<Match *> leadingEnds, currentEnds;
	std::set<Match *> branches;
	leadingEnds.insert(&rootMatch);
	branches.insert(&rootMatch);
	
	//As long as there are any leading ends, keep advancing in the matching process.
	while (!leadingEnds.empty()) {
		
		//Duplicate the set of matches since we need to iterate over them while modifying the
		//content.
		currentEnds = leadingEnds;
		leadingEnds.clear();
		
		//Iterate over the current ends, make the next matches for each and move all of them into
		//the leading ends set.
		bool anySafeMatch = false;
		for (std::set<Match *>::iterator m = currentEnds.begin(); m != currentEnds.end(); m++) {
			(*m)->makeNextMatch();
			Match * nm = (*m)->getNext();
			while (nm) {
				if (nm->getToken()) {
					if (nm->isSafeMatch())
						anySafeMatch = true;
					
					//Add this to the leading ends.
					leadingEnds.insert(nm);
					
					//Keep track of this branch.
					branches.erase(nm->getPrev());
					branches.insert(nm);
				}
				//std::cout << (std::string)*nm << std::endl;
				
				//Jump to the next sibling.
				nm = nm->getNextSibling();
			}
		}
		
		//If there were any safe matches, iterate through the leading ends and remove all that are
		//no such match.
		if (anySafeMatch)
			for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++)
				if (!(*m)->isSafeMatch())
					leadingEnds.erase(m);
		
		//Debug copying.
		if (!leadingEnds.empty())
			currentEnds = leadingEnds;
		
		//Dump the branches.
		/*std::cout << "-----" << std::endl;
		for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++)
			std::cout << (std::string)**m << std::endl;*/
	}
	
	//Dump the branches.
	for (std::set<Match *>::iterator m = branches.begin(); m != branches.end(); m++)
		std::cout << (std::string)**m << (currentEnds.count(*m) ? "" : " ◼") << std::endl;
	
	//Dump some stuff to the user window.
	std::stringstream out;
	for (std::set<Match *>::iterator m = currentEnds.begin(); m != currentEnds.end(); m++) {
		out << (std::string)**m << std::endl;
		StructureNode * n = (*m)->getStructureNode();
		if (n)
			out << (std::string)*n << std::endl;
		out << std::endl;
	}
	
	temp = out.str();
}
