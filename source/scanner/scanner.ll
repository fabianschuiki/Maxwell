%{
#include <string>
#include "../scanner.h"

//Convenience typedef of the parser's token type.
typedef Maxwell::Parser::token      token;
typedef Maxwell::Parser::token_type token_type;

//Since yylex returns a token_type, we have to override the default return (which is 0).
#define yyterminate() return token::END

//Fix stuff for the crappier OSes out there.
#define YY_NO_UNISTD_H
%}


/*** Flex Declarations and Options ***/

/* enable C++ scanner class generation */
%option c++

/* change the name of the scanner class to MaxwellFlexLexer */
%option prefix = "Maxwell"

/* automatically keep track of locations. */
%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}


/*** Regular Expressions ***/
%x COMMENT
%x STRING
%%

 /* code to place at the beginning of yylex() */
%{
	//reset location
	yylloc->step();
%}


 /* skip over whitespaces */
<*>[ \t\r]+ {
	yylloc->step();
}

 /* skip over end-of-lines */
<*>\n {
	yylloc->lines(yyleng);
	yylloc->step();
}

 /* ignore single-line and multi-line comments */
<INITIAL>\/\/[^\n]* {
	yylloc->step();
}
<INITIAL>"/*" {
	yylloc->step();
	BEGIN(COMMENT);
}
<COMMENT>"*/" {
	yylloc->step();
	BEGIN(INITIAL);
}
<COMMENT>([^\*\n]|\*[^\/\n])* {
	yylloc->step();
}

 /* Symbols */
"("		return token::LPAREN;
")"		return token::RPAREN;
"{"		return token::LBRACE;
"}"		return token::RBRACE;
"["		return token::LBRACK;
"]"		return token::RBRACK;

"=="	return token::CEQ;
"!="	return token::CNE;
"≠"		return token::CNE;
"<"		return token::CLT;
">"		return token::CGT;
"<="	return token::CLE;
">="	return token::CGE;

"."		return token::DOT;
","		return token::COMMA;
":"		return token::COLON;
";"		return token::SEMICOLON;

"="		return token::EQUAL;

"+"		return token::PLUS;
"-"		return token::MINUS;
"*"		return token::ASTERISK;
"/"		return token::SLASH;

 /* Keywords */
"class"		return token::CLASS;
"property"	return token::PROPERTY;

 /* Identifiers */
 /*[a-zA-Z_][a-zA-Z0-9_]* {*/
[^ \t\n(){}\[\]=≠!<>.,:;+\-*/]+ {
	yylval->string = new std::string(yytext, yyleng);
	return token::IDENTIFIER;
}

%%


/*** Additional Code ***/
using namespace Maxwell;

Scanner::Scanner(std::istream * in, std::ostream * out) : MaxwellFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

/* This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int MaxwellFlexLexer::yylex()
{
	std::cerr << "in MaywellFlexLexer::yylex()!" << std::endl;
	return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int MaxwellFlexLexer::yywrap()
{
	return 1;
}
