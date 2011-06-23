#pragma once
#include <vector>
#include "../match.h"


class ParallelMatch : public Match {
private:
	Match * bestMatch;
	
protected:
	std::vector<Match *> submatches;
	
	virtual void prepareCompare();
	virtual void prepareMatches() {}
	virtual bool compareNext();
	
public:
	Match * getBestMatch();
	
	virtual std::vector<std::string> toStrings();
};
