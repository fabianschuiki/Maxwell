#include <assert.h>
#include <math.h>
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
	.opt()
	.add(new StructureToken(StructureToken::Symbol, ":"))/*.safe()*/
	.add(new StructureToken(StructureToken::Identifier))
	.done()
	.opt()
	.add(new StructureToken(StructureToken::Symbol, "<"))/*.safe()*/
	.add(new StructureToken(StructureToken::Identifier))
	.many()
	.add(new StructureToken(StructureToken::Symbol, ","))
	.add(new StructureToken(StructureToken::Identifier))
	.done()
	.add(new StructureToken(StructureToken::Symbol, ">"))/*.safe()*/
	.done()
	//.add(new StructureToken(StructureToken::Reference, &class_super))
	//.add(new StructureToken(StructureToken::Reference, &class_intf_decl))
	//.add(new StructureToken(StructureToken::Symbol, ";"))/*.safe()*/
	.add(new StructureToken(StructureToken::Symbol, "{"))
	.add(new StructureToken(StructureToken::Symbol, "}"))
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
	root.fork()
	.many()
	.add(new StructureToken(StructureToken::Reference, &class_decl/*s*/))
	.done();
	
	std::cout << (std::string)class_decl;
	//std::cout << (std::string)class_super;
	
	//Create a new matcher, just for testing.
	Match rootMatch(NULL, 0, 0);
	rootMatch.setSafe(true);
	rootMatch.setToken(token);
	rootMatch.makeNextMatch(&root);
	
	//Keep a set of current leading ends.
	std::set<Match *> leadingEnds, currentEnds, finished;
	std::set<Match *> branches;
	leadingEnds.insert(&rootMatch);
	branches.insert(&rootMatch);
	float bestFinishedMatch = 0;
	
	//As long as there are any leading ends, keep advancing in the matching process.
	int iterations = 0;
	while (!leadingEnds.empty() && bestFinishedMatch < 0.9) {
		if (iterations++ > 200) {
			std::cout << "ABORTING" << std::endl;
			break;
		}
		
		//Duplicate the set of matches since we need to iterate over them while modifying the
		//content.
		currentEnds = leadingEnds;
		//leadingEnds.clear();
		
		//Get rid of matches that lie too far behind the best finished match.
		for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++)
			if ((*m)->getUnsafeMatch() < bestFinishedMatch * 0.5)
				leadingEnds.erase(m);
		
		//Iterate over the current ends and find either the first one that doesn't match, which has
		//the highest priority, or the one yielding the best match so far.
		float bestMatch = 0;
		Match * best = NULL;
		bool wasBestMatch = true;
		for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++) {
			float match = (*m)->getUnsafeMatch();
			//std::cout << (std::string)**m << " (" << match*100 << "%)" << std::endl;
			if ((*m)->dontMatch()) {
				best = (*m);
				bestMatch = match;
				wasBestMatch = false;
				break;
			}
			if (!best || match > bestMatch) {
				best = (*m);
				bestMatch = match;
			}
		}
		
		//Erase matches that are too weak.
		/*for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++)
			if (((*m)->triesLeft > 0 && --(*m)->triesLeft == 0))
				leadingEnds.erase(m);*/
		
		//Produce some debug output.
		/*for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++) {
			std::cout << (std::string)**m << " (" << (*m)->getUnsafeMatch()*100 << "%)";
			if ((*m)->triesLeft >= 0) std::cout << " [" << (*m)->triesLeft << " to beat "
				<< (*m)->matchToBeat*100 << "%]";
			if (best == *m) std::cout << " <--*";
			std::cout << std::endl;
		}
		std::cout << std::endl;*/
		
		//If there was a best match found, calculate its next matches
		bool anySafeMatch = false;
		float bestSafeMatch = 0;
		if (best) {
			leadingEnds.erase(best);
			//best->triesLeft = -1;
			best->makeNextMatch();
			Match * nm = best->getNext();
			while (nm) {
				if (best->triesLeft > 0)
					nm->triesLeft = (best->triesLeft - 1);
				nm->matchToBeat = best->matchToBeat;
				
				if (nm->getToken()) {
					if (wasBestMatch) {
						if (nm->isSafeMatch()) {
							anySafeMatch = true;
							bestSafeMatch = nm->getUnsafeMatch();
						}
						nm->triesLeft = -1;
					}
					
					//Add this to the leading ends if it matches at least a bit.
					//if (nm->getUnsafeMatch() > 0.5)
					if (nm->triesLeft != 0)
						leadingEnds.insert(nm);
					
					//Keep track of this branch.
					branches.erase(nm->getPrev());
					branches.insert(nm);
				} else {
					finished.insert(nm);
					bestFinishedMatch = std::max<float>(bestFinishedMatch, nm->getUnsafeMatch());
				}
				
				//Jump to the next sibling.
				nm = nm->getNextSibling();
			}
		}
		
		//Debug copying.
		if (!leadingEnds.empty())
			currentEnds = leadingEnds;
		
		//If there were any safe matches, iterate through the leading ends and remove all that are
		//no such match.
		if (anySafeMatch) {
			for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++) {
				if (!(*m)->isSafeMatch() && (*m)->triesLeft == -1) {
					(*m)->triesLeft = 2;
					(*m)->matchToBeat = bestSafeMatch;
				}
			}
		}
		
		//Dump the branches.
		/*std::cout << "-----" << std::endl;
		for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++)
			std::cout << (std::string)**m << std::endl;*/
	}
	
	//Dump the branches.
	/*std::cout << std::endl;
	for (std::set<Match *>::iterator m = branches.begin(); m != branches.end(); m++)
		std::cout << (std::string)**m << (currentEnds.count(*m) ? "" : " ◼")
		<< "   | " << (*m)->getUnsafeMatch() * 100 << "%" << std::endl;*/
	/*std::cout << std::endl;
	for (std::set<Match *>::iterator m = finished.begin(); m != finished.end(); m++)
		std::cout << (std::string)**m
		<< "   | " << (*m)->getUnsafeMatch() * 100 << "%" << std::endl;*/
	
	//Dump some stuff to the user window.
	std::stringstream out;
	for (std::set<Match *>::iterator m = finished.begin(); m != finished.end(); m++) {
		out << (std::string)**m << " (" << (*m)->getUnsafeMatch()*100 << "%)" << std::endl;
		StructureNode * n = (*m)->getStructureNode();
		if (n)
			out << (std::string)*n << std::endl;
		out << std::endl;
	}
	
	temp = out.str();
}
