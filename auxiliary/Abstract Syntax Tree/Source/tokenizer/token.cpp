#include "token.h"
#include <stddef.h>


Token::Token(Kind k, const std::string & t, const Range & r) : kind(k), text(t), range(r)
{
	next = NULL;
}

Token::~Token()
{
	if (next)
		delete next;
}



Token::operator std::string ()
{
	return text;
}
