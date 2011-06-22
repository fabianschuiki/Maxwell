#pragma once
#include "../tokenizer/token.h"


class Match {
private:
	float match;
	
public:
	float getMatch();
	
	void compare(Token * token);
};
