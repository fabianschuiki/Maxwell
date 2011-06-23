#pragma once
#include <vector>
#include "../match.h"


class ParallelMatch : public Match {
public:
	std::vector<Match *> submatches;
	bool submatchesDone;
	
public:
	virtual void prepareCompare();
	virtual bool compareNext();
};
