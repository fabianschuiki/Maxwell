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
    FuncDef *funcDef;
    int token;
    int symbol;
}

%type <node> func_decl func_arg type_decl body stmt expr call_arg
%type <node> primary_expr postfix_expr prefix_expr multiplicative_expr additive_expr relational_expr assignment_expr
%type <node> typeexpr union_typeexpr nonunion_typeexpr tuple_typeexpr tuple_typeexpr_arg
%type <nodes> func_args_tuple func_args stmts union_typeexprs tuple_typeexpr_args call_args
%type <varDefExpr> var_expr
%type <string> any_operator
%type <funcDef> func_decl_name

%token <string> IDENTIFIER "identifier"
%token <string> REAL "real number constant"
%token <string> INTEGER "integer number constant"
%token <string> STRING_LITERAL "string constant"
%token <string> MULTIPLICATIVE_OPERATOR ADDITIVE_OPERATOR RELATIONAL_OPERATOR OPERATOR
%token <symbol> SYMBOL "symbol"
%token END 0 "end of input"

%token FUNC "func keyword"
%token VAR "var keyword"
%token TYPE "type keyword"
%token UNARY "unary keyword"

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

%destructor { delete $$; } IDENTIFIER REAL INTEGER STRING_LITERAL OPERATOR

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
          | type_decl {
              driver.add(shared_ptr<Node>($1));
            }
          ;

func_decl : func_decl_name body {
              $1->setBody(shared_ptr<Node>($2));
            }
          | func_decl_name func_args_tuple body {
              $1->setIn(*$2);
              $1->setBody(shared_ptr<Node>($3));
              delete $2;
            }
          | func_decl_name RIGHTARROW func_args_tuple body {
              $1->setOut(*$3);
              $1->setBody(shared_ptr<Node>($4));
              delete $3;
            }
          | func_decl_name func_args_tuple RIGHTARROW func_args_tuple body {
              $1->setIn(*$2);
              $1->setOut(*$4);
              $1->setBody(shared_ptr<Node>($5));
              delete $2;
              delete $4;
             }
          ;

func_decl_name
  : FUNC IDENTIFIER {
      FuncDef* d = new FuncDef;
      d->setName(*$2); delete $2;
      $$ = d;
    }
  | FUNC any_operator {
      FuncDef* d = new FuncDef;
      d->setName(*$2); delete $2;
      $$ = d;
    }
  | FUNC UNARY any_operator {
      FuncDef* d = new FuncDef;
      d->setName("_" + *$3); delete $3;
      $$ = d;
    }
  ;

func_args_tuple
  : LPAREN RPAREN { $$ = new Nodes; }
  | func_arg {
      $$ = new Nodes;
      $$->push_back(shared_ptr<Node>($1));
    }
  | LPAREN func_args RPAREN {
      $$ = $2;
    }
  ;

func_args
  : func_arg {
      $$ = new Nodes;
      $$->push_back(shared_ptr<Node>($1));
    }
  | func_args COMMA func_arg {
      $1->push_back(shared_ptr<Node>($3));
    }
  ;

func_arg
  : IDENTIFIER {
      FuncArg *a = new FuncArg;
      a->setName(*$1);
      $$ = a;
      delete $1;
    }
  | IDENTIFIER typeexpr {
      FuncArg *a = new FuncArg;
      a->setName(*$1);
      a->setType(shared_ptr<Node>($2));
      $$ = a;
      delete $1;
    }
  ;

type_decl : TYPE IDENTIFIER {
              TypeDef *t = new TypeDef;
              t->setName(*$2);
              $$ = t;
              delete $2;
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


/* EXPRESSIONS */

primary_expr
  : IDENTIFIER {
      IdentifierExpr *i = new IdentifierExpr;
      i->setName(*$1);
      $$ = i;
      delete $1;
    }
  | LPAREN expr RPAREN { $$ = $2; }
  ;

postfix_expr
  : primary_expr
  | postfix_expr OPERATOR {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(true);
      u->setOperatorName(*$2);
      u->setExpr(shared_ptr<Node>($1));
      $$ = u;
      delete $2;
    }
  | postfix_expr DOT IDENTIFIER LPAREN RPAREN {
      CallExpr *c = new CallExpr;
      c->setName(*$3);
      c->setContext(shared_ptr<Node>($1));
      $$ = c;
      delete $3;
    }
  | postfix_expr DOT IDENTIFIER LPAREN call_args RPAREN {
      CallExpr *c = new CallExpr;
      c->setName(*$3);
      c->setCallArgs(*$5);
      c->setContext(shared_ptr<Node>($1));
      $$ = c;
      delete $3;
      delete $5;
    }
  | postfix_expr DOT IDENTIFIER {
      MemberAccessExpr *m = new MemberAccessExpr;
      m->setExpr(shared_ptr<Node>($1));
      m->setName(*$3);
      $$ = m;
      delete $3;
    }
  | IDENTIFIER LPAREN RPAREN {
      CallExpr *c = new CallExpr;
      c->setName(*$1);
      $$ = c;
      delete $1;
    }
  | IDENTIFIER LPAREN call_args RPAREN {
      CallExpr *c = new CallExpr;
      c->setName(*$1);
      c->setCallArgs(*$3);
      $$ = c;
      delete $1;
      delete $3;
    }
  ;

call_args
  : call_arg {
      $$ = new Nodes;
      $$->push_back(shared_ptr<Node>($1));
    }
  | call_args COMMA call_arg {
      $1->push_back(shared_ptr<Node>($3));
    }
  ;

call_arg
  : IDENTIFIER COLON expr {
      CallExprArg *a = new CallExprArg;
      a->setName(*$1);
      a->setExpr(shared_ptr<Node>($3));
      $$ = a;
      delete $1;
    }
  | expr {
      CallExprArg *a = new CallExprArg;
      a->setExpr(shared_ptr<Node>($1));
      $$ = a;
    }
  ;

prefix_expr
  : postfix_expr
  | any_operator prefix_expr {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(false);
      u->setOperatorName(*$1);
      u->setExpr(shared_ptr<Node>($2));
      $$ = u;
      delete $1;
    }
  ;
any_operator: MULTIPLICATIVE_OPERATOR | ADDITIVE_OPERATOR | RELATIONAL_OPERATOR | OPERATOR;

multiplicative_expr
  : prefix_expr
  | multiplicative_expr MULTIPLICATIVE_OPERATOR prefix_expr {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*$2);
      e->setLhs(shared_ptr<Node>($1));
      e->setRhs(shared_ptr<Node>($3));
      $$ = e;
      delete $2;
    }
  ;

additive_expr
  : multiplicative_expr
  | additive_expr ADDITIVE_OPERATOR multiplicative_expr {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*$2);
      e->setLhs(shared_ptr<Node>($1));
      e->setRhs(shared_ptr<Node>($3));
      $$ = e;
      delete $2;
    }
  ;

relational_expr
  : additive_expr
  | relational_expr RELATIONAL_OPERATOR additive_expr {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*$2);
      e->setLhs(shared_ptr<Node>($1));
      e->setRhs(shared_ptr<Node>($3));
      $$ = e;
      delete $2;
    }
  ;

assignment_expr
  : relational_expr
  | assignment_expr ASSIGN relational_expr {
      AssignmentExpr *e = new AssignmentExpr;
      e->setLhs(shared_ptr<Node>($1));
      e->setRhs(shared_ptr<Node>($3));
      $$ = e;
    }
  ;

expr  : assignment_expr
      | var_expr { $$ = $<node>1; }
      | var_expr ASSIGN assignment_expr {
          $1->setInitialExpr(shared_ptr<Node>($3));
        }
      ;

var_expr  : VAR IDENTIFIER typeexpr {
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

/* TYPE EXPRESSIONS */
typeexpr
  : nonunion_typeexpr
  | union_typeexpr
  ;

nonunion_typeexpr
  : IDENTIFIER {
      NamedTypeExpr *n = new NamedTypeExpr;
      n->setName(*$1);
      $$ = n;
      delete $1;
    }
  | tuple_typeexpr
  ;

union_typeexpr
  : union_typeexprs {
      UnionTypeExpr *t = new UnionTypeExpr;
      t->setTypes(*$1);
      $$ = t;
      delete $1;
    }
  ;

union_typeexprs
  : nonunion_typeexpr PIPE nonunion_typeexpr {
      $$ = new Nodes;
      $$->push_back(shared_ptr<Node>($1));
      $$->push_back(shared_ptr<Node>($3));
    }
  | union_typeexprs PIPE nonunion_typeexpr {
      $1->push_back(shared_ptr<Node>($3));
    }
  ;


tuple_typeexpr
  : LPAREN tuple_typeexpr_args RPAREN {
      TupleTypeExpr *t = new TupleTypeExpr;
      t->setArgs(*$2);
      $$ = t;
      delete $2;
    }
  ;

tuple_typeexpr_args
  : tuple_typeexpr_arg COMMA tuple_typeexpr_arg {
      $$ = new Nodes;
      $$->push_back(shared_ptr<Node>($1));
      $$->push_back(shared_ptr<Node>($3));
    }
  | tuple_typeexpr_args COMMA tuple_typeexpr_arg {
      $1->push_back(shared_ptr<Node>($3));
    }
  ;

tuple_typeexpr_arg
  : typeexpr {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setExpr(shared_ptr<Node>($1));
      $$ = t;
    }
  | IDENTIFIER COLON typeexpr {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setName(*$1);
      t->setExpr(shared_ptr<Node>($3));
      $$ = t;
      delete $1;
    }
  ;

%% /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}