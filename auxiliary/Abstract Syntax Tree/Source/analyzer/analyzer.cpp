#include "analyzer.h"
#include "matches/parallel.h"
#include "matches/string.h"
#include "matches/series.h"


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
	
	//Initialize a new root match and do the matching magic.
	rootMatch = new RootMatch;
	rootMatch->setStartToken(token);
	rootMatch->compareAll();
	
	//Dump the best match for debugging purposes.
	Match * best = rootMatch->getBestMatch();
	std::stringstream s;
	if (best) {
		s << best->getMatch() * 100 << "%" << std::endl << std::endl;
		std::vector<std::string> strings = best->toStrings();
		for (int i = 0; i < strings.size(); i++)
			s << strings[i] << std::endl;
	}
	temp = s.str();
}
