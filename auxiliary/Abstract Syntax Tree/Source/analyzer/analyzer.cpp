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
		
		//Copy the current leading ends and clear the set so we can fill them with the successors
		//again.
		std::set<Match *> currentEnds = leadingEnds;
		leadingEnds.clear();
		
		//Iterate over the current ends and advance each of them. Also keep track of the best match
		//so far.
		float bestMatch = 0;
		Match * best = NULL;
		bool anySafeMatches = false;
		for (std::set<Match *>::iterator m = currentEnds.begin(); m != currentEnds.end(); m++) {
			
            Match * cm = *m;
            
			//Decrease the expiration counter. If it reaches 0, don't bother to cope with this
			//match at all.
			if ((*m)->expiresIn > -1)
				if (--(*m)->expiresIn <= 0)
					continue;
			
			//If this is a recursive match, we have to check whether all of its non-recursive
			//siblings failed to match which will cause us to interrupt here to prevent an infinite
			//recursion.
			/*if ((*m)->isRecursive()) {
				//std::cout << "checking for recursion:" << std::endl;
				//std::cout << "\t" << (std::string)**m << std::endl;
				bool someMatched = false;
				bool someMatchedSafely = false;
				Match * pm = (*m)->getPrev();
                if (pm->isRecursive()) {
                    while (pm && pm->isRecursive()) {
                        Match * nm = pm->getNext();
                        while (nm && !someMatched) {
                            if (nm != *m && !nm->isRecursive()) {
                                if (currentEnds.count(nm))
                                    someMatched = true;
                                if (nm->isSafeMatch())
                                    someMatchedSafely = true;
                            }
                            nm = nm->getNextSibling();
                        }
                        pm = pm->getPrev();
                    }
                    if (!someMatched || someMatchedSafely) {
                        std::cout << "preventing recursion" << std::endl;
                        continue;
                    }
                }
			}*/
			
            //Fetch the best current end match.
            bool consider = true;
            if ((*m)->isRecursive()) {
                double bestCurrentMatch = 0;
                for (std::set<Match *>::iterator bcm = currentEnds.begin(); bcm != currentEnds.end(); bcm++) {
                    Match * sib = *bcm;
                    if (sib != *m && !sib->isRecursive()) {
                        if (sib->getUnsafeMatch() > bestCurrentMatch)
                            bestCurrentMatch = sib->getUnsafeMatch();
                    }
                }
                std::cout << "best sibling match " << bestCurrentMatch << std::endl;
                consider = (bestCurrentMatch < 1 - 1e-5);
            }
            
            if (consider) {
                //Make the successive matches.
                (*m)->makeNextMatch();
                
                //Iterate through them.
                Match * nm = (*m)->getNext();
                while (nm) {
                    
                    //Keep track of whether there were any safe matches.
                    if (nm->isSafeMatch())
                        anySafeMatches = true;
                    
                    //Keep track of the best match.
                    if (!best || nm->getUnsafeMatch() > bestMatch) {
                        best = nm;
                        bestMatch = nm->getUnsafeMatch();
                    }
                    
                    //If the match ran out of tokens, add it to the set of finished branches so we can
                    //come back later and find the one branch that scored the best.
                    if (!nm->getToken()) {
                        
                        //Iterate through the finished matches and find the lowest one.
                        Match * lowest = NULL;
                        float lowestMatch = 0;
                        if (finished.size() >= 3) {
                            for (std::set<Match *>::iterator fm = finished.begin();
                                 fm != finished.end(); fm++) {
                                if (!lowest || (*fm)->getSeriesMatch() < lowestMatch) {
                                    lowest = *fm;
                                    lowestMatch = (*fm)->getSeriesMatch();
                                }
                            }
                        }
                        
                        //Check whether the current match is better than the lowest in the finished set.
                        if (nm->getSeriesMatch() > lowestMatch) {
                            if (lowest)
                                finished.erase(lowest);
                            finished.insert(nm);
                        }
                    }
                    
                    //Otherwise we have to decide whether we want to follow this branch any further.
                    else {
                        leadingEnds.insert(nm);
                    }
                    
                    //Jump to the next sibling.
                    nm = nm->getNextSibling();
                }
            } else {
                leadingEnds.insert(*m);
            }
        }
		
        //Produce some debug output.
		for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++) {
			std::cout << (std::string)**m << " (" << (*m)->getUnsafeMatch()*100 << "%)";
			if ((*m)->expiresIn > -1) std::cout << " [expires in " << (*m)->expiresIn << "]";
			if ((*m)->isSafeMatch()) std::cout << " <--- safe ---*";
			std::cout << std::endl;
		}
        
		//Erase matches that lie too far behind the best.
		currentEnds = leadingEnds;
		for (std::set<Match *>::iterator m = currentEnds.begin(); m != currentEnds.end(); m++) {
			if ((*m)->getUnsafeMatch() < bestMatch * 0.75) {
                std::cout << "discarding " << (std::string)**m << std::endl;
				leadingEnds.erase(*m);
            }
        }
		
		//If there was a safe match, mark all leading ends that aren't as to expire in some defined
		//number of iterations.
		if (anySafeMatches)
			for (std::set<Match *>::iterator m = leadingEnds.begin(); m != leadingEnds.end(); m++)
				if (!(*m)->isSafeMatch() && (*m)->expiresIn < 0)
					(*m)->expiresIn = 3;
		
		std::cout << "---------------------------------" << std::endl;
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
		out << (std::string)**m << " (" << (*m)->getSeriesMatch()*100 << "%)" << std::endl;
		StructureNode * n = (*m)->getStructureNode();
		if (n)
			out << (std::string)*n << std::endl;
		out << std::endl;
	}
	
	temp = out.str();
	std::cout << std::endl << "FINISHED:" << std::endl << temp;
}
