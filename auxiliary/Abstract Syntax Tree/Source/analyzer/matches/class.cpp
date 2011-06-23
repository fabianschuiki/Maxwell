#include <iostream>
#include "class.h"


void ClassMatch::prepareCompare()
{
	//reset everything...
}

void ClassMatch::prepareMatches()
{
}

void ClassMatch::childNotification(int tag, Match * child)
{
	std::cout << "class child " << tag << " = " << child << std::endl;
}
