#include "parallel.h"


Match * ParallelMatch::getBestMatch()
{
	return bestMatch;
}



void ParallelMatch::prepareCompare()
{
	Match::prepareCompare();
	
	//Prepare the submatches if required.
	if (submatches.empty())
		prepareMatches();
	
	//Set the start token for all submatches.
	for (std::vector<Match *>::iterator m = submatches.begin(); m != submatches.end(); m++)
		(*m)->setStartToken(startToken);
}

bool ParallelMatch::compareNext()
{
	//Iterate through the submatches an ask each to compare one step if they're not done. Keep track
	//of the submatch that currently gives the best results.
	int submatchesNotDone = 0;
	bestMatch = NULL;
	match = 0;
	
	for (std::vector<Match *>::iterator m = submatches.begin(); m != submatches.end(); m++) {
		if (!(*m)->done()) {
			submatchesNotDone++;
			(*m)->compare();
		}
		if ((*m)->getMatch() > match || !bestMatch) {
			bestMatch = (*m);
			match = (*m)->getMatch();
			token = bestMatch->getNextToken();
		}
	}
	
	//Remember whether all submatches are done for outside access.
	isDone = (submatchesNotDone == 0);
	
	//Return whether all submatches were done.
	return isDone;
}



std::vector<std::string> ParallelMatch::toStrings()
{
	std::vector<std::string> s;
	
	//Iterate through all the submatches, ask each for its strings and add them all to the final
	//list.
	for (std::vector<Match *>::iterator m = submatches.begin(); m != submatches.end(); m++) {
		std::vector<std::string> strings = (*m)->toStrings();
		for (std::vector<std::string>::iterator ns = strings.begin(); ns != strings.end(); ns++)
			s.push_back(*ns);
	}
	return s;
}
