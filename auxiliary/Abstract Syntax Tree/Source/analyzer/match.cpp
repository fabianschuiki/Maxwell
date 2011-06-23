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



int Match::getTag()
{
	return tag;
}

void Match::setTag(int t)
{
	tag = t;
}

Match * Match::getParent()
{
	return parent;
}

void Match::setParent(Match * p)
{
	parent = p;
}

void Match::notifyParent()
{
	if (parent)
		parent->childNotification(tag, this);
}



Match::Match()
{
	match = 0;
	isDone = false;
	isPrepared = false;
}



bool Match::compare()
{
	if (!isPrepared) {
		prepareCompare();
		isPrepared = true;
	}
	return compareNext();
}

void Match::compareAll()
{
	while (!compare());
}

bool Match::done()
{
	return isDone;
}
