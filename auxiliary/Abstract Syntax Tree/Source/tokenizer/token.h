#pragma once


class Token {
public:
	const enum Kind {
		CommentToken,
		StringToken,
		IdentifierToken
	} kind;
	
	Token * next;
	
	Token(Kind k);
	~Token();
};
