/* Copyright © 2013 Fabian Schuiki */

%{
#include <iostream>
#include <string>
#include <vector>
#include <ast/nodes/ast.hpp>
#include <boost/smart_ptr.hpp>

using namespace ast;
using boost::shared_ptr;
typedef std::vector<NodePtr> Nodes;
%}

/* Require Bison 2.3 */
%require "2.3"

/* Generate a Generalized LR parser. This allows the parser to resolve more
 * convoluted grammar rules that are not parsable with LR(1). See the Bison
 * website at http://www.gnu.org/software/bison/manual/bison.html for more
 * information. */
%glr-parser

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
    TypeDef *typeDef;
    StructureQualifier *structureQualifier;
    RangeQualifier *rangeQualifier;
    int token;
    int symbol;
}

%type <node> func_def func_arg type_def if_expr for_expr expr call_arg

%type <node> primary_expr ifcase_expr ifcase_expr_cond postfix_expr prefix_expr multiplicative_expr additive_expr relational_expr equality_expr and_expr or_expr assignment_expr map_expr_pair body_expr block_expr nonempty_block_expr block_expr_expr macro_expr any_expr func_expr
%type <nodes> expr_list map_expr_pairs ifcase_expr_conds block_expr_exprs

%type <node> typeexpr union_typeexpr nonunion_typeexpr tuple_typeexpr tuple_typeexpr_arg qualified_typeexpr qualified_typeexpr_qualifier specialized_typeexpr
%type <nodes> func_args_tuple func_args union_typeexprs tuple_typeexpr_args call_args qualified_typeexpr_qualifiers specialized_typeexpr_specs

%type <node> structure_qualifier structure_qualifier_stmt interface_qualifier interface_qualifier_stmt native_qualifier range_qualifier
%type <nodes> structure_qualifier_stmts interface_qualifier_stmts

%type <varDefExpr> var_expr
%type <string> any_operator
%type <funcDef> func_def_name func_def_signature
%type <typeDef> type_def_name
%type <structureQualifier> structure_qualifier_decl
%type <rangeQualifier> range_qualifier_decl

%token <string> IDENTIFIER "identifier"
%token <string> NUMBER "number constant"
%token <string> STRING_LITERAL "string constant"
%token <string> MULTIPLICATIVE_OPERATOR ADDITIVE_OPERATOR RELATIONAL_OPERATOR EQUALITY_OPERATOR AND_OPERATOR OR_OPERATOR OPERATOR
%token <symbol> SYMBOL "symbol"
%token END 0 "end of input"

%token FUNC "func keyword"
%token VAR "var keyword"
%token TYPE "type keyword"
%token UNARY "unary keyword"
%token VALUE "value keyword"
%token OBJECT "object keyword"
%token INTERFACE "interface keyword"
%token NATIVE "native keyword"
%token RANGE "range keyword"
%token IF "if keyword"
%token ELSE "else keyword"
%token FOR "for keyword"
%token NIL "nil constant"
%token INCASE "incase keyword"
%token OTHERWISE "otherwise keyword"

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
%token DEFASSIGN "typeless variable :="
%token HASHTAG "#"

%destructor { delete $$; } IDENTIFIER NUMBER STRING_LITERAL MULTIPLICATIVE_OPERATOR ADDITIVE_OPERATOR RELATIONAL_OPERATOR OPERATOR

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

root_stmt : func_def {
              driver.add(NodePtr($1));
            }
          | type_def {
              driver.add(NodePtr($1));
            }
          ;

/* Function Declaration*/
func_def
  : func_def_signature block_expr {
      $1->setBody(NodePtr($2));
      $1->setImplOut(false);
    }
  | func_def_signature ASSIGN body_expr {
      $1->setBody(NodePtr($3));
      $1->setImplOut(true);
    }
  ;

func_def_signature
  : func_def_name
  | func_def_name func_args_tuple {
      $1->setIn(*$2);
      delete $2;
    }
  | func_def_name RIGHTARROW func_args_tuple {
      $1->setOut(*$3);
      delete $3;
    }
  | func_def_name func_args_tuple RIGHTARROW func_args_tuple {
      $1->setIn(*$2);
      $1->setOut(*$4);
      delete $2;
      delete $4;
     }
  ;

func_def_name
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
      $$->push_back(NodePtr($1));
    }
  | LPAREN func_args RPAREN {
      $$ = $2;
    }
  ;

func_args
  : func_arg {
      $$ = new Nodes;
      $$->push_back(NodePtr($1));
    }
  | func_args COMMA func_arg {
      $1->push_back(NodePtr($3));
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
      a->setTypeExpr(NodePtr($2));
      $$ = a;
      delete $1;
    }
  ;

/* Type Declaration */
type_def
  : type_def_name { $$ = $1; }
  | type_def_name typeexpr {
      $1->setType(NodePtr($2));
    }
  ;

type_def_name
  /*: TYPE { $$ = new TypeDef; }
  | TYPE IDENTIFIER {*/
  : TYPE IDENTIFIER {
      TypeDef *t = new TypeDef;
      t->setName(*$2);
      $$ = t;
      delete $2;
    }
  ;

/*
 * ----------------------------------------------------------------------------
 *
 *    EXPRESSIONS
 *
 * ----------------------------------------------------------------------------
 */

primary_expr
  : IDENTIFIER {
      IdentifierExpr *i = new IdentifierExpr;
      i->setName(*$1);
      $$ = i;
      delete $1;
    }
  | LPAREN any_expr RPAREN { $$ = $2; }
  | NUMBER {
     NumberConstExpr *n = new NumberConstExpr;
     n->setValue(*$1);
     $$ = n;
     delete $1;
    }
  | STRING_LITERAL {
      StringConstExpr *s = new StringConstExpr;
      s->setValue(*$1);
      $$ = s;
      delete $1;
    }
  | LBRACK expr_list RBRACK { /* array literals */
      ArrayConstExpr *a = new ArrayConstExpr;
      a->setExprs(*$2);
      $$ = a;
      delete $2;
    }
  | LBRACE expr_list RBRACE { /* set literals */
      SetConstExpr *s = new SetConstExpr;
      s->setExprs(*$2);
      $$ = s;
      delete $2;
    }
  | LBRACE map_expr_pairs RBRACE { /* map literals */
      MapConstExpr *m = new MapConstExpr;
      m->setPairs(*$2);
      $$ = m;
      delete $2;
    }
  | ifcase_expr
  | block_expr
  ;

map_expr_pairs
  : map_expr_pair {
      $$ = new Nodes;
      $$->push_back(NodePtr($1));
    }
  | map_expr_pairs COMMA map_expr_pair {
      $1->push_back(NodePtr($3));
    }
  ;
map_expr_pair
  : primary_expr COLON expr {
      MapConstExprPair *p = new MapConstExprPair;
      p->setKey(NodePtr($1));
      p->setValue(NodePtr($3));
      $$ = p;
    }
  ;

ifcase_expr
  : LBRACE ifcase_expr_conds RBRACE {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*$2);
      $$ = i;
      delete $2;
    }
  | LBRACE ifcase_expr_conds COMMA expr OTHERWISE RBRACE {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*$2);
      i->setOtherwise(NodePtr($4));
      $$ = i;
      delete $2;
    }
  ;
ifcase_expr_conds
  : ifcase_expr_cond {
      $$ = new Nodes;
      $$->push_back(NodePtr($1));
    }
  | ifcase_expr_conds COMMA ifcase_expr_cond {
      $1->push_back(NodePtr($3));
    }
  ;
ifcase_expr_cond
  : expr IF expr {
      IfCaseExprCond *c = new IfCaseExprCond;
      c->setExpr(NodePtr($1));
      c->setCond(NodePtr($3));
      $$ = c;
    }
  ;

if_expr
  : IF LPAREN expr RPAREN body_expr {
      IfExpr *s = new IfExpr;
      s->setCond(NodePtr($3));
      s->setBody(NodePtr($5));
      $$ = s;
    }
  | IF LPAREN expr RPAREN body_expr ELSE body_expr {
      IfExpr *s = new IfExpr;
      s->setCond(NodePtr($3));
      s->setBody(NodePtr($5));
      s->setElseExpr(NodePtr($7));
      $$ = s;
    }
  ;

for_expr
  : FOR LPAREN expr RPAREN body_expr {
      ForExpr *s = new ForExpr;
      s->setCond(NodePtr($3));
      s->setBody(NodePtr($5));
      $$ = s;
    }
  | FOR LPAREN expr SEMICOLON expr SEMICOLON expr RPAREN body_expr {
      ForExpr *s = new ForExpr;
      s->setInit(NodePtr($3));
      s->setCond(NodePtr($5));
      s->setStep(NodePtr($7));
      s->setBody(NodePtr($9));
      $$ = s;
    }
  ;

body_expr
  // : block_expr
  // | expr SEMICOLON
  : primary_expr
  ;

block_expr
  : LBRACE RBRACE {
      BlockExpr *b = new BlockExpr;
      $$ = b;
    }
  | nonempty_block_expr
  ;
nonempty_block_expr
  : LBRACE block_expr_exprs RBRACE {
      BlockExpr *b = new BlockExpr;
      b->setExprs(*$2);
      $$ = b;
      delete $2;
    }
  ;
block_expr_exprs
  : block_expr_expr {
      $$ = new Nodes;
      $$->push_back(NodePtr($1));
    }
  | block_expr_exprs block_expr_expr {
      $1->push_back(NodePtr($2));
    }
  ;
block_expr_expr
  : expr SEMICOLON
  | macro_expr
  ;

postfix_expr
  : primary_expr
  | postfix_expr OPERATOR {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(true);
      u->setOperatorName(*$2);
      u->setExpr(NodePtr($1));
      $$ = u;
      delete $2;
    }
  | postfix_expr DOT IDENTIFIER LPAREN RPAREN {
      CallExpr *c = new CallExpr;
      c->setName(*$3);
      c->setContext(NodePtr($1));
      $$ = c;
      delete $3;
    }
  | postfix_expr DOT IDENTIFIER LPAREN call_args RPAREN {
      CallExpr *c = new CallExpr;
      c->setName(*$3);
      c->setArgs(*$5);
      c->setContext(NodePtr($1));
      $$ = c;
      delete $3;
      delete $5;
    }
  | postfix_expr DOT IDENTIFIER {
      CallExpr *c = new CallExpr;
      c->setName(*$3);
      c->setContext(NodePtr($1));
      $$ = c;
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
      c->setArgs(*$3);
      $$ = c;
      delete $1;
      delete $3;
    }
  ;

call_args
  : call_arg {
      $$ = new Nodes;
      $$->push_back(NodePtr($1));
    }
  | call_args COMMA call_arg {
      $1->push_back(NodePtr($3));
    }
  ;

call_arg
  : IDENTIFIER COLON expr {
      CallExprArg *a = new CallExprArg;
      a->setName(*$1);
      a->setExpr(NodePtr($3));
      $$ = a;
      delete $1;
    }
  | expr {
      CallExprArg *a = new CallExprArg;
      a->setExpr(NodePtr($1));
      $$ = a;
    }
  ;

prefix_expr
  : postfix_expr
  | any_operator prefix_expr {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(false);
      u->setOperatorName(*$1);
      u->setExpr(NodePtr($2));
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
      e->setLhs(NodePtr($1));
      e->setRhs(NodePtr($3));
      $$ = e;
      delete $2;
    }
  ;

additive_expr
  : multiplicative_expr
  | additive_expr ADDITIVE_OPERATOR multiplicative_expr {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*$2);
      e->setLhs(NodePtr($1));
      e->setRhs(NodePtr($3));
      $$ = e;
      delete $2;
    }
  ;

relational_expr
  : additive_expr
  | relational_expr RELATIONAL_OPERATOR additive_expr {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*$2);
      e->setLhs(NodePtr($1));
      e->setRhs(NodePtr($3));
      $$ = e;
      delete $2;
    }
  ;

equality_expr
  : relational_expr
  | equality_expr EQUALITY_OPERATOR relational_expr {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*$2);
      e->setLhs(NodePtr($1));
      e->setRhs(NodePtr($3));
      $$ = e;
      delete $2;
    }
  ;

and_expr
  : equality_expr
  | and_expr AND_OPERATOR equality_expr {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*$2);
      e->setLhs(NodePtr($1));
      e->setRhs(NodePtr($3));
      $$ = e;
      delete $2;
    }
  ;

or_expr
  : and_expr
  | or_expr OR_OPERATOR and_expr {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*$2);
      e->setLhs(NodePtr($1));
      e->setRhs(NodePtr($3));
      $$ = e;
      delete $2;
    }
  ;

func_expr
  : or_expr
  | RIGHTARROW or_expr {
      FuncExpr *e = new FuncExpr;
      e->setExpr(NodePtr($2));
      $$ = e;
    }
  | func_args_tuple RIGHTARROW or_expr {
      FuncExpr *e = new FuncExpr;
      e->setArgs(*$1);
      e->setExpr(NodePtr($3));
      delete $1;
      $$ = e;
    }
  ;

assignment_expr
  : func_expr
  | assignment_expr ASSIGN func_expr {
      AssignmentExpr *e = new AssignmentExpr;
      e->setLhs(NodePtr($1));
      e->setRhs(NodePtr($3));
      $$ = e;
    }
  ;

var_expr
  : VAR IDENTIFIER typeexpr {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*$2);
      v->setTypeExpr(NodePtr($3));
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

expr
  : assignment_expr
  | var_expr { $$ = $<node>1; }
  | var_expr ASSIGN assignment_expr {
      $1->setInitialExpr(NodePtr($3));
    }
  | IDENTIFIER DEFASSIGN assignment_expr {
      TypelessVarDefExpr *v = new TypelessVarDefExpr;
      v->setName(*$1);
      v->setInitialExpr(NodePtr($3));
      $$ = v;
      delete $1;
    }
  ;

/* Large expressions that in C/C++ would be statements. Usually incorporate a
 * block of expressions or similar. */
macro_expr
  : if_expr
  | for_expr
  ;

any_expr: macro_expr | expr;

expr_list
  : expr {
      $$ = new Nodes;
      $$->push_back(NodePtr($1));
    }
  | expr_list COMMA expr {
      $1->push_back(NodePtr($3));
    }
  ;


/*
 * ----------------------------------------------------------------------------
 *
 *    TYPE EXPRESSIONS
 *
 * ----------------------------------------------------------------------------
 */

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
  | NIL {
      $$ = new NilTypeExpr;
    }
  | tuple_typeexpr
  | qualified_typeexpr
  | specialized_typeexpr
  ;

/* Union Type Expression */
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
      $$->push_back(NodePtr($1));
      $$->push_back(NodePtr($3));
    }
  | union_typeexprs PIPE nonunion_typeexpr {
      $1->push_back(NodePtr($3));
    }
  ;

/* Tuple Type Expression */
tuple_typeexpr
  : LPAREN tuple_typeexpr_args RPAREN {
      TupleTypeExpr *t = new TupleTypeExpr;
      t->setArgs(*$2);
      $$ = t;
      delete $2;
    }
  ;

tuple_typeexpr_args
  : tuple_typeexpr_arg {
      $$ = new Nodes;
      $$->push_back(NodePtr($1));
    }
  | tuple_typeexpr_args COMMA tuple_typeexpr_arg {
      $1->push_back(NodePtr($3));
    }
  ;

tuple_typeexpr_arg
  : typeexpr {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setExpr(NodePtr($1));
      $$ = t;
    }
  | IDENTIFIER COLON typeexpr {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setName(*$1);
      t->setExpr(NodePtr($3));
      $$ = t;
      delete $1;
    }
  ;

/* Qualified Type Expr */
qualified_typeexpr
  : qualified_typeexpr_qualifiers {
      QualifiedTypeExpr *q = new QualifiedTypeExpr;
      q->setExprs(*$1);
      $$ = q;
      delete $1;
    }
  ;

qualified_typeexpr_qualifiers
  : qualified_typeexpr_qualifier {
      $$ = new Nodes;
      $$->push_back(NodePtr($1));
    }
  | qualified_typeexpr_qualifiers qualified_typeexpr_qualifier {
      $1->push_back(NodePtr($2));
    }
  ;

/* Specialized Type Expr */
specialized_typeexpr
  : nonunion_typeexpr LBRACK specialized_typeexpr_specs RBRACK {
      SpecializedTypeExpr *t = new SpecializedTypeExpr;
      t->setExpr(NodePtr($1));
      t->setSpecExprs(*$3);
      $$ = t;
      delete $3;
    }
  ;
specialized_typeexpr_specs
  : typeexpr {
      $$ = new Nodes;
      $$->push_back(NodePtr($1));
    }
  | specialized_typeexpr_specs COMMA typeexpr {
      $1->push_back(NodePtr($3));
    }
  ;


/* TYPE QUALIFIERS */

qualified_typeexpr_qualifier
  : structure_qualifier
  | interface_qualifier
  | native_qualifier
  | range_qualifier
  ;

/* Structure */
structure_qualifier
  : structure_qualifier_decl LBRACE RBRACE { $$ = $1; }
  | structure_qualifier_decl LBRACE structure_qualifier_stmts RBRACE {
      $1->setStmts(*$3);
      delete $3;
    }
  ;

structure_qualifier_decl
  : VALUE {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("value");
      $$ = s;
    }
  | OBJECT {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("object");
      $$ = s;
    }
  ;

structure_qualifier_stmts
  : structure_qualifier_stmt { $$ = new Nodes; $$->push_back(NodePtr($1)); }
  | structure_qualifier_stmts structure_qualifier_stmt { $1->push_back(NodePtr($2)); }
  ;

structure_qualifier_stmt
  : IDENTIFIER SEMICOLON {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*$1);
      $$ = s;
      delete $1;
    }
  | IDENTIFIER typeexpr SEMICOLON {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*$1);
      s->setType(NodePtr($2));
      $$ = s;
      delete $1;
    }
  ;

/* Interface */
interface_qualifier
  : INTERFACE LBRACE RBRACE {
      InterfaceQualifier *i = new InterfaceQualifier;
      $$ = i;
    }
  | INTERFACE LBRACE interface_qualifier_stmts RBRACE {
      InterfaceQualifier *i = new InterfaceQualifier;
      i->setStmts(*$3);
      $$ = i;
      delete $3;
    }
  ;

interface_qualifier_stmts
  : interface_qualifier_stmt { $$ = new Nodes; $$->push_back(NodePtr($1)); }
  | interface_qualifier_stmts interface_qualifier_stmt { $1->push_back(NodePtr($2)); }
  ;

interface_qualifier_stmt
  : IDENTIFIER { $$ = new InvalidType; delete $1; /* dummy */ }
  ;

/* Native */
native_qualifier
  : NATIVE IDENTIFIER {
      NativeQualifier *n = new NativeQualifier;
      n->setName(*$2);
      $$ = n;
      delete $2;
    }
  ;

/* Range */
range_qualifier
  : range_qualifier_decl { $$ = $1; }
  | range_qualifier_decl LPAREN NUMBER COMMA NUMBER RPAREN {
      $1->setMin(*$3);
      $1->setMax(*$5);
      delete $3;
      delete $5;
    }
  ;

range_qualifier_decl
  : RANGE IDENTIFIER {
      RangeQualifier *r = new RangeQualifier;
      r->setName(*$2);
      $$ = r;
      delete $2;
    }
  ;

%% /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}