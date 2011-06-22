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
	Expressions * exprs;
	
	Identifier * ident;
	Identifiers * idents;
	
	Block * block;
	
	ClassDefinition * class_def;
	FunctionDefinition * func_def;
	FunctionArgument * func_arg;
	FunctionArguments * func_args;
	VariableDefinition * var_def;
	
	FunctionCall * func_call;
	FunctionCallArgument * func_call_arg;
	FunctionCallArguments * func_call_args;
	
	std::string * string;
	int token;
}

/* Define the tokens. */
%token				END			0	"end of file"
%token				EOL				"end of line"
%token <string>		IDENTIFIER FLOAT INTEGER STRING

/* Symbols. */
%token <token>		LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK
%token <token>		CEQ CNE CLT CGT CLE CGE
%token <token>		DOT COMMA COLON SEMICOLON
%token <token>		EQUAL PLUS MINUS ASTERISK SLASH

/* Keywords. */
%token <token>		CLASS PROPERTY


/* Define the types of the nodes of our nonterminal symbols. */
%type <stmt>		root_stmt class_stmt func_stmt
%type <expr>		expr type numeric string
%type <exprs>		exprs
%type <ident>		ident
%type <idents>		idents
%type <block>		root_stmts class_stmts func_stmts
%type <class_def>	class_decl class_def
%type <func_def>	func_decl func_def func_rest
%type <func_arg>	func_arg
%type <func_args>	func_args func_sel
%type <var_def>		func_arg_var var_decl var_def

%type <func_call>		func_call
%type <func_call_arg>	func_call_arg
%type <func_call_args>	func_call_args

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
 | var_def SEMICOLON { $$ = $1; }
 ;



/*** Functions ***/

/* A function declaration consists of a return type followed by a list of named arguments. */
func_decl
 : PLUS func_rest { $$ = $2; $2->shared = true; }
 | MINUS func_rest { $$ = $2; $2->shared = false; }
 ;
func_rest
 : type func_sel {
	$$ = new FunctionDefinition();
	$$->returnType = $1;
	$$->arguments = $2;
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
 : ident COLON LPAREN func_arg_var RPAREN {
	$$ = new FunctionArgument();
	$$->name = $1;
	$$->argument = $4;
 }
 ;
func_arg_var
 : type	{ $$ = new VariableDefinition(); $$->type = $1; }
 | type ident { $$ = new VariableDefinition(); $$->type = $1; $$->name = $2; }
 ;

/* A function definition consists of a function declaration followed by a bunch of function
 * statements enclosed in braces. */
func_def
 : func_decl LBRACE func_stmts RBRACE { $$ = $1; $$->statements = $3; }
 ;
func_stmts
 : { $$ = new Block(); }
 | func_stmt { $$ = new Block(); $$->statements.push_back($1); }
 | func_stmts func_stmt { $1->statements.push_back($2); }
 ;
func_stmt
 : expr SEMICOLON
 | var_def SEMICOLON
 ;



/*** Variables ***/

/* A variable declaration consists of the variable's type and name, as well as an optional initial
 * value. */
var_decl
 : type ident { $$ = new VariableDefinition(); $$->type = $1; $$->name = $2; }
 ;
var_def
 : var_decl { $$ = $1; }
 | var_decl EQUAL expr { $$ = $1; $$->initial = $3; }
 ;



/*** Types ***/

/* A type semantically is just an expression. The expression needs to be checked whether it
 * resolves to a type when processing the AST. */
type
 : expr
 ;



/*** Expressions ***/

/* An expression can be many things. See the list for details. */
expr
 : ident { $$ = $1; }
 | numeric { $$ = $1; }
 | string { $$ = $1; }
 
   //Groups and tuples
 | LPAREN expr RPAREN { $$ = $2; }
 | LPAREN exprs RPAREN { $$ = new Tuple(); ((Tuple *)$$)->expressions = $2; }
   
   //Operators
 | expr bin_operator expr
 | expr assignment expr
   
   //Members and calls
 | expr DOT ident {
	$$ = new MemberAccess();
	((MemberAccess *)$$)->subject = $1;
	((MemberAccess *)$$)->member = $3;
 }
 | func_call
 ;
exprs
 : expr COMMA expr { $$ = new Expressions(); $$->push_back($1); $$->push_back($3); }
 | exprs COMMA expr { $$ = $1; $1->push_back($3); }
 ;

/* A binary operator is any operator that takes a left and right-hand side expression and returns
 * the result. */
bin_operator
 : CEQ | CNE | CLT | CGE | CLE | CGT
 | PLUS | MINUS | ASTERISK | SLASH
 ;

/* An assignment operator is any operator containing an =. */
assignment
 : EQUAL
 ;

/* Numeric expressiosn are either an INTEGER or FLOAT. */
numeric
 : INTEGER	{ $$ = new Numeric(*$1); delete $1; }
 | FLOAT	{ $$ = new Numeric(*$1); delete $1; }
 ;

/* Strings are delimited by ". */
string
 : STRING { $$ = new String(*$1); delete $1; }
 ;

/* A function call consists of an expression a colon and the call arguments. */
func_call
 : expr COLON ident {
	FunctionCallArgument * arg = new FunctionCallArgument();
	arg->name = $3;
	
	FunctionCallArguments * args = new FunctionCallArguments();
	args->push_back(arg);
	
	$$ = new FunctionCall();
	$$->receiver = $1;
	$$->arguments = args;
 }
 | expr COLON LPAREN func_call_args RPAREN {
	$$ = new FunctionCall();
	$$->receiver = $1;
	$$->arguments = $4;
 }
 ;
func_call_args
 : func_call_arg { $$ = new FunctionCallArguments(); $$->push_back($1); }
 | func_call_args func_call_arg { $$ = $1; $$->push_back($2); }
 ;
func_call_arg
 : ident COLON expr {
	$$ = new FunctionCallArgument();
	$$->name = $1;
	$$->argument = $3;
 }
 ;

%%



/*** Additional Code ***/
using namespace Maxwell;

/* Capture errors that occur in the parser and pass them onto the driver. */
void Parser::error(const Parser::location_type & l, const std::string & m)
{
	driver.error(l, m);
}
