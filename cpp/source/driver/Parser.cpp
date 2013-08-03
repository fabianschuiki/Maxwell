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
              driver.add(NodePtr((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 6:
#line 142 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(NodePtr((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 7:
#line 148 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(2) - (1)].funcDef)->setBody(NodePtr((yysemantic_stack_[(2) - (2)].node)));
            ;}
    break;

  case 8:
#line 151 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(3) - (1)].funcDef)->setIn(*(yysemantic_stack_[(3) - (2)].nodes));
              (yysemantic_stack_[(3) - (1)].funcDef)->setBody(NodePtr((yysemantic_stack_[(3) - (3)].node)));
              delete (yysemantic_stack_[(3) - (2)].nodes);
            ;}
    break;

  case 9:
#line 156 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(4) - (1)].funcDef)->setOut(*(yysemantic_stack_[(4) - (3)].nodes));
              (yysemantic_stack_[(4) - (1)].funcDef)->setBody(NodePtr((yysemantic_stack_[(4) - (4)].node)));
              delete (yysemantic_stack_[(4) - (3)].nodes);
            ;}
    break;

  case 10:
#line 161 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(5) - (1)].funcDef)->setIn(*(yysemantic_stack_[(5) - (2)].nodes));
              (yysemantic_stack_[(5) - (1)].funcDef)->setOut(*(yysemantic_stack_[(5) - (4)].nodes));
              (yysemantic_stack_[(5) - (1)].funcDef)->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
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
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
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
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 18:
#line 204 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
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
      a->setTypeExpr(NodePtr((yysemantic_stack_[(2) - (2)].node)));
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
#line 267 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IdentifierExpr *i = new IdentifierExpr;
      i->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = i;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 25:
#line 273 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); ;}
    break;

  case 26:
#line 274 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
     NumberConstExpr *n = new NumberConstExpr;
     n->setValue(*(yysemantic_stack_[(1) - (1)].string));
     (yyval.node) = n;
     delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 27:
#line 280 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StringConstExpr *s = new StringConstExpr;
      s->setValue(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 28:
#line 286 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* array literals */
      ArrayConstExpr *a = new ArrayConstExpr;
      a->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 29:
#line 292 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* set literals */
      SetConstExpr *s = new SetConstExpr;
      s->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 30:
#line 298 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* map literals */
      MapConstExpr *m = new MapConstExpr;
      m->setPairs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = m;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 32:
#line 308 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 33:
#line 312 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 34:
#line 317 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      MapConstExprPair *p = new MapConstExprPair;
      p->setKey(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      p->setValue(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = p;
    ;}
    break;

  case 35:
#line 326 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 36:
#line 332 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*(yysemantic_stack_[(6) - (2)].nodes));
      i->setOtherwise(NodePtr((yysemantic_stack_[(6) - (4)].node)));
      (yyval.node) = i;
      delete (yysemantic_stack_[(6) - (2)].nodes);
    ;}
    break;

  case 37:
#line 341 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 38:
#line 345 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 39:
#line 350 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExprCond *c = new IfCaseExprCond;
      c->setExpr(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      c->setCond(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = c;
    ;}
    break;

  case 40:
#line 359 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfExpr *s = new IfExpr;
      s->setCond(NodePtr((yysemantic_stack_[(5) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 41:
#line 365 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfExpr *s = new IfExpr;
      s->setCond(NodePtr((yysemantic_stack_[(7) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(7) - (5)].node)));
      s->setElseExpr(NodePtr((yysemantic_stack_[(7) - (7)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 42:
#line 375 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      ForExpr *s = new ForExpr;
      s->setCond(NodePtr((yysemantic_stack_[(5) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 43:
#line 381 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      ForExpr *s = new ForExpr;
      s->setInit(NodePtr((yysemantic_stack_[(9) - (3)].node)));
      s->setCond(NodePtr((yysemantic_stack_[(9) - (5)].node)));
      s->setStep(NodePtr((yysemantic_stack_[(9) - (7)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(9) - (9)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 46:
#line 397 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BlockExpr *b = new BlockExpr;
      (yyval.node) = b;
    ;}
    break;

  case 47:
#line 401 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BlockExpr *b = new BlockExpr;
      b->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = b;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 48:
#line 409 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 49:
#line 413 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 53:
#line 424 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(true);
      u->setOperatorName(*(yysemantic_stack_[(2) - (2)].string));
      u->setExpr(NodePtr((yysemantic_stack_[(2) - (1)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 54:
#line 432 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(5) - (3)].string));
      c->setContext(NodePtr((yysemantic_stack_[(5) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(5) - (3)].string);
    ;}
    break;

  case 55:
#line 439 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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

  case 56:
#line 448 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (3)].string));
      c->setContext(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (3)].string);
    ;}
    break;

  case 57:
#line 455 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (1)].string));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 58:
#line 461 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(4) - (1)].string));
      c->setArgs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = c;
      delete (yysemantic_stack_[(4) - (1)].string);
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 59:
#line 472 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 60:
#line 476 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 61:
#line 482 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setName(*(yysemantic_stack_[(3) - (1)].string));
      a->setExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 62:
#line 489 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setExpr(NodePtr((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = a;
    ;}
    break;

  case 64:
#line 498 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(false);
      u->setOperatorName(*(yysemantic_stack_[(2) - (1)].string));
      u->setExpr(NodePtr((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 70:
#line 511 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 72:
#line 523 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 74:
#line 535 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 76:
#line 547 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 78:
#line 559 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 80:
#line 571 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 82:
#line 583 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      AssignmentExpr *e = new AssignmentExpr;
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
    ;}
    break;

  case 83:
#line 592 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*(yysemantic_stack_[(3) - (2)].string));
      v->setTypeExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.varDefExpr) = v;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 84:
#line 599 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.varDefExpr) = v;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 86:
#line 609 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); ;}
    break;

  case 87:
#line 610 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].varDefExpr)->setInitialExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 92:
#line 625 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 93:
#line 629 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 96:
#line 649 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NamedTypeExpr *n = new NamedTypeExpr;
      n->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 100:
#line 662 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnionTypeExpr *t = new UnionTypeExpr;
      t->setTypes(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 101:
#line 671 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 102:
#line 676 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 103:
#line 683 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExpr *t = new TupleTypeExpr;
      t->setArgs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 104:
#line 692 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 105:
#line 697 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 106:
#line 703 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setExpr(NodePtr((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = t;
    ;}
    break;

  case 107:
#line 708 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setName(*(yysemantic_stack_[(3) - (1)].string));
      t->setExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 108:
#line 719 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      QualifiedTypeExpr *q = new QualifiedTypeExpr;
      q->setExprs(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = q;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 109:
#line 728 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 110:
#line 732 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 111:
#line 739 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      SpecializedTypeExpr *t = new SpecializedTypeExpr;
      t->setExpr(NodePtr((yysemantic_stack_[(4) - (1)].node)));
      t->setSpecExprs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 112:
#line 748 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 113:
#line 752 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 118:
#line 769 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (1)].structureQualifier); ;}
    break;

  case 119:
#line 770 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(4) - (1)].structureQualifier)->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 120:
#line 777 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("value");
      (yyval.structureQualifier) = s;
    ;}
    break;

  case 121:
#line 782 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("object");
      (yyval.structureQualifier) = s;
    ;}
    break;

  case 122:
#line 790 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); ;}
    break;

  case 123:
#line 791 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); ;}
    break;

  case 124:
#line 795 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(2) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 125:
#line 801 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(3) - (1)].string));
      s->setType(NodePtr((yysemantic_stack_[(3) - (2)].node)));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 126:
#line 812 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      (yyval.node) = i;
    ;}
    break;

  case 127:
#line 816 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      i->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 128:
#line 825 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); ;}
    break;

  case 129:
#line 826 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); ;}
    break;

  case 130:
#line 830 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = new InvalidType; delete (yysemantic_stack_[(1) - (1)].string); /* dummy */ ;}
    break;

  case 131:
#line 835 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NativeQualifier *n = new NativeQualifier;
      n->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 132:
#line 845 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].rangeQualifier); ;}
    break;

  case 133:
#line 846 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMin(*(yysemantic_stack_[(6) - (3)].string));
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMax(*(yysemantic_stack_[(6) - (5)].string));
      delete (yysemantic_stack_[(6) - (3)].string);
      delete (yysemantic_stack_[(6) - (5)].string);
    ;}
    break;

  case 134:
#line 855 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      RangeQualifier *r = new RangeQualifier;
      r->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.rangeQualifier) = r;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 1321 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
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
  const signed char Parser::yypact_ninf_ = -29;
  const short int
  Parser::yypact_[] =
  {
        74,   321,    50,    73,    74,   -29,   -29,    54,   -29,    79,
     -29,   -29,   -29,   -29,   -29,   229,   -29,   -29,   -29,   -29,
      10,   -29,   -29,    89,   280,   311,   437,    19,   132,   -29,
     -29,   -29,   -29,   -29,    35,   -29,   148,    98,   127,   108,
     133,   135,   146,   117,   130,   134,   -29,   -29,   -29,   143,
     175,   179,   167,   -29,   131,   -29,   149,   -29,   -29,   278,
     -29,   -29,   -29,   152,   -29,   -29,   -29,   161,   -29,   240,
     -29,    79,   169,   171,   373,   -29,   437,    66,   -29,   -29,
     -29,   -29,   -29,   173,   172,   -29,   168,    42,   -29,    78,
     -29,   342,   -29,    33,   -29,   109,   -29,   -11,    79,    12,
     450,    19,   -29,   -29,   202,   -29,   148,   148,   148,   148,
     148,   148,   148,   148,   -29,     6,   -29,   -29,   170,   -29,
      72,   181,    79,    79,    79,   -29,     8,   206,   164,   209,
     -29,    76,   -29,   -29,   -29,   437,   437,   196,   -29,   217,
     -29,   404,   437,   -29,    60,   -29,   437,   -29,   -29,   183,
     437,   -29,   -29,   437,   -29,   -29,   450,   194,   -29,    98,
     127,   108,   133,   135,   146,   117,   -29,   -29,     9,   -29,
      79,   -29,   167,   167,   -29,   -10,   192,   192,    15,   -29,
      11,   -29,   189,   260,    95,   -29,   470,   203,   -14,   -29,
      48,   -29,   -29,   168,   -29,   -29,   120,   -29,   -29,   -29,
     417,   -29,   -29,   -29,   -29,   -29,   -29,    79,   -29,   200,
     -29,   -29,   245,    92,   -29,   -29,   450,   450,   437,   437,
     218,   -29,    77,   -29,   -29,   221,   230,   -29,   214,   -29,
     -29,   -29,   450,   437,   -29,   226,   450,   -29
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     0,     2,     4,     5,     0,     6,    21,
      11,    65,    66,    67,    68,     0,    12,    23,     1,     3,
      19,    26,    27,     0,     0,     0,     0,     0,     0,    15,
      52,    31,     7,    44,    63,    69,     0,    71,    73,    75,
      77,    79,    81,    85,    86,     0,    96,   120,   121,     0,
       0,     0,     0,    22,    94,    95,   100,    97,    98,   108,
      99,   109,   114,     0,   115,   116,   117,   132,    13,     0,
      20,    84,     0,     0,     0,    14,     0,     0,    17,    88,
      89,    91,    90,     0,    24,    46,    52,     0,    32,     0,
      37,     0,    48,    92,    51,     0,    92,     0,    19,     0,
       0,     0,     8,    53,     0,    64,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,   131,   134,    96,   106,
       0,     0,     0,     0,     0,   110,     0,     0,    24,     0,
      57,     0,    59,    62,    83,     0,     0,    92,    16,     0,
      25,     0,     0,    30,     0,    35,     0,    47,    49,     0,
       0,    50,    29,     0,    28,     9,     0,    56,    70,    72,
      74,    76,    78,    80,    82,    87,   130,   126,     0,   128,
       0,   103,     0,     0,   112,     0,   101,   102,     0,   118,
       0,   122,     0,     0,    24,    58,     0,     0,     0,    18,
      24,    34,    24,     0,    33,    38,     0,    39,    93,    10,
       0,   127,   129,   107,   105,   104,   111,     0,   124,     0,
     119,   123,     0,    24,    61,    60,     0,     0,     0,     0,
       0,    54,     0,   113,   125,     0,    40,    42,     0,    36,
      55,   133,     0,     0,    41,     0,     0,    43
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
       -29,   -29,   -29,   253,   -29,   -29,   -20,   -29,   -19,   -29,
     -29,   -21,   -29,   150,   -29,   -29,   128,   -29,   -29,   -25,
     -29,   -29,   185,   -29,    90,    91,   -28,    69,   195,   193,
     197,   198,   201,   208,   191,   -29,   -24,   -15,   -29,   281,
      -3,    26,   -29,   -29,   -29,   -29,    -4,   -29,   -29,   -29,
     -29,   262,   -29,   -29,   -29,   142,   -29,   -29,   157,   -29,
     -29,   -29
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     3,     4,     5,     6,     7,    28,    77,    29,     8,
       9,    30,    87,    88,    31,    89,    90,    79,    80,    32,
      33,    91,    92,    34,   131,   132,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    82,    83,    95,
     119,    54,    55,    56,    57,   120,   121,    58,    59,    60,
     175,    61,    62,    63,   180,   181,    64,   168,   169,    65,
      66,    67
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -97;
  const short int
  Parser::yytable_[] =
  {
        81,    93,    96,   102,    86,    78,    53,   100,   105,   166,
      94,   178,   166,    46,   178,    98,   217,    70,    46,   -24,
     -24,   -24,    98,   154,   206,   218,   153,   207,    47,    48,
      49,    50,    51,    47,    48,    49,    50,    51,   167,    69,
     179,   201,    75,   210,    52,   133,   -24,   103,    99,   -24,
      81,   -24,   137,    17,   208,    86,   150,    20,    21,    22,
      11,    12,    13,   192,    21,    22,    14,   149,   134,    23,
      16,   104,   151,    18,   143,   155,    94,   141,   158,   144,
      78,   156,    46,    24,    68,    25,   219,    26,     1,    74,
       2,    76,    71,    26,    27,    70,   138,    47,    48,    49,
      50,    51,   171,   139,   106,    81,   185,   230,    52,   172,
     145,   187,   188,   186,   186,   146,   108,   133,   191,   174,
     189,   141,   196,   193,   141,   -96,   197,   -96,   -96,   198,
     -96,   199,   -96,   170,   107,    84,    21,    22,    11,    12,
      13,   152,   109,   150,    14,   110,   153,    23,   220,   176,
     177,    84,    21,    22,    11,    12,    13,   111,   112,   214,
      14,    74,   133,    25,   122,    26,   123,   203,   204,   205,
     118,   113,   101,   114,   115,   209,   133,    74,   116,    76,
     203,    26,   117,   126,   124,    47,    48,    49,    50,    51,
     127,   226,   227,   141,   228,   214,    52,   -96,   135,   -96,
     136,   141,   183,   140,   223,   157,   142,   234,   170,   235,
     182,   237,   184,    21,    22,    11,    12,    13,   173,   150,
      98,    14,   151,   200,    23,   122,   212,    47,    48,    49,
      50,    51,    72,   216,    73,    11,    12,    13,   129,   224,
      76,    14,    26,   128,    21,    22,    11,    12,    13,   225,
     229,   231,    14,   233,   232,    23,   236,    19,    47,    48,
      49,    50,    51,   213,    21,    22,    11,    12,    13,   129,
     130,    76,    14,    26,   195,    23,   148,   215,    47,    48,
      49,    50,    51,    20,    21,    22,    11,    12,    13,   129,
     222,    76,    14,    26,   194,    23,    47,    48,    49,    50,
      51,   160,   159,    72,   165,    73,   161,    97,   162,    74,
      75,    76,   163,    26,    84,    21,    22,    11,    12,    13,
     164,   125,   211,    14,    10,   202,    23,    11,    12,    13,
       0,     0,     0,    14,    72,     0,    73,     0,    15,     0,
      74,     0,    76,    85,    26,    84,    21,    22,    11,    12,
      13,     0,     0,     0,    14,     0,     0,    23,     0,     0,
       0,     0,     0,     0,     0,    72,     0,    73,     0,     0,
       0,    74,     0,    76,   147,    26,    84,    21,    22,    11,
      12,    13,     0,     0,     0,    14,     0,     0,    23,     0,
       0,     0,     0,     0,     0,     0,    72,     0,    73,     0,
       0,     0,    74,     0,    76,     0,    26,   190,    21,    22,
      11,    12,    13,     0,     0,     0,    14,     0,     0,    23,
     190,    21,    22,    11,    12,    13,     0,     0,     0,    14,
       0,     0,    23,    74,   130,    76,     0,    26,     0,     0,
      84,    21,    22,    11,    12,    13,    74,   221,    76,    14,
      26,     0,    23,    84,    21,    22,    11,    12,    13,     0,
       0,     0,    14,     0,     0,    23,    74,     0,    76,     0,
      26,     0,     0,   190,    21,    22,    11,    12,    13,    74,
       0,    25,    14,    26,     0,    23,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    74,
       0,    76,     0,    26
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        24,    25,    26,    28,    25,    24,     9,    27,    36,     3,
      25,     3,     3,     3,     3,     3,    30,    20,     3,     9,
      10,    11,     3,    34,    34,    39,    37,    37,    18,    19,
      20,    21,    22,    18,    19,    20,    21,    22,    32,    29,
      32,    32,    30,    32,    29,    69,    36,    12,    29,    39,
      74,    41,    76,     3,    39,    76,    23,     3,     4,     5,
       6,     7,     8,     3,     4,     5,    12,    91,    71,    15,
       1,    36,    39,     0,    32,   100,    91,    29,   106,    37,
      99,   101,     3,    29,    15,    31,    38,    33,    14,    29,
      16,    31,     3,    33,    40,    98,    30,    18,    19,    20,
      21,    22,    30,    37,     6,   129,    30,    30,    29,    37,
      32,   135,   136,    37,    37,    37,     8,   141,   142,   122,
     139,    29,   146,   144,    29,    33,   150,    35,    33,   153,
      35,   156,    37,    38,     7,     3,     4,     5,     6,     7,
       8,    32,     9,    23,    12,    10,    37,    15,    28,   123,
     124,     3,     4,     5,     6,     7,     8,    11,    41,   183,
      12,    29,   186,    31,    33,    33,    35,   170,   172,   173,
       3,    41,    40,    39,    31,   178,   200,    29,     3,    31,
     183,    33,     3,    31,    35,    18,    19,    20,    21,    22,
      29,   216,   217,    29,   218,   219,    29,    33,    29,    35,
      29,    29,    38,    30,   207,     3,    38,   232,    38,   233,
       4,   236,     3,     4,     5,     6,     7,     8,    37,    23,
       3,    12,    39,    29,    15,    33,    37,    18,    19,    20,
      21,    22,    23,    30,    25,     6,     7,     8,    29,    39,
      31,    12,    33,     3,     4,     5,     6,     7,     8,     4,
      32,    30,    12,    39,    24,    15,    30,     4,    18,    19,
      20,    21,    22,     3,     4,     5,     6,     7,     8,    29,
      30,    31,    12,    33,   146,    15,    91,   186,    18,    19,
      20,    21,    22,     3,     4,     5,     6,     7,     8,    29,
     200,    31,    12,    33,   144,    15,    18,    19,    20,    21,
      22,   108,   107,    23,   113,    25,   109,    26,   110,    29,
      30,    31,   111,    33,     3,     4,     5,     6,     7,     8,
     112,    59,   180,    12,     3,   168,    15,     6,     7,     8,
      -1,    -1,    -1,    12,    23,    -1,    25,    -1,    17,    -1,
      29,    -1,    31,    32,    33,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    -1,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    25,    -1,    -1,
      -1,    29,    -1,    31,    32,    33,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    -1,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    25,    -1,
      -1,    -1,    29,    -1,    31,    -1,    33,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,    15,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      -1,    -1,    15,    29,    30,    31,    -1,    33,    -1,    -1,
       3,     4,     5,     6,     7,     8,    29,    30,    31,    12,
      33,    -1,    15,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    -1,    -1,    15,    29,    -1,    31,    -1,
      33,    -1,    -1,     3,     4,     5,     6,     7,     8,    29,
      -1,    31,    12,    33,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    31,    -1,    33
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    14,    16,    43,    44,    45,    46,    47,    51,    52,
       3,     6,     7,     8,    12,    17,    69,     3,     0,    45,
       3,     4,     5,    15,    29,    31,    33,    40,    48,    50,
      53,    56,    61,    62,    65,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     3,    18,    19,    20,
      21,    22,    29,    82,    83,    84,    85,    86,    89,    90,
      91,    93,    94,    95,    98,   101,   102,   103,    69,    29,
      82,     3,    23,    25,    29,    30,    31,    49,    50,    59,
      60,    78,    79,    80,     3,    32,    53,    54,    55,    57,
      58,    63,    64,    78,    79,    81,    78,    81,     3,    29,
      48,    40,    61,    12,    36,    68,     6,     7,     8,     9,
      10,    11,    41,    41,    39,    31,     3,     3,     3,    82,
      87,    88,    33,    35,    35,    93,    31,    29,     3,    29,
      30,    66,    67,    78,    82,    29,    29,    78,    30,    37,
      30,    29,    38,    32,    37,    32,    37,    32,    64,    78,
      23,    39,    32,    37,    34,    61,    48,     3,    68,    70,
      71,    72,    73,    74,    75,    76,     3,    32,    99,   100,
      38,    30,    37,    37,    82,    92,    83,    83,     3,    32,
      96,    97,     4,    38,     3,    30,    37,    78,    78,    50,
       3,    78,     3,    53,    55,    58,    78,    78,    78,    61,
      29,    32,   100,    82,    88,    88,    34,    37,    39,    82,
      32,    97,    37,     3,    78,    67,    30,    30,    39,    38,
      28,    30,    66,    82,    39,     4,    61,    61,    78,    32,
      30,    30,    24,    39,    61,    78,    30,    61
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
      50,    51,    51,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    54,    54,    55,    56,    56,    57,    57,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    65,    65,    65,    65,    65,    66,
      66,    67,    67,    68,    68,    69,    69,    69,    69,    70,
      70,    71,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    76,    76,    77,    77,    78,    78,    78,    79,    79,
      80,    80,    81,    81,    82,    82,    83,    83,    83,    83,
      84,    85,    85,    86,    87,    87,    88,    88,    89,    90,
      90,    91,    92,    92,    93,    93,    93,    93,    94,    94,
      95,    95,    96,    96,    97,    97,    98,    98,    99,    99,
     100,   101,   102,   102,   103
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     2,     1,     1,     1,     2,     3,     4,
       5,     2,     2,     3,     2,     1,     3,     1,     3,     1,
       2,     1,     2,     2,     1,     3,     1,     1,     3,     3,
       3,     1,     1,     3,     3,     3,     6,     1,     3,     3,
       5,     7,     5,     9,     1,     2,     2,     3,     1,     2,
       2,     1,     1,     2,     5,     6,     3,     3,     4,     1,
       3,     3,     1,     1,     2,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     2,     1,     1,     3,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     1,     3,     1,     1,
       2,     4,     1,     3,     1,     1,     1,     1,     3,     4,
       1,     1,     1,     2,     2,     3,     3,     4,     1,     2,
       1,     2,     1,     6,     2
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
  "type_decl", "type_decl_name", "primary_expr", "map_expr_pairs",
  "map_expr_pair", "ifcase_expr", "ifcase_expr_conds", "ifcase_expr_cond",
  "if_expr", "for_expr", "body_expr", "block_expr", "block_expr_exprs",
  "block_expr_expr", "postfix_expr", "call_args", "call_arg",
  "prefix_expr", "any_operator", "multiplicative_expr", "additive_expr",
  "relational_expr", "equality_expr", "and_expr", "or_expr",
  "assignment_expr", "var_expr", "expr", "macro_expr", "any_expr",
  "expr_list", "typeexpr", "nonunion_typeexpr", "union_typeexpr",
  "union_typeexprs", "tuple_typeexpr", "tuple_typeexpr_args",
  "tuple_typeexpr_arg", "qualified_typeexpr",
  "qualified_typeexpr_qualifiers", "specialized_typeexpr",
  "specialized_typeexpr_specs", "qualified_typeexpr_qualifier",
  "structure_qualifier", "structure_qualifier_decl",
  "structure_qualifier_stmts", "structure_qualifier_stmt",
  "interface_qualifier", "interface_qualifier_stmts",
  "interface_qualifier_stmt", "native_qualifier", "range_qualifier",
  "range_qualifier_decl", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        43,     0,    -1,    44,    -1,    44,    45,    -1,    45,    -1,
      46,    -1,    51,    -1,    47,    61,    -1,    47,    48,    61,
      -1,    47,    40,    48,    61,    -1,    47,    48,    40,    48,
      61,    -1,    14,     3,    -1,    14,    69,    -1,    14,    17,
      69,    -1,    29,    30,    -1,    50,    -1,    29,    49,    30,
      -1,    50,    -1,    49,    37,    50,    -1,     3,    -1,     3,
      82,    -1,    52,    -1,    52,    82,    -1,    16,     3,    -1,
       3,    -1,    29,    80,    30,    -1,     4,    -1,     5,    -1,
      33,    81,    34,    -1,    31,    81,    32,    -1,    31,    54,
      32,    -1,    56,    -1,    55,    -1,    54,    37,    55,    -1,
      53,    38,    78,    -1,    31,    57,    32,    -1,    31,    57,
      37,    78,    28,    32,    -1,    58,    -1,    57,    37,    58,
      -1,    78,    23,    78,    -1,    23,    29,    78,    30,    61,
      -1,    23,    29,    78,    30,    61,    24,    61,    -1,    25,
      29,    78,    30,    61,    -1,    25,    29,    78,    39,    78,
      39,    78,    30,    61,    -1,    62,    -1,    78,    39,    -1,
      31,    32,    -1,    31,    63,    32,    -1,    64,    -1,    63,
      64,    -1,    78,    39,    -1,    79,    -1,    53,    -1,    65,
      12,    -1,    65,    36,     3,    29,    30,    -1,    65,    36,
       3,    29,    66,    30,    -1,    65,    36,     3,    -1,     3,
      29,    30,    -1,     3,    29,    66,    30,    -1,    67,    -1,
      66,    37,    67,    -1,     3,    38,    78,    -1,    78,    -1,
      65,    -1,    69,    68,    -1,     6,    -1,     7,    -1,     8,
      -1,    12,    -1,    68,    -1,    70,     6,    68,    -1,    70,
      -1,    71,     7,    70,    -1,    71,    -1,    72,     8,    71,
      -1,    72,    -1,    73,     9,    72,    -1,    73,    -1,    74,
      10,    73,    -1,    74,    -1,    75,    11,    74,    -1,    75,
      -1,    76,    41,    75,    -1,    15,     3,    82,    -1,    15,
       3,    -1,    76,    -1,    77,    -1,    77,    41,    76,    -1,
      59,    -1,    60,    -1,    79,    -1,    78,    -1,    78,    -1,
      81,    37,    78,    -1,    83,    -1,    84,    -1,     3,    -1,
      86,    -1,    89,    -1,    91,    -1,    85,    -1,    83,    35,
      83,    -1,    85,    35,    83,    -1,    29,    87,    30,    -1,
      88,    37,    88,    -1,    87,    37,    88,    -1,    82,    -1,
       3,    38,    82,    -1,    90,    -1,    93,    -1,    90,    93,
      -1,    83,    33,    92,    34,    -1,    82,    -1,    92,    37,
      82,    -1,    94,    -1,    98,    -1,   101,    -1,   102,    -1,
      95,    31,    32,    -1,    95,    31,    96,    32,    -1,    18,
      -1,    19,    -1,    97,    -1,    96,    97,    -1,     3,    39,
      -1,     3,    82,    39,    -1,    20,    31,    32,    -1,    20,
      31,    99,    32,    -1,   100,    -1,    99,   100,    -1,     3,
      -1,    21,     3,    -1,   103,    -1,   103,    29,     4,    37,
       4,    30,    -1,    22,     3,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    10,    12,    14,    17,    21,
      26,    32,    35,    38,    42,    45,    47,    51,    53,    57,
      59,    62,    64,    67,    70,    72,    76,    78,    80,    84,
      88,    92,    94,    96,   100,   104,   108,   115,   117,   121,
     125,   131,   139,   145,   155,   157,   160,   163,   167,   169,
     172,   175,   177,   179,   182,   188,   195,   199,   203,   208,
     210,   214,   218,   220,   222,   225,   227,   229,   231,   233,
     235,   239,   241,   245,   247,   251,   253,   257,   259,   263,
     265,   269,   271,   275,   279,   282,   284,   286,   290,   292,
     294,   296,   298,   300,   304,   306,   308,   310,   312,   314,
     316,   318,   322,   326,   330,   334,   338,   340,   344,   346,
     348,   351,   356,   358,   362,   364,   366,   368,   370,   374,
     379,   381,   383,   385,   388,   391,   395,   399,   404,   406,
     409,   411,   414,   416,   423
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   132,   132,   135,   136,   139,   142,   148,   151,   156,
     161,   171,   176,   181,   189,   190,   194,   200,   204,   210,
     216,   227,   228,   236,   267,   273,   274,   280,   286,   292,
     298,   304,   308,   312,   317,   326,   332,   341,   345,   350,
     359,   365,   375,   381,   392,   393,   397,   401,   409,   413,
     418,   419,   423,   424,   432,   439,   448,   455,   461,   472,
     476,   482,   489,   497,   498,   507,   507,   507,   507,   510,
     511,   522,   523,   534,   535,   546,   547,   558,   559,   570,
     571,   582,   583,   592,   599,   608,   609,   610,   618,   619,
     622,   622,   625,   629,   644,   645,   649,   655,   656,   657,
     662,   671,   676,   683,   692,   697,   703,   708,   719,   728,
     732,   739,   748,   752,   761,   762,   763,   764,   769,   770,
     777,   782,   790,   791,   795,   801,   812,   816,   825,   826,
     830,   835,   845,   846,   855
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
  const int Parser::yylast_ = 503;
  const int Parser::yynnts_ = 62;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 18;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 42;

  const unsigned int Parser::yyuser_token_number_max_ = 296;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace driver

#line 863 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
 /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}
