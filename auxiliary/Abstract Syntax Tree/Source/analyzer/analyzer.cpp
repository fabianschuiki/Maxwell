#include "analyzer.h"
#include "matches/parallel.h"
#include "matches/string.h"


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
	
	//Abort if we don't have a valid token.
	if (!token) return;
	
	//Do some debug matching.
	ParallelMatch pm;
	StringMatch kw1("class");
	StringMatch kw2("construct");
	StringMatch kw3("automatically");
	pm.submatches.push_back(&kw1);
	pm.submatches.push_back(&kw2);
	pm.submatches.push_back(&kw3);
	pm.setStartToken(token);
	pm.compareAll();
}
