#include <assert.h>
#include <math.h>
#include <iostream>
#include <set>
#include "analyzer.h"
#include "structure/root.h"


Match * Analyzer::getRootMatch()
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
	
	//Create the root structure instance which holds a template of the entire Maxwell syntax tree.
	StructureRoot root;
	
	//Create a new root match.
	rootMatch = new Match(NULL, 0, 0);
	rootMatch->setSafe(true);
	rootMatch->setToken(token);
	rootMatch->makeNextMatch(&root);
	
	//Keep a set of current leading ends.
	std::set<Match *> leadingEnds, finished;
	//std::set<Match *> branches;
	leadingEnds.insert(rootMatch);
	//branches.insert(rootMatch);
	float bestFinishedMatch = 0;
	
	//As long as there are any leading ends, keep advancing in the matching process.
	int iterations = 0;
	while (!leadingEnds.empty() && bestFinishedMatch < 0.9) {
		//assert(iterations++ < 20000);
		
		//Get rid of matches that lie too far behind the best finished match.
		for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++)
			if ((*m)->getSeriesMatch() < bestFinishedMatch * 0.5)
				leadingEnds.erase(m);
		
		//Iterate over the current ends and find either the first one that doesn't match, which has
		//the highest priority, or the one yielding the best match so far.
		float bestMatch = 0;
		Match * best = NULL;
		bool wasBestMatch = true;
		for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++) {
			float match = (*m)->getSeriesMatch();
			//std::cout << (std::string)**m << " (" << match*100 << "%)" << std::endl;
			if ((*m)->dontMatch() && !(*m)->isRecursive()) {
				best = (*m);
				bestMatch = match;
				wasBestMatch = false;
			}
			if (wasBestMatch && (!best || best->isRecursive() || match > bestMatch)) {
				best = (*m);
				bestMatch = match;
			}
			
			if (match < 0.75 && (*m)->triesLeft == -1)
				(*m)->triesLeft = (match / 0.75) * 5;
		}
		
		//Erase matches that are too weak.
		/*for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++)
			if (((*m)->triesLeft > 0 && --(*m)->triesLeft == 0))
				leadingEnds.erase(m);*/
		
		//Produce some debug output.
		for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++) {
			std::cout << (std::string)**m << " (" << (*m)->getSeriesMatch()*100 << "%, Δ"
			<< (*m)->getDeltaMatch()*100 << "%)";
			if ((*m)->triesLeft >= 0) std::cout << " [" << (*m)->triesLeft << "]";
			if (best == *m) std::cout << " <--*";
			std::cout << std::endl;
		}
		std::cout << std::endl;
		
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
							bestSafeMatch = nm->getSeriesMatch();
						}
						if (nm->getDeltaMatch() >= 0)
							nm->triesLeft = -1;
					}
					
					//Add this to the leading ends if it matches at least a bit and there are no
					//equivalent matches present.
					if (nm->triesLeft != 0 && nm->getSeriesMatch() > 0.5) {
						/*bool equivalent = false;
						for*/
						leadingEnds.insert(nm);
					}
					
					//Keep track of this branch.
					/*branches.erase(nm->getPrev());
					branches.insert(nm);*/
				} else {
					finished.insert(nm);
					bestFinishedMatch = std::max<float>(bestFinishedMatch, nm->getSeriesMatch());
					std::cout << "match: " << (std::string)*nm << std::endl;
				}
				
				//Jump to the next sibling.
				nm = nm->getNextSibling();
			}
		}
		
		//If there were any safe matches, iterate through the leading ends and remove all that are
		//no such match.
		if (anySafeMatch)
			for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++)
				if (!(*m)->isSafeMatch() && (*m)->triesLeft == -1)
					(*m)->triesLeft = 2;
		
		//If there are no more leading ends and we have no finished branch, insert the last end we
		//tried into the finished array.
		if (leadingEnds.empty() && finished.empty())
			finished.insert(best);
		
		//Dump the branches.
		/*std::cout << "-----" << std::endl;
		for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++)
			std::cout << (std::string)**m << std::endl;*/
	}
	
	//Dump the branches.
	/*std::cout << std::endl;
	for (std::set<Match *>::iterator m = branches.begin(); m != branches.end(); m++)
		std::cout << (std::string)**m << (currentEnds.count(*m) ? "" : " ◼")
		<< "   | " << (*m)->getSeriesMatch() * 100 << "%" << std::endl;*/
	/*std::cout << std::endl;
	for (std::set<Match *>::iterator m = finished.begin(); m != finished.end(); m++)
		std::cout << (std::string)**m
		<< "   | " << (*m)->getSeriesMatch() * 100 << "%" << std::endl;*/
	
	//Dump some stuff to the user window.
	std::stringstream out;
	for (std::set<Match *>::iterator m = finished.begin(); m != finished.end(); m++) {
		out << (std::string)**m << " (" << (*m)->getSeriesMatch()*100 << "%)" << std::endl;
		StructureNode * n = (*m)->getStructureNode();
		if (n)
			out << (std::string)*n << std::endl;
		out << std::endl;
	}
	
	temp = out.str();
}
