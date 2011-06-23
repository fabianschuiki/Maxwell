#include <iostream>
#include "class.h"
#include "string.h"


void ClassMatch::prepareCompare()
{
	SeriesMatch::prepareCompare();
	//reset everything...
}

void ClassMatch::prepareMatches()
{
	matches.push_back(new StringMatch("class"));
}

void ClassMatch::childNotification(int tag, Match * child)
{
	std::cout << "class child " << tag << " = " << child << std::endl;
}
