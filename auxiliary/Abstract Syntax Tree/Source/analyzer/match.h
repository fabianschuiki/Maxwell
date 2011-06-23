#pragma once
#include "../tokenizer/token.h"


class Match {
protected:
	float match;
	
	Token * startToken;
	Token * token;
	
	bool isDone;
	bool isPrepared;
	
public:
	float getMatch();
	
	Token * getStartToken();
	Token * getNextToken();
	void setStartToken(Token * token);
	
	Match();
	virtual ~Match() {}
	
	virtual void prepareCompare() {}
	virtual bool compareNext() = 0;
	void compare();
	void compareAll();
	bool done();
};
