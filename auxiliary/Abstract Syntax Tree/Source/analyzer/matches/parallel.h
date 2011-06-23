#pragma once
#include <vector>
#include "../match.h"


class ParallelMatch : public Match {
private:
	Match * bestMatch;
	
public:
	std::vector<Match *> submatches;
	
	virtual void prepareCompare();
	virtual bool compareNext();
	
public:
	Match * getBestMatch();
	
	virtual std::vector<std::string> toStrings();
};
