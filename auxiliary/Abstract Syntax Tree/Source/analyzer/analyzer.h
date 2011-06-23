#pragma once
#include "match.h"


class Analyzer {
private:
	Match * rootMatch;
	
public:
	Match * getRootMatch();
	
	Analyzer();
	~Analyzer();
	
	void process(Token * token);
};
