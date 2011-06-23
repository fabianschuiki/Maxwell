#pragma once
#include "matches/root.h"


class Analyzer {
private:
	RootMatch * rootMatch;
	
public:
	RootMatch * getRootMatch();
	
	Analyzer();
	~Analyzer();
	
	void process(Token * token);
	
	std::string temp;
};
