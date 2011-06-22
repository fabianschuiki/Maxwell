#pragma once
#include <string>
#include "location.h"


class Token {
public:
	const enum Kind {
		kInvalidToken = 0,
		kStringToken,
		kIdentifierToken,
		kSymbolToken,
		kNumberToken
	} kind;
	const std::string text;
	const Range range;
	
	Token * next;
	
	Token(Kind k, const std::string & t, const Range & r);
	~Token();
	
	operator std::string ();
};
