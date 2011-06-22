#include "tokenizer.h"


void Tokenizer::addToken(Token * token)
{
	if (lastToken)
		lastToken->next = token;
	lastToken = token;
	if (!firstToken)
		firstToken = lastToken;
}



Token * Tokenizer::getFirstToken()
{
	return firstToken;
}



Tokenizer::Tokenizer()
{
	firstToken = NULL;
	lastToken = NULL;
}

Tokenizer::~Tokenizer()
{
	if (firstToken)
		delete firstToken;
}



void Tokenizer::process(std::istream & input)
{
}
