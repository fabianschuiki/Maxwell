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
#line 253 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IdentifierExpr *i = new IdentifierExpr;
      i->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = i;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 25:
#line 259 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); ;}
    break;

  case 26:
#line 260 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
     NumberConstExpr *n = new NumberConstExpr;
     n->setValue(*(yysemantic_stack_[(1) - (1)].string));
     (yyval.node) = n;
     delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 27:
#line 266 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StringConstExpr *s = new StringConstExpr;
      s->setValue(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 28:
#line 272 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* array literals */
      ArrayConstExpr *a = new ArrayConstExpr;
      a->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 29:
#line 278 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* set literals */
      SetConstExpr *s = new SetConstExpr;
      s->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 30:
#line 284 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* map literals */
      MapConstExpr *m = new MapConstExpr;
      m->setPairs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = m;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 32:
#line 294 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 33:
#line 298 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 34:
#line 303 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      MapConstExprPair *p = new MapConstExprPair;
      p->setKey(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      p->setValue(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = p;
    ;}
    break;

  case 35:
#line 312 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 36:
#line 318 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*(yysemantic_stack_[(6) - (2)].nodes));
      i->setOtherwise(NodePtr((yysemantic_stack_[(6) - (4)].node)));
      (yyval.node) = i;
      delete (yysemantic_stack_[(6) - (2)].nodes);
    ;}
    break;

  case 37:
#line 327 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 38:
#line 331 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 39:
#line 336 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExprCond *c = new IfCaseExprCond;
      c->setExpr(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      c->setCond(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = c;
    ;}
    break;

  case 40:
#line 345 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfExpr *s = new IfExpr;
      s->setCond(NodePtr((yysemantic_stack_[(5) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 41:
#line 351 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfExpr *s = new IfExpr;
      s->setCond(NodePtr((yysemantic_stack_[(7) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(7) - (5)].node)));
      s->setElseExpr(NodePtr((yysemantic_stack_[(7) - (7)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 42:
#line 361 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      ForExpr *s = new ForExpr;
      s->setCond(NodePtr((yysemantic_stack_[(5) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 43:
#line 367 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 383 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BlockExpr *b = new BlockExpr;
      (yyval.node) = b;
    ;}
    break;

  case 47:
#line 387 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BlockExpr *b = new BlockExpr;
      b->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = b;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 48:
#line 395 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 49:
#line 399 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 53:
#line 410 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 418 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(5) - (3)].string));
      c->setContext(NodePtr((yysemantic_stack_[(5) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(5) - (3)].string);
    ;}
    break;

  case 55:
#line 425 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 434 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (3)].string));
      c->setContext(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (3)].string);
    ;}
    break;

  case 57:
#line 441 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (1)].string));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 58:
#line 447 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 458 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 60:
#line 462 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 61:
#line 468 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setName(*(yysemantic_stack_[(3) - (1)].string));
      a->setExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 62:
#line 475 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setExpr(NodePtr((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = a;
    ;}
    break;

  case 64:
#line 484 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 497 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 509 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 521 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 533 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 545 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 557 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 569 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      AssignmentExpr *e = new AssignmentExpr;
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
    ;}
    break;

  case 83:
#line 578 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*(yysemantic_stack_[(3) - (2)].string));
      v->setTypeExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.varDefExpr) = v;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 84:
#line 585 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.varDefExpr) = v;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 86:
#line 595 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); ;}
    break;

  case 87:
#line 596 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].varDefExpr)->setInitialExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 92:
#line 611 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 93:
#line 615 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 96:
#line 635 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NamedTypeExpr *n = new NamedTypeExpr;
      n->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 97:
#line 641 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.node) = new NilTypeExpr;
    ;}
    break;

  case 101:
#line 651 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnionTypeExpr *t = new UnionTypeExpr;
      t->setTypes(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 102:
#line 660 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 103:
#line 665 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 104:
#line 672 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExpr *t = new TupleTypeExpr;
      t->setArgs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 105:
#line 681 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 106:
#line 686 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 107:
#line 692 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setExpr(NodePtr((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = t;
    ;}
    break;

  case 108:
#line 697 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setName(*(yysemantic_stack_[(3) - (1)].string));
      t->setExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 109:
#line 708 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      QualifiedTypeExpr *q = new QualifiedTypeExpr;
      q->setExprs(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = q;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 110:
#line 717 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 111:
#line 721 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 112:
#line 728 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      SpecializedTypeExpr *t = new SpecializedTypeExpr;
      t->setExpr(NodePtr((yysemantic_stack_[(4) - (1)].node)));
      t->setSpecExprs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 113:
#line 737 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 114:
#line 741 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 119:
#line 758 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (1)].structureQualifier); ;}
    break;

  case 120:
#line 759 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(4) - (1)].structureQualifier)->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 121:
#line 766 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("value");
      (yyval.structureQualifier) = s;
    ;}
    break;

  case 122:
#line 771 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("object");
      (yyval.structureQualifier) = s;
    ;}
    break;

  case 123:
#line 779 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); ;}
    break;

  case 124:
#line 780 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); ;}
    break;

  case 125:
#line 784 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(2) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 126:
#line 790 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(3) - (1)].string));
      s->setType(NodePtr((yysemantic_stack_[(3) - (2)].node)));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 127:
#line 801 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      (yyval.node) = i;
    ;}
    break;

  case 128:
#line 805 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      i->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 129:
#line 814 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); ;}
    break;

  case 130:
#line 815 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); ;}
    break;

  case 131:
#line 819 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = new InvalidType; delete (yysemantic_stack_[(1) - (1)].string); /* dummy */ ;}
    break;

  case 132:
#line 824 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NativeQualifier *n = new NativeQualifier;
      n->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 133:
#line 834 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].rangeQualifier); ;}
    break;

  case 134:
#line 835 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMin(*(yysemantic_stack_[(6) - (3)].string));
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMax(*(yysemantic_stack_[(6) - (5)].string));
      delete (yysemantic_stack_[(6) - (3)].string);
      delete (yysemantic_stack_[(6) - (5)].string);
    ;}
    break;

  case 135:
#line 844 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      RangeQualifier *r = new RangeQualifier;
      r->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.rangeQualifier) = r;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 1328 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
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
  const short int Parser::yypact_ninf_ = -186;
  const short int
  Parser::yypact_[] =
  {
        47,    94,    28,    62,    47,  -186,  -186,     3,  -186,   259,
    -186,  -186,  -186,  -186,  -186,   174,  -186,  -186,  -186,  -186,
     259,    11,    45,    52,   -18,  -186,  -186,  -186,  -186,  -186,
      48,    91,   101,  -186,   272,  -186,    38,  -186,    73,  -186,
    -186,   284,  -186,  -186,  -186,    79,  -186,  -186,  -186,    85,
    -186,  -186,  -186,    68,  -186,    89,  -186,  -186,   117,   118,
     119,   154,   202,  -186,   202,  -186,  -186,  -186,  -186,    84,
    -186,    57,  -186,   253,   115,   149,   155,   156,   158,   160,
     132,   133,   137,  -186,   157,    52,  -186,     5,  -186,  -186,
     151,  -186,    82,   161,   259,   259,   259,  -186,    12,   187,
    -186,   196,   120,   259,   202,   202,  -186,  -186,   170,   164,
      99,  -186,   105,  -186,   188,   108,  -186,   -17,  -186,  -186,
    -186,   209,  -186,   253,   253,   253,   253,   253,   253,   253,
     253,  -186,  -186,   157,  -186,  -186,    27,  -186,   259,  -186,
     272,   272,  -186,   130,   180,   180,     7,  -186,    32,  -186,
     178,  -186,    29,  -186,    92,  -186,  -186,  -186,   186,    36,
    -186,   202,  -186,   241,  -186,   202,   202,  -186,   202,  -186,
     192,  -186,   115,   149,   155,   156,   158,   160,   132,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,   259,  -186,   184,  -186,
    -186,   220,   202,  -186,   222,   235,   235,   202,  -186,  -186,
     164,  -186,  -186,    -7,  -186,  -186,   189,  -186,  -186,   206,
    -186,  -186,    45,   208,  -186,   210,  -186,   213,   216,  -186,
     104,  -186,    33,   235,  -186,   202,  -186,  -186,  -186,   224,
     235,  -186
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     0,     2,     4,     5,     0,     6,    21,
      11,    65,    66,    67,    68,     0,    12,    23,     1,     3,
      19,     0,     0,     0,     0,    15,     7,    96,   121,   122,
       0,     0,     0,    97,     0,    22,    94,    95,   101,    98,
      99,   109,   100,   110,   115,     0,   116,   117,   118,   133,
      13,    20,    14,     0,    17,    24,    26,    27,     0,     0,
       0,     0,     0,    46,     0,    52,    31,    88,    89,     0,
      48,    63,    69,     0,    71,    73,    75,    77,    79,    81,
      85,    86,     0,    51,     0,     0,     8,     0,   132,   135,
      96,   107,     0,     0,     0,     0,     0,   111,     0,     0,
      16,     0,     0,    84,     0,     0,    91,    90,     0,    52,
       0,    32,     0,    37,    92,     0,    92,     0,    47,    49,
      53,     0,    64,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     9,     0,   131,   127,     0,   129,     0,   104,
       0,     0,   113,     0,   102,   103,     0,   119,     0,   123,
       0,    18,    24,    57,     0,    59,    62,    83,     0,     0,
      25,     0,    30,     0,    35,     0,     0,    29,     0,    28,
      56,    70,    72,    74,    76,    78,    80,    82,    87,    10,
     128,   130,   108,   106,   105,   112,     0,   125,     0,   120,
     124,     0,     0,    58,     0,     0,     0,     0,    34,    24,
       0,    33,    38,     0,    39,    93,     0,   114,   126,     0,
      61,    60,     0,    40,    44,     0,    42,     0,     0,    54,
       0,   134,    92,     0,    45,     0,    36,    55,    41,     0,
       0,    43
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -186,  -186,  -186,   263,  -186,  -186,   -20,  -186,   -16,  -186,
    -186,   -60,  -186,   100,  -186,  -186,   106,  -186,  -186,  -185,
       0,  -186,   200,  -186,    67,    93,   -69,     8,   152,   171,
     163,   168,   169,   179,   153,  -186,   -22,   238,  -186,   236,
      -8,   -77,  -186,  -186,  -186,  -186,    14,  -186,  -186,  -186,
    -186,   266,  -186,  -186,  -186,   162,  -186,  -186,   173,  -186,
    -186,  -186
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     3,     4,     5,     6,     7,    24,    53,    25,     8,
       9,    65,   110,   111,    66,   112,   113,    67,    68,   213,
     214,    69,    70,    71,   154,   155,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,   215,    83,   108,   115,
      91,    36,    37,    38,    39,    92,    93,    40,    41,    42,
     143,    43,    44,    45,   148,   149,    46,   136,   137,    47,
      48,    49
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        82,    35,   109,    84,   122,    54,    20,    26,   134,    16,
      27,   216,    51,    22,    20,   146,   166,   169,   144,   145,
     168,   218,    85,    50,    86,    28,    29,    30,    31,    32,
     134,    17,    21,    33,    22,   146,    34,   135,   228,   106,
     114,    52,   116,    23,   147,   231,   187,    82,    55,    56,
      57,    11,    12,    13,   171,    20,   166,    14,   102,   180,
      58,     1,    18,     2,   189,   133,   196,   192,    59,   120,
      60,    94,   131,    95,    61,   197,    62,    63,    64,    87,
     156,    21,   158,   159,   132,   151,   142,    55,    56,    57,
      11,    12,    13,   121,    88,   157,    14,    10,   100,    58,
      11,    12,    13,   200,    89,   101,    14,    59,    96,    60,
      98,    15,   139,    61,    99,    62,   118,    64,   102,   140,
     103,   123,   193,   152,    56,    57,    11,    12,    13,   194,
     182,   162,    14,   179,   227,    58,   163,   164,   188,   198,
     167,   194,   165,   203,   204,   168,   205,   104,   105,    61,
     153,    62,   109,    64,   183,   184,   124,    55,    56,    57,
      11,    12,    13,   125,   185,   126,    14,   186,   127,    58,
     210,   128,   156,   129,   130,   217,   131,    59,   207,    60,
      11,    12,    13,    61,   156,    62,    14,    64,    22,   138,
     222,   150,   152,    56,    57,    11,    12,    13,   141,    20,
     160,    14,   161,   229,    58,    55,    56,    57,    11,    12,
      13,   166,   170,    94,    14,   191,   195,    58,    61,   219,
      62,   206,    64,   208,   209,   152,    56,    57,    11,    12,
      13,    61,   223,    62,    14,    64,   221,    58,    55,    56,
      57,    11,    12,    13,   199,    56,    57,    14,   226,   224,
      58,    61,   225,    62,   230,    64,    55,    56,    57,    11,
      12,    13,    27,   201,    61,    14,   212,    19,    64,   119,
      61,   202,    62,   220,    64,    90,   172,    28,    29,    30,
      31,    32,    61,   178,    62,    33,    64,   211,    34,   174,
      28,    29,    30,    31,    32,   175,   173,   176,    33,   107,
     117,    34,    28,    29,    30,    31,    32,    97,   177,   181,
     190
  };

  /* YYCHECK.  */
  const unsigned char
  Parser::yycheck_[] =
  {
        22,     9,    62,    23,    73,    21,     3,     7,     3,     1,
       3,   196,    20,    31,     3,     3,    23,    34,    95,    96,
      37,    28,    40,    15,    24,    18,    19,    20,    21,    22,
       3,     3,    29,    26,    31,     3,    29,    32,   223,    61,
      62,    30,    64,    40,    32,   230,    39,    69,     3,     4,
       5,     6,     7,     8,   123,     3,    23,    12,    29,    32,
      15,    14,     0,    16,    32,    85,    30,    38,    23,    12,
      25,    33,    39,    35,    29,    39,    31,    32,    33,    31,
     102,    29,   104,   105,    84,   101,    94,     3,     4,     5,
       6,     7,     8,    36,     3,   103,    12,     3,    30,    15,
       6,     7,     8,   163,     3,    37,    12,    23,    35,    25,
      31,    17,    30,    29,    29,    31,    32,    33,    29,    37,
       3,     6,    30,     3,     4,     5,     6,     7,     8,    37,
     138,    32,    12,   133,    30,    15,    37,    32,   146,   161,
      32,    37,    37,   165,   166,    37,   168,    29,    29,    29,
      30,    31,   212,    33,   140,   141,     7,     3,     4,     5,
       6,     7,     8,     8,    34,     9,    12,    37,    10,    15,
     192,    11,   194,    41,    41,   197,    39,    23,   186,    25,
       6,     7,     8,    29,   206,    31,    12,    33,    31,    38,
     212,     4,     3,     4,     5,     6,     7,     8,    37,     3,
      30,    12,    38,   225,    15,     3,     4,     5,     6,     7,
       8,    23,     3,    33,    12,    37,    30,    15,    29,    30,
      31,    29,    33,    39,     4,     3,     4,     5,     6,     7,
       8,    29,    24,    31,    12,    33,    30,    15,     3,     4,
       5,     6,     7,     8,     3,     4,     5,    12,    32,    39,
      15,    29,    39,    31,    30,    33,     3,     4,     5,     6,
       7,     8,     3,   163,    29,    12,    31,     4,    33,    69,
      29,   165,    31,   206,    33,     3,   124,    18,    19,    20,
      21,    22,    29,   130,    31,    26,    33,   194,    29,   126,
      18,    19,    20,    21,    22,   127,   125,   128,    26,    61,
      64,    29,    18,    19,    20,    21,    22,    41,   129,   136,
     148
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    14,    16,    43,    44,    45,    46,    47,    51,    52,
       3,     6,     7,     8,    12,    17,    69,     3,     0,    45,
       3,    29,    31,    40,    48,    50,    62,     3,    18,    19,
      20,    21,    22,    26,    29,    82,    83,    84,    85,    86,
      89,    90,    91,    93,    94,    95,    98,   101,   102,   103,
      69,    82,    30,    49,    50,     3,     4,     5,    15,    23,
      25,    29,    31,    32,    33,    53,    56,    59,    60,    63,
      64,    65,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    48,    40,    62,    31,     3,     3,
       3,    82,    87,    88,    33,    35,    35,    93,    31,    29,
      30,    37,    29,     3,    29,    29,    78,    79,    80,    53,
      54,    55,    57,    58,    78,    81,    78,    81,    32,    64,
      12,    36,    68,     6,     7,     8,     9,    10,    11,    41,
      41,    39,    62,    48,     3,    32,    99,   100,    38,    30,
      37,    37,    82,    92,    83,    83,     3,    32,    96,    97,
       4,    50,     3,    30,    66,    67,    78,    82,    78,    78,
      30,    38,    32,    37,    32,    37,    23,    32,    37,    34,
       3,    68,    70,    71,    72,    73,    74,    75,    76,    62,
      32,   100,    82,    88,    88,    34,    37,    39,    82,    32,
      97,    37,    38,    30,    37,    30,    30,    39,    78,     3,
      53,    55,    58,    78,    78,    78,    29,    82,    39,     4,
      78,    67,    31,    61,    62,    78,    61,    78,    28,    30,
      66,    30,    78,    24,    39,    39,    32,    30,    61,    78,
      30,    61
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
      83,    84,    85,    85,    86,    87,    87,    88,    88,    89,
      90,    90,    91,    92,    92,    93,    93,    93,    93,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    99,
      99,   100,   101,   102,   102,   103
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
       1,     1,     3,     3,     3,     3,     3,     1,     3,     1,
       1,     2,     4,     1,     3,     1,     1,     1,     1,     3,
       4,     1,     1,     1,     2,     2,     3,     3,     4,     1,
       2,     1,     2,     1,     6,     2
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
      46,    -1,    51,    -1,    47,    62,    -1,    47,    48,    62,
      -1,    47,    40,    48,    62,    -1,    47,    48,    40,    48,
      62,    -1,    14,     3,    -1,    14,    69,    -1,    14,    17,
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
      26,    -1,    86,    -1,    89,    -1,    91,    -1,    85,    -1,
      83,    35,    83,    -1,    85,    35,    83,    -1,    29,    87,
      30,    -1,    88,    37,    88,    -1,    87,    37,    88,    -1,
      82,    -1,     3,    38,    82,    -1,    90,    -1,    93,    -1,
      90,    93,    -1,    83,    33,    92,    34,    -1,    82,    -1,
      92,    37,    82,    -1,    94,    -1,    98,    -1,   101,    -1,
     102,    -1,    95,    31,    32,    -1,    95,    31,    96,    32,
      -1,    18,    -1,    19,    -1,    97,    -1,    96,    97,    -1,
       3,    39,    -1,     3,    82,    39,    -1,    20,    31,    32,
      -1,    20,    31,    99,    32,    -1,   100,    -1,    99,   100,
      -1,     3,    -1,    21,     3,    -1,   103,    -1,   103,    29,
       4,    37,     4,    30,    -1,    22,     3,    -1
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
     316,   318,   320,   324,   328,   332,   336,   340,   342,   346,
     348,   350,   353,   358,   360,   364,   366,   368,   370,   372,
     376,   381,   383,   385,   387,   390,   393,   397,   401,   406,
     408,   411,   413,   416,   418,   425
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   132,   132,   135,   136,   139,   142,   148,   151,   156,
     161,   171,   176,   181,   189,   190,   194,   200,   204,   210,
     216,   227,   228,   236,   253,   259,   260,   266,   272,   278,
     284,   290,   294,   298,   303,   312,   318,   327,   331,   336,
     345,   351,   361,   367,   378,   379,   383,   387,   395,   399,
     404,   405,   409,   410,   418,   425,   434,   441,   447,   458,
     462,   468,   475,   483,   484,   493,   493,   493,   493,   496,
     497,   508,   509,   520,   521,   532,   533,   544,   545,   556,
     557,   568,   569,   578,   585,   594,   595,   596,   604,   605,
     608,   608,   611,   615,   630,   631,   635,   641,   644,   645,
     646,   651,   660,   665,   672,   681,   686,   692,   697,   708,
     717,   721,   728,   737,   741,   750,   751,   752,   753,   758,
     759,   766,   771,   779,   780,   784,   790,   801,   805,   814,
     815,   819,   824,   834,   835,   844
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
  const int Parser::yylast_ = 310;
  const int Parser::yynnts_ = 62;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 18;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 42;

  const unsigned int Parser::yyuser_token_number_max_ = 296;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace driver

#line 852 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
 /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}
