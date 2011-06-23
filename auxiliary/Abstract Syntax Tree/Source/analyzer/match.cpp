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
	
	isDone = false;
	isPrepared = false;
}



Match::Match()
{
	match = 0;
	isDone = false;
	isPrepared = false;
}



void Match::compare()
{
	if (!isPrepared) {
		prepareCompare();
		isPrepared = true;
	}
	compareNext();
}

void Match::compareAll()
{
	while (!compare());
}

bool Match::done()
{
	return isDone;
}
