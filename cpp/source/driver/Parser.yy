/* Copyright © 2013 Fabian Schuiki */

%{
#include <iostream>
#include <string>
#include <vector>
#include <ast/nodes/ast.hpp>
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
%name-prefix="driver" /* namespace the parser will be enclosed in */
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
    VarDefExpr *varDefExpr;
    int token;
    int symbol;
}

%type <node> func_decl func_arg func_arg_tuple body stmt expr type_expr union_type_expr nonunion_type_expr
%type <nodes> func_args stmts union_type_exprs
%type <varDefExpr> var_expr

%token <string> IDENTIFIER "identifier"
%token <string> REAL "real number constant"
%token <string> INTEGER "integer number constant"
%token <string> STRING_LITERAL "string constant"
%token <symbol> SYMBOL "symbol"
%token END 0 "end of input"

%token FUNC "func keyword"
%token VAR "var keyword"

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
%token ASSIGN "assignment operator ="

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

root_stmt : func_decl {
              driver.add(shared_ptr<Node>($1));
            }
          ;

func_decl : FUNC IDENTIFIER body {
              FuncDef* d = new FuncDef;
              d->setName(*$2); delete $2;
              d->setBody(shared_ptr<Node>($3));
              $$ = d;
            }
          | FUNC IDENTIFIER func_arg_tuple body {
              FuncDef *d = new FuncDef;
              d->setName(*$2); delete $2;
              d->setIn(shared_ptr<Node>($3));
              d->setBody(shared_ptr<Node>($4));
              $$ = d;
            }
          | FUNC IDENTIFIER RIGHTARROW func_arg_tuple body {
              FuncDef *d = new FuncDef;
              d->setName(*$2); delete $2;
              d->setOut(shared_ptr<Node>($4));
              d->setBody(shared_ptr<Node>($5));
              $$ = d;
            }
          | FUNC IDENTIFIER func_arg_tuple RIGHTARROW func_arg_tuple body {
              FuncDef *d = new FuncDef;
              d->setName(*$2); delete $2;
              d->setIn(shared_ptr<Node>($3));
              d->setOut(shared_ptr<Node>($5));
              d->setBody(shared_ptr<Node>($6));
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
          | IDENTIFIER type_expr {
              FuncArg *a = new FuncArg;
              a->setName(*$1);
              a->setType(shared_ptr<Node>($2));
              $$ = a;
              delete $1;
            }
          ;

type_expr : union_type_expr
          | nonunion_type_expr
          ;

nonunion_type_expr  : IDENTIFIER {
                        NamedType *n = new NamedType;
                        n->setName(*$1);
                        $$ = n;
                        delete $1;
                      }
                    ;

union_type_expr : union_type_exprs {
                    UnionType *t = new UnionType;
                    t->setTypes(*$1);
                    $$ = t;
                    delete $1;
                  }
                ;

union_type_exprs  : nonunion_type_expr PIPE nonunion_type_expr {
                      $$ = new Nodes;
                      $$->push_back(shared_ptr<Node>($1));
                      $$->push_back(shared_ptr<Node>($3));
                    }
                  | union_type_exprs PIPE nonunion_type_expr {
                      $1->push_back(shared_ptr<Node>($3));
                    }
                  ;

body  : LBRACE RBRACE {
          FuncBody *b = new FuncBody;
          $$ = b;
        }
      | LBRACE stmts RBRACE {
          FuncBody *b = new FuncBody;
          b->setStmts(*$2);
          $$ = b;
          delete $2;
        }
      ;

stmts : stmt {
          $$ = new Nodes;
          $$->push_back(shared_ptr<Node>($1));
        }
      | stmts stmt {
          $1->push_back(shared_ptr<Node>($2));
        }
      ;

stmt  : expr SEMICOLON {
          ExprStmt *s = new ExprStmt;
          s->setExpr(shared_ptr<Node>($1));
          $$ = s;
        }
      ;

expr  : IDENTIFIER {
          IdentifierExpr *i = new IdentifierExpr;
          i->setName(*$1);
          $$ = i;
          delete $1;
        }
      | var_expr { $$ = $<node>1; }
      | var_expr ASSIGN expr {
          $1->setInitialExpr(shared_ptr<Node>($3));
        }
      ;

var_expr  : VAR IDENTIFIER type_expr {
              VarDefExpr *v = new VarDefExpr;
              v->setName(*$2);
              v->setType(shared_ptr<Node>($3));
              $$ = v;
              delete $2;
            }
          | VAR IDENTIFIER {
              VarDefExpr *v = new VarDefExpr;
              v->setName(*$2);
              $$ = v;
              delete $2;
            }
          ;


%% /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}