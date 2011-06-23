#include "parallel.h"


Match * ParallelMatch::getBestMatch()
{
	return bestMatch;
}



void ParallelMatch::prepareCompare()
{
	Match::prepareCompare();
	
	//Prepare the matches if required.
	if (matches.empty())
		prepareMatches();
	
	//Set the start token for all matches.
	for (std::vector<Match *>::iterator m = matches.begin(); m != matches.end(); m++)
		(*m)->setStartToken(startToken);
}

bool ParallelMatch::compareNext()
{
	//Iterate through the matches an ask each to compare one step if they're not done. Keep track
	//of the submatch that currently gives the best results.
	int matchesNotDone = 0;
	bestMatch = NULL;
	match = 0;
	
	for (std::vector<Match *>::iterator m = matches.begin(); m != matches.end(); m++) {
		if (!(*m)->done()) {
			matchesNotDone++;
			(*m)->compare();
		}
		if ((*m)->getMatch() > match || !bestMatch) {
			bestMatch = (*m);
			match = (*m)->getMatch();
			token = bestMatch->getNextToken();
		}
	}
	
	//Remember whether all matches are done for outside access.
	isDone = (matchesNotDone == 0);
	
	//Return whether all matches were done.
	return isDone;
}



std::vector<std::string> ParallelMatch::toStrings()
{
	std::vector<std::string> s;
	
	//Iterate through all the matches, ask each for its strings and add them all to the final
	//list.
	for (std::vector<Match *>::iterator m = matches.begin(); m != matches.end(); m++) {
		std::vector<std::string> strings = (*m)->toStrings();
		for (std::vector<std::string>::iterator ns = strings.begin(); ns != strings.end(); ns++)
			s.push_back(*ns);
	}
	return s;
}

ParallelMatch::operator std::string()
{
	if (bestMatch)
		return (std::string)*bestMatch;
	return "";
}
