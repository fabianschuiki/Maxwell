/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

   Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

// Take the name prefix into account.
#define yylex   driverlex

#include "Parser.hpp"

/* User implementation prologue.  */
#line 117 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"

#include "Driver.hpp"
#include "Scanner.hpp"

/* This connects the Bison parser to the Flex scanner. */
#undef yylex
#define yylex driver.lexer->lex

using std::cout;
using std::endl;


/* Line 317 of lalr1.cc.  */
#line 56 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG							\
  for (bool yydebugcond_ = yydebug_; yydebugcond_; yydebugcond_ = false)	\
    (*yycdebug_)

/* Enable debugging if requested.  */
#if YYDEBUG

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab

namespace driver
{
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
      driver (driver_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif /* ! YYDEBUG */

  void
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 3: /* "\"identifier\"" */
#line 110 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 216 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 4: /* "\"number constant\"" */
#line 110 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 221 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 5: /* "\"string constant\"" */
#line 110 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 226 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 6: /* "MULTIPLICATIVE_OPERATOR" */
#line 110 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 231 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 7: /* "ADDITIVE_OPERATOR" */
#line 110 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 236 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 8: /* "RELATIONAL_OPERATOR" */
#line 110 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 241 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 12: /* "OPERATOR" */
#line 110 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 246 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;

	default:
	  break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }


  int
  Parser::parse ()
  {
    /// Look-ahead and look-ahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the look-ahead.
    semantic_type yylval;
    /// Location of the look-ahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    #line 28 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
{
	// initialize the location object
	yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}
  /* Line 555 of yacc.c.  */
#line 328 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;
    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without look-ahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a look-ahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Accept?  */
    if (yyn == yyfinal_)
      goto yyacceptlab;

    /* Shift the look-ahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted unless it is eof.  */
    if (yychar != yyeof_)
      yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 5:
#line 139 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 6:
#line 142 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 7:
#line 148 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(2) - (1)].funcDef)->setBody(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
            ;}
    break;

  case 8:
#line 151 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(3) - (1)].funcDef)->setIn(*(yysemantic_stack_[(3) - (2)].nodes));
              (yysemantic_stack_[(3) - (1)].funcDef)->setBody(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
              delete (yysemantic_stack_[(3) - (2)].nodes);
            ;}
    break;

  case 9:
#line 156 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(4) - (1)].funcDef)->setOut(*(yysemantic_stack_[(4) - (3)].nodes));
              (yysemantic_stack_[(4) - (1)].funcDef)->setBody(shared_ptr<Node>((yysemantic_stack_[(4) - (4)].node)));
              delete (yysemantic_stack_[(4) - (3)].nodes);
            ;}
    break;

  case 10:
#line 161 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(5) - (1)].funcDef)->setIn(*(yysemantic_stack_[(5) - (2)].nodes));
              (yysemantic_stack_[(5) - (1)].funcDef)->setOut(*(yysemantic_stack_[(5) - (4)].nodes));
              (yysemantic_stack_[(5) - (1)].funcDef)->setBody(shared_ptr<Node>((yysemantic_stack_[(5) - (5)].node)));
              delete (yysemantic_stack_[(5) - (2)].nodes);
              delete (yysemantic_stack_[(5) - (4)].nodes);
             ;}
    break;

  case 11:
#line 171 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName(*(yysemantic_stack_[(2) - (2)].string)); delete (yysemantic_stack_[(2) - (2)].string);
      (yyval.funcDef) = d;
    ;}
    break;

  case 12:
#line 176 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName(*(yysemantic_stack_[(2) - (2)].string)); delete (yysemantic_stack_[(2) - (2)].string);
      (yyval.funcDef) = d;
    ;}
    break;

  case 13:
#line 181 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName("_" + *(yysemantic_stack_[(3) - (3)].string)); delete (yysemantic_stack_[(3) - (3)].string);
      (yyval.funcDef) = d;
    ;}
    break;

  case 14:
#line 189 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; ;}
    break;

  case 15:
#line 190 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 16:
#line 194 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 17:
#line 200 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 18:
#line 204 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 19:
#line 210 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncArg *a = new FuncArg;
      a->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = a;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 20:
#line 216 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncArg *a = new FuncArg;
      a->setName(*(yysemantic_stack_[(2) - (1)].string));
      a->setTypeExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 21:
#line 227 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].typeDef); ;}
    break;

  case 22:
#line 228 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].typeDef)->setType(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 23:
#line 236 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TypeDef *t = new TypeDef;
      t->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.typeDef) = t;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 24:
#line 244 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          FuncBody *b = new FuncBody;
          (yyval.node) = b;
        ;}
    break;

  case 25:
#line 248 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          FuncBody *b = new FuncBody;
          b->setStmts(*(yysemantic_stack_[(3) - (2)].nodes));
          (yyval.node) = b;
          delete (yysemantic_stack_[(3) - (2)].nodes);
        ;}
    break;

  case 26:
#line 256 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yyval.nodes) = new Nodes;
          (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
        ;}
    break;

  case 27:
#line 260 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yysemantic_stack_[(2) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
        ;}
    break;

  case 28:
#line 266 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      ExprStmt *s = new ExprStmt;
      s->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (1)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 31:
#line 273 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.node) = new BlockStmt;
    ;}
    break;

  case 32:
#line 276 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BlockStmt *b = new BlockStmt;
      b->setStmts(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = b;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 33:
#line 285 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfStmt *s = new IfStmt;
      s->setCond(NodePtr((yysemantic_stack_[(5) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 34:
#line 291 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfStmt *s = new IfStmt;
      s->setCond(NodePtr((yysemantic_stack_[(7) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(7) - (5)].node)));
      s->setElseStmt(NodePtr((yysemantic_stack_[(7) - (7)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 35:
#line 301 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      ForStmt *s = new ForStmt;
      s->setCond(NodePtr((yysemantic_stack_[(5) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 36:
#line 307 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      ForStmt *s = new ForStmt;
      s->setInit(NodePtr((yysemantic_stack_[(9) - (3)].node)));
      s->setCond(NodePtr((yysemantic_stack_[(9) - (5)].node)));
      s->setStep(NodePtr((yysemantic_stack_[(9) - (7)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(9) - (9)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 37:
#line 326 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IdentifierExpr *i = new IdentifierExpr;
      i->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = i;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 38:
#line 332 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); ;}
    break;

  case 39:
#line 333 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
     NumberConstExpr *n = new NumberConstExpr;
     n->setValue(*(yysemantic_stack_[(1) - (1)].string));
     (yyval.node) = n;
     delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 40:
#line 339 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StringConstExpr *s = new StringConstExpr;
      s->setValue(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 41:
#line 345 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* array literals */
      ArrayConstExpr *a = new ArrayConstExpr;
      a->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 42:
#line 351 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* set literals */
      SetConstExpr *s = new SetConstExpr;
      s->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 43:
#line 357 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* map literals */
      MapConstExpr *m = new MapConstExpr;
      m->setPairs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = m;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 45:
#line 367 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 46:
#line 371 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 47:
#line 376 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      MapConstExprPair *p = new MapConstExprPair;
      p->setKey(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      p->setValue(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = p;
    ;}
    break;

  case 48:
#line 385 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 49:
#line 391 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*(yysemantic_stack_[(6) - (2)].nodes));
      i->setOtherwise(NodePtr((yysemantic_stack_[(6) - (4)].node)));
      (yyval.node) = i;
      delete (yysemantic_stack_[(6) - (2)].nodes);
    ;}
    break;

  case 50:
#line 400 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 51:
#line 404 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 52:
#line 409 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExprCond *c = new IfCaseExprCond;
      c->setExpr(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      c->setCond(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = c;
    ;}
    break;

  case 54:
#line 419 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(true);
      u->setOperatorName(*(yysemantic_stack_[(2) - (2)].string));
      u->setExpr(NodePtr((yysemantic_stack_[(2) - (1)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 55:
#line 427 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(5) - (3)].string));
      c->setContext(NodePtr((yysemantic_stack_[(5) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(5) - (3)].string);
    ;}
    break;

  case 56:
#line 434 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(6) - (3)].string));
      c->setArgs(*(yysemantic_stack_[(6) - (5)].nodes));
      c->setContext(NodePtr((yysemantic_stack_[(6) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(6) - (3)].string);
      delete (yysemantic_stack_[(6) - (5)].nodes);
    ;}
    break;

  case 57:
#line 443 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (3)].string));
      c->setContext(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (3)].string);
    ;}
    break;

  case 58:
#line 450 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (1)].string));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 59:
#line 456 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(4) - (1)].string));
      c->setArgs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = c;
      delete (yysemantic_stack_[(4) - (1)].string);
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 60:
#line 467 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 61:
#line 471 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 62:
#line 477 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setName(*(yysemantic_stack_[(3) - (1)].string));
      a->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 63:
#line 484 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setExpr(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = a;
    ;}
    break;

  case 65:
#line 493 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(false);
      u->setOperatorName(*(yysemantic_stack_[(2) - (1)].string));
      u->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 71:
#line 506 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 73:
#line 518 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 75:
#line 530 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 77:
#line 542 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 79:
#line 554 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 81:
#line 566 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 83:
#line 578 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      AssignmentExpr *e = new AssignmentExpr;
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
    ;}
    break;

  case 84:
#line 587 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*(yysemantic_stack_[(3) - (2)].string));
      v->setTypeExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.varDefExpr) = v;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 85:
#line 594 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.varDefExpr) = v;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 87:
#line 604 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); ;}
    break;

  case 88:
#line 605 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].varDefExpr)->setInitialExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 89:
#line 611 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 90:
#line 615 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 93:
#line 635 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NamedTypeExpr *n = new NamedTypeExpr;
      n->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 97:
#line 648 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnionTypeExpr *t = new UnionTypeExpr;
      t->setTypes(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 98:
#line 657 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 99:
#line 662 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 100:
#line 669 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExpr *t = new TupleTypeExpr;
      t->setArgs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 101:
#line 678 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 102:
#line 683 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 103:
#line 689 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setExpr(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = t;
    ;}
    break;

  case 104:
#line 694 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setName(*(yysemantic_stack_[(3) - (1)].string));
      t->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 105:
#line 705 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      QualifiedTypeExpr *q = new QualifiedTypeExpr;
      q->setExprs(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = q;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 106:
#line 714 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 107:
#line 718 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 108:
#line 725 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      SpecializedTypeExpr *t = new SpecializedTypeExpr;
      t->setExpr(NodePtr((yysemantic_stack_[(4) - (1)].node)));
      t->setSpecExprs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 109:
#line 734 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 110:
#line 738 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 115:
#line 755 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (1)].structureQualifier); ;}
    break;

  case 116:
#line 756 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(4) - (1)].structureQualifier)->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 117:
#line 763 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("value");
      (yyval.structureQualifier) = s;
    ;}
    break;

  case 118:
#line 768 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("object");
      (yyval.structureQualifier) = s;
    ;}
    break;

  case 119:
#line 776 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); ;}
    break;

  case 120:
#line 777 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); ;}
    break;

  case 121:
#line 781 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(2) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 122:
#line 787 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(3) - (1)].string));
      s->setType(NodePtr((yysemantic_stack_[(3) - (2)].node)));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 123:
#line 798 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      (yyval.node) = i;
    ;}
    break;

  case 124:
#line 802 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      i->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 125:
#line 811 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); ;}
    break;

  case 126:
#line 812 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); ;}
    break;

  case 127:
#line 816 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = new InvalidType; delete (yysemantic_stack_[(1) - (1)].string); /* dummy */ ;}
    break;

  case 128:
#line 821 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NativeQualifier *n = new NativeQualifier;
      n->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 129:
#line 831 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].rangeQualifier); ;}
    break;

  case 130:
#line 832 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMin(*(yysemantic_stack_[(6) - (3)].string));
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMax(*(yysemantic_stack_[(6) - (5)].string));
      delete (yysemantic_stack_[(6) - (3)].string);
      delete (yysemantic_stack_[(6) - (5)].string);
    ;}
    break;

  case 131:
#line 841 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      RangeQualifier *r = new RangeQualifier;
      r->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.rangeQualifier) = r;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 1347 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	default: break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse look-ahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    if (yyn == yyfinal_)
      goto yyacceptlab;

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the look-ahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		   &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyeof_ && yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char Parser::yypact_ninf_ = -64;
  const short int
  Parser::yypact_[] =
  {
         5,    96,    84,    89,     5,   -64,   -64,    10,   -64,   162,
     -64,   -64,   -64,   -64,   -64,   143,   -64,   -64,   -64,   -64,
     162,     7,    65,    27,    23,   -64,   -64,   -64,   -64,   -64,
      62,   102,   106,   340,   -64,    82,   -64,    66,   -64,   -64,
     140,   -64,   -64,   -64,    85,   -64,   -64,   -64,   108,   -64,
     -64,   -64,    29,   -64,   110,   -64,   -64,   128,   118,   124,
     301,   164,   -64,   301,   195,   -64,   -64,   -64,   -64,   -64,
      28,   -64,   334,   148,   149,   156,   165,   163,   166,   134,
     144,   147,   157,    27,   -64,     6,   -64,   -64,   152,   -64,
      48,   155,   162,   162,   162,   -64,    11,   190,   -64,   201,
     115,   162,   301,   301,   301,   175,   -64,   226,   168,   -15,
     -64,    44,   -64,    -3,    63,   -64,    92,   -64,   -64,   -64,
     205,   -64,   334,   334,   334,   334,   334,   334,   334,   334,
     -64,   -64,   157,   -64,   -64,    25,   -64,   162,   -64,   340,
     340,   -64,    98,   176,   176,    13,   -64,    26,   -64,   174,
     -64,   -14,   -64,    49,   -64,   -64,   -64,   182,    35,   191,
     -64,   -64,   301,   -64,    22,   -64,   301,   301,   -64,   301,
     -64,   184,   -64,   148,   149,   156,   165,   163,   166,   134,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   162,   -64,   177,
     -64,   -64,   211,   301,   -64,   321,   257,   257,   301,   -64,
     -64,   168,   -64,   -64,    -5,   -64,   -64,   288,   -64,   -64,
     187,   -64,   -64,   197,   -64,   180,   193,   -64,    54,   -64,
     257,   301,   -64,   -64,   -64,   192,   257,   -64
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     0,     2,     4,     5,     0,     6,    21,
      11,    66,    67,    68,    69,     0,    12,    23,     1,     3,
      19,     0,     0,     0,     0,    15,     7,    93,   117,   118,
       0,     0,     0,     0,    22,    91,    92,    97,    94,    95,
     105,    96,   106,   111,     0,   112,   113,   114,   129,    13,
      20,    14,     0,    17,    37,    39,    40,     0,     0,     0,
       0,     0,    24,     0,     0,    26,    29,    30,    53,    44,
      64,    70,     0,    72,    74,    76,    78,    80,    82,    86,
      87,     0,     0,     0,     8,     0,   128,   131,    93,   103,
       0,     0,     0,     0,     0,   107,     0,     0,    16,     0,
       0,    85,     0,     0,     0,     0,    31,     0,    53,     0,
      45,     0,    50,    89,     0,    89,     0,    25,    27,    54,
       0,    65,     0,     0,     0,     0,     0,     0,     0,     0,
      28,     9,     0,   127,   123,     0,   125,     0,   100,     0,
       0,   109,     0,    98,    99,     0,   115,     0,   119,     0,
      18,    37,    58,     0,    60,    63,    84,     0,     0,    89,
      38,    32,     0,    43,     0,    48,     0,     0,    42,     0,
      41,    57,    71,    73,    75,    77,    79,    81,    83,    88,
      10,   124,   126,   104,   102,   101,   108,     0,   121,     0,
     116,   120,     0,     0,    59,     0,     0,     0,     0,    47,
      37,     0,    46,    51,     0,    52,    90,     0,   110,   122,
       0,    62,    61,    33,    35,     0,     0,    55,     0,   130,
       0,     0,    49,    56,    34,     0,     0,    36
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
       -64,   -64,   -64,   219,   -64,   -64,   -16,   -64,   -17,   -64,
     -64,   -22,   178,   -63,   -64,   -64,   -58,   -64,    71,   -64,
     -64,    70,   -64,    30,    45,   -60,    60,   119,   120,   121,
     117,   123,   125,   116,   -64,   -55,   185,    -9,    31,   -64,
     -64,   -64,   -64,     2,   -64,   -64,   -64,   -64,   207,   -64,
     -64,   -64,   105,   -64,   -64,   131,   -64,   -64,   -64
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     3,     4,     5,     6,     7,    24,    52,    25,     8,
       9,    26,    64,    65,    66,    67,    68,   109,   110,    69,
     111,   112,    70,   153,   154,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,   114,    89,    35,    36,
      37,    38,    90,    91,    39,    40,    41,   142,    42,    43,
      44,   147,   148,    45,   135,   136,    46,    47,    48
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        34,   118,    84,   108,    53,   105,   113,    82,   115,   133,
      20,    50,   121,    20,   145,   100,    27,   163,   167,     1,
     167,     2,   164,   216,   193,   200,    55,    56,   133,   145,
      20,    28,    29,    30,    31,    32,   130,    51,   134,    21,
     119,    22,    33,   146,   118,   155,   108,   157,   158,   159,
      23,    60,   188,   104,    22,    63,    21,   181,   190,    98,
     131,    16,   172,    83,   120,   197,    99,   132,    54,    55,
      56,    11,    12,    13,   198,    49,   165,    14,   138,   194,
      57,   166,   150,   141,   223,   139,   195,    17,    58,    18,
      59,   195,   156,    85,    60,   168,    61,    62,    63,    10,
     169,    94,    11,    12,    13,    86,   201,   199,    14,    87,
     180,   204,   205,    15,   206,    92,    96,    93,   151,    55,
      56,    11,    12,    13,   143,   144,   170,    14,   183,   169,
      57,   101,   186,   213,   214,   187,   189,    97,   211,   100,
     155,   184,   185,   215,    60,   152,   104,   102,    63,    11,
      12,    13,   155,   103,   122,    14,   123,   224,    28,    29,
      30,    31,    32,   227,   124,    27,   225,    54,    55,    56,
      11,    12,    13,   126,   125,   128,    14,   127,   208,    57,
      28,    29,    30,    31,    32,   129,   130,    58,    22,    59,
     137,    33,   140,    60,   149,    61,   106,    63,    54,    55,
      56,    11,    12,    13,    20,   160,   162,    14,   171,    92,
      57,   192,   196,   207,   167,   210,   209,   219,    58,   221,
      59,   220,   226,    19,    60,   222,    61,   117,    63,    54,
      55,    56,    11,    12,    13,   202,   203,   218,    14,   107,
     212,    57,   173,   176,   174,   179,   175,    95,   116,    58,
     177,    59,   191,   178,     0,    60,     0,    61,   161,    63,
      54,    55,    56,    11,    12,    13,   182,     0,     0,    14,
       0,     0,    57,     0,     0,     0,     0,     0,     0,     0,
      58,     0,    59,     0,     0,     0,    60,     0,    61,     0,
      63,   151,    55,    56,    11,    12,    13,     0,     0,     0,
      14,     0,     0,    57,    54,    55,    56,    11,    12,    13,
       0,     0,     0,    14,     0,     0,    57,    60,   217,   104,
       0,    63,     0,     0,   151,    55,    56,    11,    12,    13,
      60,     0,   104,    14,    63,     0,    57,    54,    55,    56,
      11,    12,    13,    88,     0,     0,    14,     0,     0,     0,
      60,     0,   104,     0,    63,     0,     0,     0,    28,    29,
      30,    31,    32,    60,     0,   104,     0,    63,     0,    33
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
         9,    64,    24,    61,    21,    60,    61,    23,    63,     3,
       3,    20,    72,     3,     3,    29,     3,    32,    23,    14,
      23,    16,    37,    28,    38,     3,     4,     5,     3,     3,
       3,    18,    19,    20,    21,    22,    39,    30,    32,    29,
      12,    31,    29,    32,   107,   100,   104,   102,   103,   104,
      40,    29,    39,    31,    31,    33,    29,    32,    32,    30,
      82,     1,   122,    40,    36,    30,    37,    83,     3,     4,
       5,     6,     7,     8,    39,    15,    32,    12,    30,    30,
      15,    37,    99,    92,    30,    37,    37,     3,    23,     0,
      25,    37,   101,    31,    29,    32,    31,    32,    33,     3,
      37,    35,     6,     7,     8,     3,   164,   162,    12,     3,
     132,   166,   167,    17,   169,    33,    31,    35,     3,     4,
       5,     6,     7,     8,    93,    94,    34,    12,   137,    37,
      15,     3,    34,   196,   197,    37,   145,    29,   193,    29,
     195,   139,   140,   198,    29,    30,    31,    29,    33,     6,
       7,     8,   207,    29,     6,    12,     7,   220,    18,    19,
      20,    21,    22,   226,     8,     3,   221,     3,     4,     5,
       6,     7,     8,    10,     9,    41,    12,    11,   187,    15,
      18,    19,    20,    21,    22,    41,    39,    23,    31,    25,
      38,    29,    37,    29,     4,    31,    32,    33,     3,     4,
       5,     6,     7,     8,     3,    30,    38,    12,     3,    33,
      15,    37,    30,    29,    23,     4,    39,    30,    23,    39,
      25,    24,    30,     4,    29,    32,    31,    32,    33,     3,
       4,     5,     6,     7,     8,   164,   166,   207,    12,    61,
     195,    15,   123,   126,   124,   129,   125,    40,    63,    23,
     127,    25,   147,   128,    -1,    29,    -1,    31,    32,    33,
       3,     4,     5,     6,     7,     8,   135,    -1,    -1,    12,
      -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    25,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    -1,    -1,    15,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    -1,    -1,    15,    29,    30,    31,
      -1,    33,    -1,    -1,     3,     4,     5,     6,     7,     8,
      29,    -1,    31,    12,    33,    -1,    15,     3,     4,     5,
       6,     7,     8,     3,    -1,    -1,    12,    -1,    -1,    -1,
      29,    -1,    31,    -1,    33,    -1,    -1,    -1,    18,    19,
      20,    21,    22,    29,    -1,    31,    -1,    33,    -1,    29
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    14,    16,    43,    44,    45,    46,    47,    51,    52,
       3,     6,     7,     8,    12,    17,    68,     3,     0,    45,
       3,    29,    31,    40,    48,    50,    53,     3,    18,    19,
      20,    21,    22,    29,    79,    80,    81,    82,    83,    86,
      87,    88,    90,    91,    92,    95,    98,    99,   100,    68,
      79,    30,    49,    50,     3,     4,     5,    15,    23,    25,
      29,    31,    32,    33,    54,    55,    56,    57,    58,    61,
      64,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    48,    40,    53,    31,     3,     3,     3,    79,
      84,    85,    33,    35,    35,    90,    31,    29,    30,    37,
      29,     3,    29,    29,    31,    77,    32,    54,    58,    59,
      60,    62,    63,    77,    78,    77,    78,    32,    55,    12,
      36,    67,     6,     7,     8,     9,    10,    11,    41,    41,
      39,    53,    48,     3,    32,    96,    97,    38,    30,    37,
      37,    79,    89,    80,    80,     3,    32,    93,    94,     4,
      50,     3,    30,    65,    66,    77,    79,    77,    77,    77,
      30,    32,    38,    32,    37,    32,    37,    23,    32,    37,
      34,     3,    67,    69,    70,    71,    72,    73,    74,    75,
      53,    32,    97,    79,    85,    85,    34,    37,    39,    79,
      32,    94,    37,    38,    30,    37,    30,    30,    39,    77,
       3,    58,    60,    63,    77,    77,    77,    29,    79,    39,
       4,    77,    66,    55,    55,    77,    28,    30,    65,    30,
      24,    39,    32,    30,    55,    77,    30,    55
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    42,    43,    44,    44,    45,    45,    46,    46,    46,
      46,    47,    47,    47,    48,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    53,    53,    54,    54,    55,    55,
      55,    55,    55,    56,    56,    57,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    59,    59,    60,    61,    61,
      62,    62,    63,    64,    64,    64,    64,    64,    64,    64,
      65,    65,    66,    66,    67,    67,    68,    68,    68,    68,
      69,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    74,    75,    75,    76,    76,    77,    77,    77,    78,
      78,    79,    79,    80,    80,    80,    80,    81,    82,    82,
      83,    84,    84,    85,    85,    86,    87,    87,    88,    89,
      89,    90,    90,    90,    90,    91,    91,    92,    92,    93,
      93,    94,    94,    95,    95,    96,    96,    97,    98,    99,
      99,   100
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     2,     1,     1,     1,     2,     3,     4,
       5,     2,     2,     3,     2,     1,     3,     1,     3,     1,
       2,     1,     2,     2,     2,     3,     1,     2,     2,     1,
       1,     2,     3,     5,     7,     5,     9,     1,     3,     1,
       1,     3,     3,     3,     1,     1,     3,     3,     3,     6,
       1,     3,     3,     1,     2,     5,     6,     3,     3,     4,
       1,     3,     3,     1,     1,     2,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     2,     1,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     1,     3,     1,     1,     2,     4,     1,
       3,     1,     1,     1,     1,     3,     4,     1,     1,     1,
       2,     2,     3,     3,     4,     1,     2,     1,     2,     1,
       6,     2
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of input\"", "error", "$undefined", "\"identifier\"",
  "\"number constant\"", "\"string constant\"", "MULTIPLICATIVE_OPERATOR",
  "ADDITIVE_OPERATOR", "RELATIONAL_OPERATOR", "EQUALITY_OPERATOR",
  "AND_OPERATOR", "OR_OPERATOR", "OPERATOR", "\"symbol\"",
  "\"func keyword\"", "\"var keyword\"", "\"type keyword\"",
  "\"unary keyword\"", "\"value keyword\"", "\"object keyword\"",
  "\"interface keyword\"", "\"native keyword\"", "\"range keyword\"",
  "\"if keyword\"", "\"else keyword\"", "\"for keyword\"",
  "\"nil constant\"", "\"incase keyword\"", "\"otherwise keyword\"",
  "\"opening paranthesis (\"", "\"closing paranthesis )\"",
  "\"opening braces {\"", "\"closing braces }\"", "\"opening bracket [\"",
  "\"closing bracket ]\"", "\"vertical pipe |\"", "\".\"", "\",\"",
  "\":\"", "\";\"", "\"right arrow ->\"", "\"assignment operator =\"",
  "$accept", "root", "root_stmts", "root_stmt", "func_decl",
  "func_decl_name", "func_args_tuple", "func_args", "func_arg",
  "type_decl", "type_decl_name", "body", "stmts", "stmt", "if_stmt",
  "for_stmt", "primary_expr", "map_expr_pairs", "map_expr_pair", "if_expr",
  "if_expr_conds", "if_expr_cond", "postfix_expr", "call_args", "call_arg",
  "prefix_expr", "any_operator", "multiplicative_expr", "additive_expr",
  "relational_expr", "equality_expr", "and_expr", "or_expr",
  "assignment_expr", "var_expr", "expr", "expr_list", "typeexpr",
  "nonunion_typeexpr", "union_typeexpr", "union_typeexprs",
  "tuple_typeexpr", "tuple_typeexpr_args", "tuple_typeexpr_arg",
  "qualified_typeexpr", "qualified_typeexpr_qualifiers",
  "specialized_typeexpr", "specialized_typeexpr_specs",
  "qualified_typeexpr_qualifier", "structure_qualifier",
  "structure_qualifier_decl", "structure_qualifier_stmts",
  "structure_qualifier_stmt", "interface_qualifier",
  "interface_qualifier_stmts", "interface_qualifier_stmt",
  "native_qualifier", "range_qualifier", "range_qualifier_decl", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        43,     0,    -1,    44,    -1,    44,    45,    -1,    45,    -1,
      46,    -1,    51,    -1,    47,    53,    -1,    47,    48,    53,
      -1,    47,    40,    48,    53,    -1,    47,    48,    40,    48,
      53,    -1,    14,     3,    -1,    14,    68,    -1,    14,    17,
      68,    -1,    29,    30,    -1,    50,    -1,    29,    49,    30,
      -1,    50,    -1,    49,    37,    50,    -1,     3,    -1,     3,
      79,    -1,    52,    -1,    52,    79,    -1,    16,     3,    -1,
      31,    32,    -1,    31,    54,    32,    -1,    55,    -1,    54,
      55,    -1,    77,    39,    -1,    56,    -1,    57,    -1,    31,
      32,    -1,    31,    54,    32,    -1,    23,    29,    77,    30,
      55,    -1,    23,    29,    77,    30,    55,    24,    55,    -1,
      25,    29,    77,    30,    55,    -1,    25,    29,    77,    39,
      77,    39,    77,    30,    55,    -1,     3,    -1,    29,    77,
      30,    -1,     4,    -1,     5,    -1,    33,    78,    34,    -1,
      31,    78,    32,    -1,    31,    59,    32,    -1,    61,    -1,
      60,    -1,    59,    37,    60,    -1,    58,    38,    77,    -1,
      31,    62,    32,    -1,    31,    62,    37,    77,    28,    32,
      -1,    63,    -1,    62,    37,    63,    -1,    77,    23,    77,
      -1,    58,    -1,    64,    12,    -1,    64,    36,     3,    29,
      30,    -1,    64,    36,     3,    29,    65,    30,    -1,    64,
      36,     3,    -1,     3,    29,    30,    -1,     3,    29,    65,
      30,    -1,    66,    -1,    65,    37,    66,    -1,     3,    38,
      77,    -1,    77,    -1,    64,    -1,    68,    67,    -1,     6,
      -1,     7,    -1,     8,    -1,    12,    -1,    67,    -1,    69,
       6,    67,    -1,    69,    -1,    70,     7,    69,    -1,    70,
      -1,    71,     8,    70,    -1,    71,    -1,    72,     9,    71,
      -1,    72,    -1,    73,    10,    72,    -1,    73,    -1,    74,
      11,    73,    -1,    74,    -1,    75,    41,    74,    -1,    15,
       3,    79,    -1,    15,     3,    -1,    75,    -1,    76,    -1,
      76,    41,    75,    -1,    77,    -1,    78,    37,    77,    -1,
      80,    -1,    81,    -1,     3,    -1,    83,    -1,    86,    -1,
      88,    -1,    82,    -1,    80,    35,    80,    -1,    82,    35,
      80,    -1,    29,    84,    30,    -1,    85,    37,    85,    -1,
      84,    37,    85,    -1,    79,    -1,     3,    38,    79,    -1,
      87,    -1,    90,    -1,    87,    90,    -1,    80,    33,    89,
      34,    -1,    79,    -1,    89,    37,    79,    -1,    91,    -1,
      95,    -1,    98,    -1,    99,    -1,    92,    31,    32,    -1,
      92,    31,    93,    32,    -1,    18,    -1,    19,    -1,    94,
      -1,    93,    94,    -1,     3,    39,    -1,     3,    79,    39,
      -1,    20,    31,    32,    -1,    20,    31,    96,    32,    -1,
      97,    -1,    96,    97,    -1,     3,    -1,    21,     3,    -1,
     100,    -1,   100,    29,     4,    37,     4,    30,    -1,    22,
       3,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    10,    12,    14,    17,    21,
      26,    32,    35,    38,    42,    45,    47,    51,    53,    57,
      59,    62,    64,    67,    70,    73,    77,    79,    82,    85,
      87,    89,    92,    96,   102,   110,   116,   126,   128,   132,
     134,   136,   140,   144,   148,   150,   152,   156,   160,   164,
     171,   173,   177,   181,   183,   186,   192,   199,   203,   207,
     212,   214,   218,   222,   224,   226,   229,   231,   233,   235,
     237,   239,   243,   245,   249,   251,   255,   257,   261,   263,
     267,   269,   273,   275,   279,   283,   286,   288,   290,   294,
     296,   300,   302,   304,   306,   308,   310,   312,   314,   318,
     322,   326,   330,   334,   336,   340,   342,   344,   347,   352,
     354,   358,   360,   362,   364,   366,   370,   375,   377,   379,
     381,   384,   387,   391,   395,   400,   402,   405,   407,   410,
     412,   419
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   132,   132,   135,   136,   139,   142,   148,   151,   156,
     161,   171,   176,   181,   189,   190,   194,   200,   204,   210,
     216,   227,   228,   236,   244,   248,   256,   260,   266,   271,
     272,   273,   276,   285,   291,   301,   307,   326,   332,   333,
     339,   345,   351,   357,   363,   367,   371,   376,   385,   391,
     400,   404,   409,   418,   419,   427,   434,   443,   450,   456,
     467,   471,   477,   484,   492,   493,   502,   502,   502,   502,
     505,   506,   517,   518,   529,   530,   541,   542,   553,   554,
     565,   566,   577,   578,   587,   594,   603,   604,   605,   611,
     615,   630,   631,   635,   641,   642,   643,   648,   657,   662,
     669,   678,   683,   689,   694,   705,   714,   718,   725,   734,
     738,   747,   748,   749,   750,   755,   756,   763,   768,   776,
     777,   781,   787,   798,   802,   811,   812,   816,   821,   831,
     832,   841
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "), ";
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 369;
  const int Parser::yynnts_ = 59;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 18;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 42;

  const unsigned int Parser::yyuser_token_number_max_ = 296;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace driver

#line 849 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
 /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}
