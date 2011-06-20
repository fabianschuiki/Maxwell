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
	
	Block * block;
	
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
%type <ident> ident
%type <block> root_stmts class_stmts
%type <stmt> root_stmt class_stmt class_decl

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
 : class_decl
// | func_decl
 ;

/* Convenience identifier. */
ident
 : IDENTIFIER { $$ = new Identifier(*$1); delete $1; }
 ;



/* A class declaration consists of the keyword 'class' followed by the desired class name.
 * Optionally a : and the superclass's name may be appended to inherit from that. Implemented inter-
 * faces may also be added in triangular brackets <>. */
class_decl
 : CLASS ident class_body { $$ = new ClassDeclaration(*$2); }
 | CLASS ident CLT class_intfs CGT class_body
 | CLASS ident COLON ident class_body { $$ = new ClassDeclaration(*$2, *$4); }
 | CLASS ident COLON ident CLT class_intfs CGT class_body
 ;

/* The class interfaces are a comma-separated list of identifiers. */
class_intfs
 : class_intf
 | class_intfs COMMA class_intf
 ;
class_intf
 : ident
 ;

/* The class body is a bunch of class statements encapsuled in braces. */
class_body
 : LBRACE class_stmts RBRACE
 | LBRACE RBRACE
 ;
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
