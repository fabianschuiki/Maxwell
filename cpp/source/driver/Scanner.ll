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

%x IN_COMMENT

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
<INITIAL,IN_COMMENT>\n {
    yylloc->lines(yyleng);
    yylloc->step();
}

 /* Eat comments. */
"//"[^\n]*  ; /* we might want to keep track of the comments, for automated documentation */
<INITIAL>{
    "/*"      BEGIN(IN_COMMENT);
}
<IN_COMMENT>{
    "*/"      BEGIN(INITIAL);
    [^*\n]+   // eat comment in chunks
    "*"       // eat the lone star
}

 /* Eat strings. */
"\""(\\.|[^\\"\""])*"\""  storeToken; return token::STRING_LITERAL;

 /* Keywords */
"func"  return token::FUNC;

[a-zA-Z_][a-zA-Z0-9_]*    storeToken; return token::IDENTIFIER;
[0-9]+"."[0-9]*           storeToken; return token::REAL;
[0-9]+                    storeToken; return token::INTEGER;

"("  return token::LPAREN;
")"  return token::RPAREN;
"{"  return token::LBRACE;
"}"  return token::RBRACE;
"["  return token::LBRACK;
"]"  return token::RBRACK;

"|"  return token::PIPE;

"."  return token::DOT;
","  return token::COMMA;
":"  return token::COLON;
";"  return token::SEMICOLON;

"->" return token::RIGHTARROW;

 /* All other characters are interpreted as a symbol. */
. {
    yylval->symbol = yytext[0]; return token::SYMBOL;
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