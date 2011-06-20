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
	
	ClassDefinition * class_def;
	FunctionDefinition * func_def;
	FunctionArgument * func_arg;
	FunctionArguments * func_args;
	
	Type * type;
	Types * types;
	
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
%token <token>		EQUAL PLUS MINUS ASTERISK SLASH

/* Keywords. */
%token <token>		CLASS PROPERTY


/* Define the types of the nodes of our nonterminal symbols. */
%type <stmt>		root_stmt class_stmt func_stmt
%type <ident>		ident
%type <idents>		idents
%type <block>		root_stmts class_stmts func_stmts
%type <class_def>	class_decl class_def
%type <func_def>	func_decl func_def
%type <func_arg>	func_arg
%type <func_args>	func_args func_sel
%type <type>		type
%type <types>		types

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
 : class_decl SEMICOLON { $$ = $1; }
 | class_def { $$ = $1; }
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



/*** Classes ***/

/* A class declaration consists of the keyword 'class' followed by the desired class name.
 * Optionally a : and the superclass's name may be appended to inherit from that. Implemented inter-
 * faces may also be added in triangular brackets <>. */
class_decl
 : CLASS ident {
	$$ = new ClassDefinition();
	$$->name = $2;
 }
 | CLASS ident CLT idents CGT {
	$$ = new ClassDefinition();
	$$->name = $2;
	$$->interfaces = $4;
 }
 | CLASS ident COLON ident {
	$$ = new ClassDefinition();
	$$->name = $2;
	$$->super = $4;
 }
 | CLASS ident COLON ident CLT idents CGT{
	$$ = new ClassDefinition();
	$$->name = $2;
	$$->super = $4;
	$$->interfaces = $6;
 }
 ;

 /* A class definition consists of a class declaration followed by a bunch of class statements en-
  * closed in braces. */
class_def
 : class_decl LBRACE RBRACE { $$ = $1; }
 | class_decl LBRACE class_stmts RBRACE { $$ = $1; $$->statements = $3; }
 ;

/* Class statements. */
class_stmts
 : class_stmt { $$ = new Block(); $$->statements.push_back($1); }
 | class_stmts class_stmt { $1->statements.push_back($2); }
 ;
class_stmt
 : func_decl SEMICOLON { $$ = $1; }
 | func_def { $$ = $1; }
 ;



/*** Functions ***/

/* A function declaration consists of a return type followed by a list of named arguments. */
func_decl
 : PLUS|MINUS type func_sel {
	$$ = new FunctionDefinition();
	$$->shared = ($1 == token::PLUS);
	$$->returnType = $2;
	$$->arguments = $3;
 }
 ;

/* A function selector is either simply an identifier for a function without any arguments, or a
 * list of parameter names and types. */
func_sel
 : ident {
	FunctionArgument * arg = new FunctionArgument();
	arg->name = $1;
	$$ = new FunctionArguments();
	$$->push_back(arg);
 }
 | func_args { $$ = $1; }
 ;
func_args
 : func_arg { $$ = new FunctionArguments(); $$->push_back($1); }
 | func_args func_arg { $1->push_back($2); }
 ;
func_arg
 : ident COLON LPAREN type /* actually var_decl */ RPAREN {
	$$ = new FunctionArgument();
	$$->name = $1;
	$$->argument = $4;
 }
 ;

/* A function definition consists of a function declaration followed by a bunch of function
 * statements enclosed in braces. */
func_def
 : func_decl LBRACE RBRACE { $$ = $1; }
 | func_decl LBRACE func_stmts RBRACE { $$ = $1; $$->statements = $3; }
 ;
func_stmts
 : func_stmt { $$ = new Block(); $$->statements.push_back($1); }
 | func_stmts func_stmt { $1->statements.push_back($2); }
 ;
func_stmt
 :
 ;



/*** Types ***/
/* A type is a group of code that describes a section of memory. This may be through a simple type,
 * memory structure or a tuple of multiple types. */
type
 : ident {
	$$ = new ConcreteType();
	((ConcreteType *)$$)->name = $1;
 }
 | LPAREN types RPAREN {
	$$ = new TupleType();
	((TupleType *)$$)->types = $2;
 }
 ;
types
 : type { $$ = new Types(); $$->push_back($1); }
 | types COMMA type { $1->push_back($3); }
 ;

%%



/*** Additional Code ***/
using namespace Maxwell;

/* Capture errors that occur in the parser and pass them onto the driver. */
void Parser::error(const Parser::location_type & l, const std::string & m)
{
	driver.error(l, m);
}
