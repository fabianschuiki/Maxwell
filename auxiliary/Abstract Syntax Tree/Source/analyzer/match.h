#pragma once
#include <vector>
#include <string>
#include "../tokenizer/token.h"


class Match {
protected:
	float match;
	
	Token * startToken;
	Token * token;
	
	bool isDone;
	bool isPrepared;
	
	virtual void prepareCompare() {}
	virtual bool compareNext() = 0;
	
public:
	float getMatch();
	
	Token * getStartToken();
	Token * getNextToken();
	void setStartToken(Token * token);
	
	Match();
	virtual ~Match() {}
	
	bool compare();
	void compareAll();
	bool done();
	
	virtual std::vector<std::string> toStrings() = 0;
};
