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
	std::set<Match *> branches;
	leadingEnds.insert(rootMatch);
	branches.insert(rootMatch);
	float bestFinishedMatch = 0;
	
	//As long as there are any leading ends, keep advancing in the matching process.
	while (!leadingEnds.empty()) {
        
        //Find the most promising recursive and non-recursive leading ends.
        Match * bestNonRecursive = NULL;
        Match * bestRecursive = NULL;
        double bestNonRecursiveMatch = 0;
        double bestRecursiveMatch = 0;
        unsigned int bestRecursiveDepth = 0;
		for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++) {
            double match = (*m)->getFinalMatch();
            unsigned int depth = (*m)->getDepth();
            if ((*m)->isRecursive()) {
                if (!bestRecursive || (match >= bestRecursiveMatch && depth <= bestRecursiveDepth)) {
                    bestRecursive = *m;
                    bestRecursiveMatch = match;
                    bestRecursiveDepth = depth;
                }
            } else {
                if (!bestNonRecursive || match >= bestNonRecursiveMatch) {
                    bestNonRecursive = *m;
                    bestNonRecursiveMatch = match;
                }
            }
        }
		
        //Decide what leading end to follow.
        Match * follow;
        double followMatch;
        if (bestNonRecursive && bestNonRecursiveMatch >= 0.95) {
            follow = bestNonRecursive;
            followMatch = bestNonRecursiveMatch;
        } else {
            follow = bestRecursive;
            followMatch = bestRecursiveMatch;
        }
        
        //Show what we've found.
        std::cout << "recursive:     ";
        if (bestRecursive)
            std::cout << (std::string)*bestRecursive << " (" << bestRecursiveMatch << ", " << bestRecursiveDepth << ")" << (follow == bestRecursive ? " <!>" : "") << "\n";
        else
            std::cout << "none\n";
        if (bestNonRecursive)
            std::cout << "non-recursive: " << (std::string)*bestNonRecursive << " (" << bestNonRecursiveMatch << ", " << bestNonRecursive->getDepth() << ")" << (follow == bestNonRecursive ? " <!>" : "") << "\n";
        else
            std::cout << "none\n";
        
        //DEBUG: Subline.
		std::cout << std::string(40, '-') << std::endl;
        
        //Advance the leading end we've found and remove it from the list of leading ends.
        follow->makeNextMatch();
        leadingEnds.erase(follow);
        
        //Iterate through the the submatches we created and add each to the list of leading ends.
        /*if (follow->getStructureNode())
            std::cout << (std::string)*follow->getStructureNode() << "\n";*/
        std::set<Match *> safeMatches;
        for (Match * m = follow->getNext(); m; m = m->getNextSibling()) {
            std::cout << "spawned: " << (std::string)*m << " (" << m->getFinalMatch() << ", " << m->getDepth() << ")\n";
            leadingEnds.insert(m);
            if (m->isSafeMatch())
                safeMatches.insert(m);
        }
        
        //If there were any safe matches, they replace the leading ends.
        if (!safeMatches.empty()) {
            std::cout << safeMatches.size() << " safe matches replace " << leadingEnds.size() << " leading ends.\n";
            leadingEnds = safeMatches;
        }
		
        //DEBUG: Line.
		std::cout << std::string(40, '=') << std::endl;
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
	
	/*//Dump some stuff to the user window.
	std::stringstream out;
	for (std::set<Match *>::iterator m = finished.begin(); m != finished.end(); m++) {
		out << (std::string)**m << " (" << (*m)->getSeriesMatch()*100 << "%)" << std::endl;
		StructureNode * n = (*m)->getStructureNode();
		if (n)
			out << (std::string)*n << std::endl;
		out << std::endl;
	}
	
	temp = out.str();
	std::cout << std::endl << "FINISHED:" << std::endl << temp;*/
}
