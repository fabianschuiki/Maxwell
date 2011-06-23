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
	
	int tag;
	Match * parent;
	
public:
	float getMatch();
	
	//Token Iteration
	Token * getStartToken();
	Token * getNextToken();
	void setStartToken(Token * token);
	
	//Tagging
	int getTag();
	void setTag(int tag);
	Match * getParent();
	void setParent(Match * parent);
	
	virtual void notifyParent();
	virtual void childNotification(int tag, Match * child) {}
	
	//Construction
	Match();
	virtual ~Match() {}
	
	//Comparison
	bool compare();
	void compareAll();
	bool done();
	
	virtual std::vector<std::string> toStrings() = 0;
	virtual operator std::string() = 0;
};
