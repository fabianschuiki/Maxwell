#pragma once
#include "../tokenizer/token.h"


class Match {
private:
	float match;
	
public:
	float getMatch();
	std::string temp;
	
	void compare(Token * token);
};
