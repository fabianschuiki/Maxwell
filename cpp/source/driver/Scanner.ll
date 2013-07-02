/* Copyright © 2013 Fabian Schuiki */

%{
#include <string>
#include "Scanner.hpp"

#define storeToken yylval->string = new std::string(yytext, yyleng)

/* Add local typedefs for the parser's tokens for our convenience. */
typedef example::Parser::token token;
typedef example::Parser::token_type token_type;

/* Make yyterminate return a special token instead of 0. */
#define yyterminate() return token::END;

/* Disable unistd.h which is not available under Windows. */
#define YY_NO_UNISTD_H
%}

/* Enable the C++ magic. */
%option c++

/* Change the name of the lexer class to "ExampleFlexLexer" */
%option prefix="Example"

/* The manual says "somewhat more optimized", whatever that means. */
%option batch

/* Produce some debug output. Disable this for the release version. */
%option debug

/* Advance the location tracker during lexing. */
%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}


%% /*** Token Regular Expressions ***/

 /* Whenever yylex() is invoked, we step the location tracker forward. */
%{
	// reset location
	yylloc->step();
%}

 /* Ignore whitespaces. */
[ \t\r]+ {
	yylloc->step();
}

 /* Ignore newlines. */
\n {
	yylloc->lines(yyleng);
	yylloc->step();
}

[a-zA-Z_][a-zA-Z0-9_]*  storeToken; return token::IDENTIFIER;
[0-9]+"."[0-9]*         storeToken; return token::REAL;
[0-9]+                  storeToken; return token::INTEGER;

 /* Pass all other characters to Bison. */
. {
	return static_cast<token_type>(*yytext);
}


%% /*** Additional Code ***/

/* Wrapper class around the lexer created by Flex which makes the interface look similar to the parser. */
namespace example {

Scanner::Scanner(std::istream* in, std::ostream* out) : ExampleFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

}

#ifdef yylex
#undef yylex
#endif

/**
 * This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead.
 */
int ExampleFlexLexer::yylex()
{
	std::cerr << "in ExampleFlexLexer::yylex() !" << std::endl;
	return 0;
}

/**
 * When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller.
 */
int ExampleFlexLexer::yywrap()
{
	return 1;
}