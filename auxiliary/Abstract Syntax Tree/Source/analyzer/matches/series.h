#pragma once
#include <vector>
#include "../match.h"


class SeriesMatch : public Match {
private:
	bool submatchAdvanced;
	int position;
	
protected:
	std::vector<Match *> matches;
	
	virtual void prepareCompare();
	virtual void prepareMatches() {}
	virtual bool compareNext();
	
public:
	virtual std::vector<std::string> toStrings();
	virtual operator std::string();
};
