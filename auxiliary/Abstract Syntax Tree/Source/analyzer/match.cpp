#include "match.h"


float Match::getMatch()
{
	return match;
}



Token * Match::getStartToken()
{
	return startToken;
}

Token * Match::getNextToken()
{
	return token;
}

void Match::setStartToken(Token * t)
{
	startToken = t;
	token = t;
}



Match::Match()
{
	match = 0;
}
