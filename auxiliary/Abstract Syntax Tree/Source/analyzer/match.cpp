#include "match.h"
#include <iostream>


void Match::compare(Token * token)
{
	std::string text("automatically");
	
	std::string::const_iterator t, u;
	t = token->text.begin();
	u =        text.begin();
	
	int matchUntil = 0;
	for (; t != token->text.end() && u != text.end(); t++, u++) {
		if (*t == *u)
			matchUntil++;
		else
			break;
	}
	
	match = (double)matchUntil / text.size();
	std::cout << text << std::endl;
	std::cout << std::string(matchUntil, ' ') << '^' << std::endl;
}
