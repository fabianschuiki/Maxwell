%{
#include <stdio.h>
#include <string>
#include <vector>
%}



/*** Bison Declarations ***/

/* Write a header file containing the definitions. */
%defines

/* Use the C++ skeleton. */
%skeleton "lalr1.cc"

/* Parser namespace and class identifier. */
%define "namespace" "Maxwell"
%define "parser_class_name" "Parser"

/* keep track of the current position within the input */
%locations
%initial-action {
	//Initialize the location object.
	@$.begin.filename = @$.end.filename = &driver.streamName;
};

/* Pass the driver by reference to the parser and scanner. This provides a nice interface that does
 * not rely on global variables. */
%parse-param { class Driver & driver }

/* verbose error messages */
%error-verbose

/* specify the initial node */
%start root



/*** Tokens ***/

/* Represent the different ways to access the AST node values. */
%union {
	std::string * string;
	int token;
}

/* Define the tokens. */
%token				END			0	"end of file"
%token				EOL				"end of line"
%token <string>		IDENTIFIER

/* Symbols. */
%token <token>		LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK
%token <token>		CEQ CNE CLT CGT
%token <token>		DOT COMMA COLON SEMICOLON
%token <token>		EQUAL

/* Keywords. */
%token <token>		CLASS PROPERTY

%destructor { delete $$; } IDENTIFIER



/* Connect the bison parser to the scanner object in the driver. */
%{
#include "driver.h"
#include "scanner.h"
#undef yylex
#define yylex driver.scanner->lex
%}



/*** Grammar Rules ***/
%%

root		: statements
			;

statements	: statement
			| statements statement
			;

statement	: class_decl
			| property_decl SEMICOLON
			| var_decl SEMICOLON
			;

block		: LBRACE statements RBRACE
			| LBRACE RBRACE
			;
			
ident		: IDENTIFIER
			;
idents		: ident
			| idents COMMA ident
			;

class_decl	: CLASS ident block
			| CLASS ident COLON class_inheritage block
			;

class_inheritage	: ident
					| ident CLT idents CGT
					;

property_decl	: PROPERTY var_decl
				;

var_decl	: ident ident
			| ident ident EQUAL expr;
			;

expr		: ident
			| LPAREN expr RPAREN

%%



/*** Additional Code ***/
using namespace Maxwell;

/* Capture errors that occur in the parser and pass them onto the driver. */
void Parser::error(const Parser::location_type & l, const std::string & m)
{
	driver.error(l, m);
}
