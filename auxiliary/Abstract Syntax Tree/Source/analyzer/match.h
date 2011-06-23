#pragma once
#include "../tokenizer/token.h"


class Match {
protected:
	float match;
	
	Token * startToken;
	Token * token;
	
public:
	float getMatch();
	
	Token * getStartToken();
	Token * getNextToken();
	void setStartToken(Token * token);
	
	Match();
	virtual ~Match() {}
	
	virtual bool compare() = 0;
};
