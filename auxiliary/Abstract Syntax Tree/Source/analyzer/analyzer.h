#pragma once
#include "../tokenizer/token.h"


class Analyzer {
private:
	//Match * rootMatch;
	
public:
	Analyzer();
	~Analyzer();
	
	//Match * getRootMatch();
	
	void process(Token * token);
	
	std::string temp;
};
