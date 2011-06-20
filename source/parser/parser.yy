%{
#include <stdio.h>
#include <string>
#include <vector>

#include "../../node.h"
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
	Node * node;
	
	Statement * stmt;
	Expression * expr;
	
	Identifier * ident;
	Identifiers * idents;
	
	Block * block;
	
	ClassDefinition * class_decl;
	
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


/* Define the types of the nodes of our nonterminal symbols. */
%type <stmt>		root_stmt class_stmt
%type <ident>		ident
%type <idents>		idents
%type <block>		root_stmts class_stmts
%type <class_decl>	class_decl

/*%destructor { delete $$; } IDENTIFIER*/



/* Connect the bison parser to the scanner object in the driver. */
%{
#include "../../driver.h"
#include "../../scanner/scanner.h"
#undef yylex
#define yylex driver.scanner->lex
%}



/*** Grammar Rules ***/
%%

 /* The root section of the file. May contain any number of root statements. */
root
 : root_stmts { driver.programBlock = $1; }
 ;
root_stmts
 : root_stmt { $$ = new Block(); $$->statements.push_back($1); }
 | root_stmts root_stmt { $1->statements.push_back($2); }
 ;

/* A root statement may be a class or function declaration, as well as import statements. */
root_stmt
 : class_decl SEMICOLON
 | class_def
// | func_decl
 ;

/* Identifier and comma-separated list of identifiers. */
ident
 : IDENTIFIER { $$ = new Identifier(*$1); delete $1; }
 ;
idents
 : ident { $$ = new Identifiers(); $$->push_back($1); }
 | idents COMMA ident { $1->push_back($3); }
 ;



/* A class declaration consists of the keyword 'class' followed by the desired class name.
 * Optionally a : and the superclass's name may be appended to inherit from that. Implemented inter-
 * faces may also be added in triangular brackets <>. */
class_decl
 : CLASS ident {
	$$ = new ClassDefinition();
	$$->name = *$2;
 }
 | CLASS ident CLT idents CGT {
	$$ = new ClassDefinition();
	$$->name = *$2;
	$$->interfaces = *$4;
 }
 | CLASS ident COLON ident {
	$$ = new ClassDefinition();
	$$->name = *$2;
	$$->super = *$4;
 }
 | CLASS ident COLON ident CLT idents CGT{
	$$ = new ClassDefinition();
	$$->name = *$2;
	$$->super = *$4;
	$$->interfaces = *$6;
 }
 ;

 /* A class definition consists of a class declaration followed by a bunch of class statements en-
  * closed in braces. */
class_def
 : class_decl LBRACE RBRACE
 | class_decl LBRACE class_stmts RBRACE
 ;

/* Class statements. */
class_stmts
 : class_stmt
 | class_stmts class_stmt
 ;
class_stmt
 :
 ;

%%



/*** Additional Code ***/
using namespace Maxwell;

/* Capture errors that occur in the parser and pass them onto the driver. */
void Parser::error(const Parser::location_type & l, const std::string & m)
{
	driver.error(l, m);
}
