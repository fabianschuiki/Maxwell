#pragma once
#include "../tokenizer/token.h"


class Match {
protected:
	float match;
	
public:
	float getMatch();
	
	Match();
	virtual ~Match() {}
	
	virtual void compare(Token * token) = 0;
};
