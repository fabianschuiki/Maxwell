#include "token.h"
#include <stddef.h>


Token::Token(Kind k) : kind(k)
{
	next = NULL;
}

Token::~Token()
{
	if (next)
		delete next;
}
