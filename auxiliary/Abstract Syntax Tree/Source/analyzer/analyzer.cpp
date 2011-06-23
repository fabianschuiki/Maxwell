#include "analyzer.h"
#include "matches/parallel.h"
#include "matches/string.h"
#include "matches/series.h"


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
	StringMatch kw11("property");
	StringMatch kw12("readonly");
	StringMatch kw21("construct");
	StringMatch kw22("automatically");
	SeriesMatch sm1, sm2;
	sm1.submatches.push_back(&kw11);
	sm1.submatches.push_back(&kw12);
	sm2.submatches.push_back(&kw21);
	sm2.submatches.push_back(&kw22);
	pm.submatches.push_back(&sm1);
	pm.submatches.push_back(&sm2);
	
	pm.setStartToken(token);
	pm.compareAll();
	
	Match * best = pm.getBestMatch();
	std::stringstream s;
	s << best->getMatch() * 100 << "%" << std::endl << std::endl;
	std::vector<std::string> strings = best->toStrings();
	for (int i = 0; i < strings.size(); i++)
		s << strings[i] << std::endl;
	temp = s.str();
}
