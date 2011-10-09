#pragma once
#include <istream>
#include "token.h"


class Tokenizer {
private:
	Token * firstToken;
	Token * lastToken;
	
	void addToken(Token * token);
	
public:
	Token * getFirstToken();
	
	Tokenizer();
	~Tokenizer();
	
	void process(std::istream & input);
};
