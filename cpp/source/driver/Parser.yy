/* Copyright © 2013 Fabian Schuiki */

%{
#include <iostream>
#include <string>
#include <vector>
#include <ast/ast.hpp>
#include <boost/smart_ptr.hpp>

using namespace ast;
using boost::shared_ptr;
typedef std::vector<shared_ptr<Node> > Nodes;
%}

/* Require Bison 2.3 */
%require "2.3"

/* Produce debug output. Disable this for the release version. */
%debug

/* Use the modern C++ skeleton file. */
%skeleton "lalr1.cc"
%name-prefix="example" /* namespace the parser will be enclosed in */
%define "parser_class_name" "Parser" /* class name of the parser */

/* Keep track of the current position within the input. */
%locations
%initial-action {
	// initialize the location object
	@$.begin.filename = @$.end.filename = &driver.streamname;
};

/* Pass the driver by reference into the parser and the lexer. */
%parse-param { class Driver& driver }

/* Produce some verbose error messages. */
%error-verbose


/*** BEGIN GRAMMAR TOKENS ***/

%union {
    Node *node;
    std::string *string;
    Nodes *nodes;
    int token;
    int symbol;
}

%type <node> func_decl func_arg func_arg_tuple
%type <nodes> func_args

%token <string> IDENTIFIER "identifier"
%token <string> REAL "real number constant"
%token <string> INTEGER "integer number constant"
%token <string> STRING_LITERAL "string constant"
%token <symbol> SYMBOL "symbol"
%token END 0 "end of input"

%token FUNC "func keyword"
%token LPAREN "opening paranthesis ("
%token RPAREN "closing paranthesis )"
%token LBRACE "opening braces {"
%token RBRACE "closing braces }"
%token LBRACK "opening bracket ["
%token RBRACK "closing bracket ]"
%token PIPE "vertical pipe |"
%token DOT "."
%token COMMA ","
%token COLON ":"
%token SEMICOLON ";"
%token RIGHTARROW "right arrow ->"

%left "+" "-"
%left "*" "/"

%destructor { delete $$; } IDENTIFIER REAL INTEGER STRING_LITERAL

%start root

/*** END GRAMMAR TOKENS ***/

/* Add the glue code require to hook up the Bison parser to the Flex lexer class. */
%{
#include "Driver.hpp"
#include "Scanner.hpp"

/* This connects the Bison parser to the Flex scanner. */
#undef yylex
#define yylex driver.lexer->lex

using std::cout;
using std::endl;
%}


%% /*** Grammar Rules ***/

root : root_stmts
     ;

root_stmts : root_stmts root_stmt
           | root_stmt
           ;

root_stmt : func_decl
          ;

func_decl : FUNC IDENTIFIER body {
              FunctionDefinition* d = new FunctionDefinition;
              d->setName(*$2); delete $2;
              $$ = d;
            }
          | FUNC IDENTIFIER func_arg_tuple body {
              FunctionDefinition *d = new FunctionDefinition;
              d->setName(*$2); delete $2;
              d->setIn(shared_ptr<Node>($3));
              $$ = d;
            }
          | FUNC IDENTIFIER RIGHTARROW func_arg_tuple body {
              FunctionDefinition *d = new FunctionDefinition;
              d->setName(*$2); delete $2;
              d->setOut(shared_ptr<Node>($4));
              $$ = d;
            }
          | FUNC IDENTIFIER func_arg_tuple RIGHTARROW func_arg_tuple body {
              FunctionDefinition *d = new FunctionDefinition;
              d->setName(*$2); delete $2;
              d->setIn(shared_ptr<Node>($3));
              d->setOut(shared_ptr<Node>($5));
              $$ = d;
             }
          ;

func_arg_tuple  : LPAREN RPAREN { $$ = NULL; }
                | func_arg {
                    FuncArgTuple *t = new FuncArgTuple;
                    Nodes args(1);
                    args[0] = shared_ptr<Node>($1);
                    t->setArgs(args);
                    $$ = t;
                  }
                | LPAREN func_args RPAREN {
                    FuncArgTuple *t = new FuncArgTuple;
                    t->setArgs(*$2);
                    $$ = t;
                    delete $2;
                  }
                ;

func_args : func_arg {
              $$ = new Nodes;
              $$->push_back(shared_ptr<Node>($1));
            }
          | func_args COMMA func_arg {
              $1->push_back(shared_ptr<Node>($3));
            }
          ;

func_arg  : IDENTIFIER {
              FuncArg *a = new FuncArg;
              a->setName(*$1);
              $$ = a;
              delete $1;
            }
          | IDENTIFIER COLON type_expr { cout << "function argument " << *$1 << endl; }
          ;

type_expr : union_type_expr
          ;

nonunion_type_expr : IDENTIFIER { cout << "type " << *$1 << " found" << endl; }
                   | LPAREN type_tuple_args RPAREN { cout << "type tuple" << endl; }
                   ;

union_type_expr : union_type_expr PIPE nonunion_type_expr { cout << "union type" << endl; }
                | nonunion_type_expr
                ;

type_tuple_args : type_tuple_args COMMA type_tuple_arg
                | type_tuple_arg
                ;

type_tuple_arg : type_expr { cout << "type tuple argument" << endl; }
               ;

body : LBRACE RBRACE { cout << "empty body" << endl; }
     | LBRACE root_stmts RBRACE { cout << "filled body" << endl; }
     ;


%% /*** Additional Code ***/

void example::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}