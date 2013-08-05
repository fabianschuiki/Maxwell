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
#line 149 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].funcDef)->setBody(NodePtr((yysemantic_stack_[(2) - (2)].node)));
      (yysemantic_stack_[(2) - (1)].funcDef)->setImplOut(false);
    ;}
    break;

  case 8:
#line 153 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].funcDef)->setBody(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yysemantic_stack_[(3) - (1)].funcDef)->setImplOut(true);
    ;}
    break;

  case 10:
#line 161 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].funcDef)->setIn(*(yysemantic_stack_[(2) - (2)].nodes));
      delete (yysemantic_stack_[(2) - (2)].nodes);
    ;}
    break;

  case 11:
#line 165 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].funcDef)->setOut(*(yysemantic_stack_[(3) - (3)].nodes));
      delete (yysemantic_stack_[(3) - (3)].nodes);
    ;}
    break;

  case 12:
#line 169 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(4) - (1)].funcDef)->setIn(*(yysemantic_stack_[(4) - (2)].nodes));
      (yysemantic_stack_[(4) - (1)].funcDef)->setOut(*(yysemantic_stack_[(4) - (4)].nodes));
      delete (yysemantic_stack_[(4) - (2)].nodes);
      delete (yysemantic_stack_[(4) - (4)].nodes);
     ;}
    break;

  case 13:
#line 178 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName(*(yysemantic_stack_[(2) - (2)].string)); delete (yysemantic_stack_[(2) - (2)].string);
      (yyval.funcDef) = d;
    ;}
    break;

  case 14:
#line 183 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName(*(yysemantic_stack_[(2) - (2)].string)); delete (yysemantic_stack_[(2) - (2)].string);
      (yyval.funcDef) = d;
    ;}
    break;

  case 15:
#line 188 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName("_" + *(yysemantic_stack_[(3) - (3)].string)); delete (yysemantic_stack_[(3) - (3)].string);
      (yyval.funcDef) = d;
    ;}
    break;

  case 16:
#line 196 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; ;}
    break;

  case 17:
#line 197 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 18:
#line 201 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 19:
#line 207 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 20:
#line 211 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 21:
#line 217 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncArg *a = new FuncArg;
      a->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = a;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 22:
#line 223 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncArg *a = new FuncArg;
      a->setName(*(yysemantic_stack_[(2) - (1)].string));
      a->setTypeExpr(NodePtr((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 23:
#line 234 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].typeDef); ;}
    break;

  case 24:
#line 235 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].typeDef)->setType(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 25:
#line 243 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TypeDef *t = new TypeDef;
      t->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.typeDef) = t;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 26:
#line 260 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IdentifierExpr *i = new IdentifierExpr;
      i->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = i;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 27:
#line 266 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); ;}
    break;

  case 28:
#line 267 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
     NumberConstExpr *n = new NumberConstExpr;
     n->setValue(*(yysemantic_stack_[(1) - (1)].string));
     (yyval.node) = n;
     delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 29:
#line 273 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StringConstExpr *s = new StringConstExpr;
      s->setValue(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 30:
#line 279 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* array literals */
      ArrayConstExpr *a = new ArrayConstExpr;
      a->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 31:
#line 285 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* set literals */
      SetConstExpr *s = new SetConstExpr;
      s->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 32:
#line 291 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { /* map literals */
      MapConstExpr *m = new MapConstExpr;
      m->setPairs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = m;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 34:
#line 301 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 35:
#line 305 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 36:
#line 310 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      MapConstExprPair *p = new MapConstExprPair;
      p->setKey(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      p->setValue(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = p;
    ;}
    break;

  case 37:
#line 319 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 38:
#line 325 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*(yysemantic_stack_[(6) - (2)].nodes));
      i->setOtherwise(NodePtr((yysemantic_stack_[(6) - (4)].node)));
      (yyval.node) = i;
      delete (yysemantic_stack_[(6) - (2)].nodes);
    ;}
    break;

  case 39:
#line 334 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 40:
#line 338 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 41:
#line 343 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExprCond *c = new IfCaseExprCond;
      c->setExpr(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      c->setCond(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = c;
    ;}
    break;

  case 42:
#line 352 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfExpr *s = new IfExpr;
      s->setCond(NodePtr((yysemantic_stack_[(5) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 43:
#line 358 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfExpr *s = new IfExpr;
      s->setCond(NodePtr((yysemantic_stack_[(7) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(7) - (5)].node)));
      s->setElseExpr(NodePtr((yysemantic_stack_[(7) - (7)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 44:
#line 368 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      ForExpr *s = new ForExpr;
      s->setCond(NodePtr((yysemantic_stack_[(5) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 45:
#line 374 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      ForExpr *s = new ForExpr;
      s->setInit(NodePtr((yysemantic_stack_[(9) - (3)].node)));
      s->setCond(NodePtr((yysemantic_stack_[(9) - (5)].node)));
      s->setStep(NodePtr((yysemantic_stack_[(9) - (7)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(9) - (9)].node)));
      (yyval.node) = s;
    ;}
    break;

  case 48:
#line 390 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BlockExpr *b = new BlockExpr;
      (yyval.node) = b;
    ;}
    break;

  case 49:
#line 394 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BlockExpr *b = new BlockExpr;
      b->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = b;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 50:
#line 402 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 51:
#line 406 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 55:
#line 417 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(true);
      u->setOperatorName(*(yysemantic_stack_[(2) - (2)].string));
      u->setExpr(NodePtr((yysemantic_stack_[(2) - (1)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 56:
#line 425 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(5) - (3)].string));
      c->setContext(NodePtr((yysemantic_stack_[(5) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(5) - (3)].string);
    ;}
    break;

  case 57:
#line 432 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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

  case 58:
#line 441 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (3)].string));
      c->setContext(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (3)].string);
    ;}
    break;

  case 59:
#line 448 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (1)].string));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 60:
#line 454 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(4) - (1)].string));
      c->setArgs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = c;
      delete (yysemantic_stack_[(4) - (1)].string);
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 61:
#line 465 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 62:
#line 469 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 63:
#line 475 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setName(*(yysemantic_stack_[(3) - (1)].string));
      a->setExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 64:
#line 482 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setExpr(NodePtr((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = a;
    ;}
    break;

  case 66:
#line 491 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(false);
      u->setOperatorName(*(yysemantic_stack_[(2) - (1)].string));
      u->setExpr(NodePtr((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 72:
#line 504 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 516 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 528 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 540 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 552 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 564 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 84:
#line 576 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      AssignmentExpr *e = new AssignmentExpr;
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
    ;}
    break;

  case 85:
#line 585 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*(yysemantic_stack_[(3) - (2)].string));
      v->setTypeExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.varDefExpr) = v;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 86:
#line 592 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.varDefExpr) = v;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 88:
#line 602 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); ;}
    break;

  case 89:
#line 603 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].varDefExpr)->setInitialExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 94:
#line 618 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 95:
#line 622 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 98:
#line 642 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NamedTypeExpr *n = new NamedTypeExpr;
      n->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 99:
#line 648 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.node) = new NilTypeExpr;
    ;}
    break;

  case 103:
#line 658 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnionTypeExpr *t = new UnionTypeExpr;
      t->setTypes(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 104:
#line 667 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 105:
#line 672 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 106:
#line 679 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExpr *t = new TupleTypeExpr;
      t->setArgs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 107:
#line 688 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 108:
#line 692 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 109:
#line 698 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setExpr(NodePtr((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = t;
    ;}
    break;

  case 110:
#line 703 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setName(*(yysemantic_stack_[(3) - (1)].string));
      t->setExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 111:
#line 714 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      QualifiedTypeExpr *q = new QualifiedTypeExpr;
      q->setExprs(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = q;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 112:
#line 723 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 113:
#line 727 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 114:
#line 734 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      SpecializedTypeExpr *t = new SpecializedTypeExpr;
      t->setExpr(NodePtr((yysemantic_stack_[(4) - (1)].node)));
      t->setSpecExprs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 115:
#line 743 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 116:
#line 747 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 121:
#line 764 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (1)].structureQualifier); ;}
    break;

  case 122:
#line 765 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(4) - (1)].structureQualifier)->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 123:
#line 772 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("value");
      (yyval.structureQualifier) = s;
    ;}
    break;

  case 124:
#line 777 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("object");
      (yyval.structureQualifier) = s;
    ;}
    break;

  case 125:
#line 785 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); ;}
    break;

  case 126:
#line 786 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); ;}
    break;

  case 127:
#line 790 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(2) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 128:
#line 796 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(3) - (1)].string));
      s->setType(NodePtr((yysemantic_stack_[(3) - (2)].node)));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 129:
#line 807 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      (yyval.node) = i;
    ;}
    break;

  case 130:
#line 811 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      i->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 131:
#line 820 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); ;}
    break;

  case 132:
#line 821 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); ;}
    break;

  case 133:
#line 825 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = new InvalidType; delete (yysemantic_stack_[(1) - (1)].string); /* dummy */ ;}
    break;

  case 134:
#line 830 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NativeQualifier *n = new NativeQualifier;
      n->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 135:
#line 840 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].rangeQualifier); ;}
    break;

  case 136:
#line 841 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMin(*(yysemantic_stack_[(6) - (3)].string));
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMax(*(yysemantic_stack_[(6) - (5)].string));
      delete (yysemantic_stack_[(6) - (3)].string);
      delete (yysemantic_stack_[(6) - (5)].string);
    ;}
    break;

  case 137:
#line 850 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      RangeQualifier *r = new RangeQualifier;
      r->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.rangeQualifier) = r;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 1333 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
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
  const short int Parser::yypact_ninf_ = -187;
  const short int
  Parser::yypact_[] =
  {
       102,   294,     7,    40,   102,  -187,  -187,   -10,     3,  -187,
     258,  -187,  -187,  -187,  -187,  -187,   131,  -187,  -187,  -187,
    -187,    47,   121,  -187,   258,    14,     4,   -18,  -187,  -187,
    -187,  -187,    58,    60,    82,  -187,   270,  -187,   112,  -187,
      73,  -187,  -187,   150,  -187,  -187,  -187,    68,  -187,  -187,
    -187,    83,  -187,   111,  -187,  -187,   138,   117,   124,   152,
     219,  -187,   219,  -187,  -187,  -187,  -187,    88,  -187,    45,
    -187,   252,   125,   154,   155,   157,   163,   167,   141,   143,
     147,  -187,    47,  -187,  -187,   148,  -187,  -187,    28,  -187,
    -187,     4,    13,  -187,  -187,   158,  -187,    36,  -187,   258,
     258,   258,  -187,    16,   191,   186,   258,   219,   219,  -187,
    -187,   169,   159,    51,  -187,    70,  -187,   177,    77,  -187,
      64,  -187,  -187,  -187,   200,  -187,   252,   252,   252,   252,
     252,   252,   252,   252,  -187,   -15,  -187,  -187,   201,  -187,
    -187,  -187,    17,  -187,   258,  -187,   270,  -187,   128,   172,
     172,     8,  -187,    32,  -187,   170,   -20,  -187,    37,  -187,
    -187,  -187,   176,   -16,  -187,   219,  -187,   101,  -187,   219,
     219,  -187,   219,  -187,   179,  -187,   125,   154,   155,   157,
     163,   167,   141,  -187,  -187,  -187,  -187,  -187,  -187,   258,
    -187,   181,  -187,  -187,   224,   219,  -187,   239,   121,   121,
     219,  -187,  -187,   159,  -187,  -187,    54,  -187,  -187,   206,
    -187,  -187,   199,  -187,  -187,   208,  -187,   194,   198,  -187,
      38,  -187,   121,   219,  -187,  -187,  -187,   210,   121,  -187
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     0,     2,     4,     5,     0,     9,     6,
      23,    13,    67,    68,    69,    70,     0,    14,    25,     1,
       3,     0,     0,     7,    21,     0,     0,    10,    17,    98,
     123,   124,     0,     0,     0,    99,     0,    24,    96,    97,
     103,   100,   101,   111,   102,   112,   117,     0,   118,   119,
     120,   135,    15,    26,    28,    29,     0,     0,     0,     0,
       0,    48,     0,    54,    33,    90,    91,     0,    50,    65,
      71,     0,    73,    75,    77,    79,    81,    83,    87,    88,
       0,    53,     0,     8,    46,     0,    22,    16,     0,    19,
      11,     0,     0,   134,   137,    98,   109,     0,   107,     0,
       0,     0,   113,     0,     0,     0,    86,     0,     0,    93,
      92,     0,    54,     0,    34,     0,    39,    94,     0,    94,
       0,    49,    51,    55,     0,    66,     0,     0,     0,     0,
       0,     0,     0,     0,    52,    94,    47,    18,     0,    12,
     133,   129,     0,   131,     0,   106,     0,   115,     0,   104,
     105,     0,   121,     0,   125,     0,    26,    59,     0,    61,
      64,    85,     0,     0,    27,     0,    32,     0,    37,     0,
       0,    31,     0,    30,    58,    72,    74,    76,    78,    80,
      82,    84,    89,    20,   130,   132,   110,   108,   114,     0,
     127,     0,   122,   126,     0,     0,    60,     0,     0,     0,
       0,    36,    26,     0,    35,    40,     0,    41,    95,     0,
     116,   128,     0,    63,    62,    42,    44,     0,     0,    56,
       0,   136,     0,     0,    38,    57,    43,     0,     0,    45
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -187,  -187,  -187,   234,  -187,  -187,  -187,   -22,  -187,   -23,
    -187,  -187,   -57,  -187,    74,  -187,  -187,    80,  -187,  -187,
    -186,   246,  -187,   195,  -187,    56,    66,   -66,    55,   139,
     146,   140,   137,   144,   161,   149,  -187,   -21,   212,  -187,
     232,    -9,    22,  -187,  -187,  -187,  -187,   162,  -187,  -187,
    -187,  -187,   243,  -187,  -187,  -187,   142,  -187,  -187,   156,
    -187,  -187,  -187
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     3,     4,     5,     6,     7,     8,    27,    88,    28,
       9,    10,    63,   113,   114,    64,   115,   116,    65,    66,
      83,    84,    67,    68,    69,   158,   159,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    85,    81,   111,
     118,    96,    38,    39,    40,    41,    97,    98,    42,    43,
      44,   148,    45,    46,    47,   153,   154,    48,   142,   143,
      49,    50,    51
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        80,    37,    89,   112,    90,   125,    24,    24,   170,   105,
      18,    29,   215,   216,   199,    86,   140,    24,   195,   151,
     140,    21,    91,   200,   134,   112,    30,    31,    32,    33,
      34,    22,    25,    25,    35,   151,   226,    36,   109,   117,
      19,   119,   229,    26,    87,   141,    80,   190,   152,   184,
      53,    54,    55,    12,    13,    14,    17,   123,   137,    15,
     175,   135,    56,    93,   192,   138,   145,   196,   225,   139,
      57,    52,    58,   146,   197,   197,    59,   170,    60,    61,
      62,   124,   218,   166,   160,    94,   162,   163,   167,    92,
     147,    53,    54,    55,    12,    13,    14,   161,   173,   103,
      15,   172,   168,    56,   202,    54,    55,   169,   101,   171,
     203,    57,   104,    58,   172,   183,     1,    59,     2,    60,
     121,    62,   149,   150,    53,    54,    55,    12,    13,    14,
      59,   126,    60,    15,    62,   186,    56,    12,    13,    14,
     105,   106,   191,    15,   201,    99,   107,   100,   206,   207,
      59,   208,    82,   108,    62,    53,    54,    55,    12,    13,
      14,   127,   188,   128,    15,   189,   129,    56,    30,    31,
      32,    33,    34,   130,   213,    57,   160,    58,   131,   217,
     210,    59,   132,    60,   133,    62,   134,   136,   160,   156,
      54,    55,    12,    13,    14,   155,   144,   165,    15,   164,
     170,    56,   227,   174,    24,    99,   198,   194,   209,   156,
      54,    55,    12,    13,    14,    59,   157,    60,    15,    62,
     211,    56,    53,    54,    55,    12,    13,    14,   212,   221,
     224,    15,   222,   223,    56,    59,   219,    60,    20,    62,
     228,   204,   156,    54,    55,    12,    13,    14,    59,   205,
      60,    15,    62,    23,    56,    53,    54,    55,    12,    13,
      14,    29,   122,   214,    15,   220,   176,   179,    59,   178,
      60,   110,    62,    95,   177,   180,    30,    31,    32,    33,
      34,    59,   182,    60,    35,    62,   102,    36,    30,    31,
      32,    33,    34,   181,   120,   193,    35,    11,   185,    36,
      12,    13,    14,     0,     0,     0,    15,     0,   187,     0,
       0,    16
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        21,    10,    25,    60,    26,    71,     3,     3,    23,    29,
       3,     3,   198,   199,    30,    24,     3,     3,    38,     3,
       3,    31,    40,    39,    39,    82,    18,    19,    20,    21,
      22,    41,    29,    29,    26,     3,   222,    29,    59,    60,
       0,    62,   228,    40,    30,    32,    67,    39,    32,    32,
       3,     4,     5,     6,     7,     8,     1,    12,    30,    12,
     126,    82,    15,     3,    32,    37,    30,    30,    30,    91,
      23,    16,    25,    37,    37,    37,    29,    23,    31,    32,
      33,    36,    28,    32,   105,     3,   107,   108,    37,    31,
      99,     3,     4,     5,     6,     7,     8,   106,    34,    31,
      12,    37,    32,    15,     3,     4,     5,    37,    35,    32,
     167,    23,    29,    25,    37,   138,    14,    29,    16,    31,
      32,    33,   100,   101,     3,     4,     5,     6,     7,     8,
      29,     6,    31,    12,    33,   144,    15,     6,     7,     8,
      29,     3,   151,    12,   165,    33,    29,    35,   169,   170,
      29,   172,    31,    29,    33,     3,     4,     5,     6,     7,
       8,     7,    34,     8,    12,    37,     9,    15,    18,    19,
      20,    21,    22,    10,   195,    23,   197,    25,    11,   200,
     189,    29,    41,    31,    41,    33,    39,    39,   209,     3,
       4,     5,     6,     7,     8,     4,    38,    38,    12,    30,
      23,    15,   223,     3,     3,    33,    30,    37,    29,     3,
       4,     5,     6,     7,     8,    29,    30,    31,    12,    33,
      39,    15,     3,     4,     5,     6,     7,     8,     4,    30,
      32,    12,    24,    39,    15,    29,    30,    31,     4,    33,
      30,   167,     3,     4,     5,     6,     7,     8,    29,   169,
      31,    12,    33,     7,    15,     3,     4,     5,     6,     7,
       8,     3,    67,   197,    12,   209,   127,   130,    29,   129,
      31,    59,    33,     3,   128,   131,    18,    19,    20,    21,
      22,    29,   133,    31,    26,    33,    43,    29,    18,    19,
      20,    21,    22,   132,    62,   153,    26,     3,   142,    29,
       6,     7,     8,    -1,    -1,    -1,    12,    -1,   146,    -1,
      -1,    17
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    14,    16,    43,    44,    45,    46,    47,    48,    52,
      53,     3,     6,     7,     8,    12,    17,    70,     3,     0,
      45,    31,    41,    63,     3,    29,    40,    49,    51,     3,
      18,    19,    20,    21,    22,    26,    29,    83,    84,    85,
      86,    87,    90,    91,    92,    94,    95,    96,    99,   102,
     103,   104,    70,     3,     4,     5,    15,    23,    25,    29,
      31,    32,    33,    54,    57,    60,    61,    64,    65,    66,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    31,    62,    63,    79,    83,    30,    50,    51,
      49,    40,    31,     3,     3,     3,    83,    88,    89,    33,
      35,    35,    94,    31,    29,    29,     3,    29,    29,    79,
      80,    81,    54,    55,    56,    58,    59,    79,    82,    79,
      82,    32,    65,    12,    36,    69,     6,     7,     8,     9,
      10,    11,    41,    41,    39,    79,    39,    30,    37,    49,
       3,    32,   100,   101,    38,    30,    37,    83,    93,    84,
      84,     3,    32,    97,    98,     4,     3,    30,    67,    68,
      79,    83,    79,    79,    30,    38,    32,    37,    32,    37,
      23,    32,    37,    34,     3,    69,    71,    72,    73,    74,
      75,    76,    77,    51,    32,   101,    83,    89,    34,    37,
      39,    83,    32,    98,    37,    38,    30,    37,    30,    30,
      39,    79,     3,    54,    56,    59,    79,    79,    79,    29,
      83,    39,     4,    79,    68,    62,    62,    79,    28,    30,
      67,    30,    24,    39,    32,    30,    62,    79,    30,    62
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
         0,    42,    43,    44,    44,    45,    45,    46,    46,    47,
      47,    47,    47,    48,    48,    48,    49,    49,    49,    50,
      50,    51,    51,    52,    52,    53,    54,    54,    54,    54,
      54,    54,    54,    54,    55,    55,    56,    57,    57,    58,
      58,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    67,    67,    68,    68,    69,    69,    70,    70,    70,
      70,    71,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    76,    76,    77,    77,    78,    78,    79,    79,    79,
      80,    80,    81,    81,    82,    82,    83,    83,    84,    84,
      84,    84,    84,    85,    86,    86,    87,    88,    88,    89,
      89,    90,    91,    91,    92,    93,    93,    94,    94,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    99,
      99,   100,   100,   101,   102,   103,   103,   104
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     2,     1,     1,     1,     2,     3,     1,
       2,     3,     4,     2,     2,     3,     2,     1,     3,     1,
       3,     1,     2,     1,     2,     2,     1,     3,     1,     1,
       3,     3,     3,     1,     1,     3,     3,     3,     6,     1,
       3,     3,     5,     7,     5,     9,     1,     2,     2,     3,
       1,     2,     2,     1,     1,     2,     5,     6,     3,     3,
       4,     1,     3,     3,     1,     1,     2,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     2,     1,     1,     3,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     1,     3,     1,
       3,     1,     1,     2,     4,     1,     3,     1,     1,     1,
       1,     3,     4,     1,     1,     1,     2,     2,     3,     3,
       4,     1,     2,     1,     2,     1,     6,     2
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
  "$accept", "root", "root_stmts", "root_stmt", "func_def",
  "func_def_signature", "func_def_name", "func_args_tuple", "func_args",
  "func_arg", "type_def", "type_def_name", "primary_expr",
  "map_expr_pairs", "map_expr_pair", "ifcase_expr", "ifcase_expr_conds",
  "ifcase_expr_cond", "if_expr", "for_expr", "body_expr", "block_expr",
  "block_expr_exprs", "block_expr_expr", "postfix_expr", "call_args",
  "call_arg", "prefix_expr", "any_operator", "multiplicative_expr",
  "additive_expr", "relational_expr", "equality_expr", "and_expr",
  "or_expr", "assignment_expr", "var_expr", "expr", "macro_expr",
  "any_expr", "expr_list", "typeexpr", "nonunion_typeexpr",
  "union_typeexpr", "union_typeexprs", "tuple_typeexpr",
  "tuple_typeexpr_args", "tuple_typeexpr_arg", "qualified_typeexpr",
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
      46,    -1,    52,    -1,    47,    63,    -1,    47,    41,    62,
      -1,    48,    -1,    48,    49,    -1,    48,    40,    49,    -1,
      48,    49,    40,    49,    -1,    14,     3,    -1,    14,    70,
      -1,    14,    17,    70,    -1,    29,    30,    -1,    51,    -1,
      29,    50,    30,    -1,    51,    -1,    50,    37,    51,    -1,
       3,    -1,     3,    83,    -1,    53,    -1,    53,    83,    -1,
      16,     3,    -1,     3,    -1,    29,    81,    30,    -1,     4,
      -1,     5,    -1,    33,    82,    34,    -1,    31,    82,    32,
      -1,    31,    55,    32,    -1,    57,    -1,    56,    -1,    55,
      37,    56,    -1,    54,    38,    79,    -1,    31,    58,    32,
      -1,    31,    58,    37,    79,    28,    32,    -1,    59,    -1,
      58,    37,    59,    -1,    79,    23,    79,    -1,    23,    29,
      79,    30,    62,    -1,    23,    29,    79,    30,    62,    24,
      62,    -1,    25,    29,    79,    30,    62,    -1,    25,    29,
      79,    39,    79,    39,    79,    30,    62,    -1,    63,    -1,
      79,    39,    -1,    31,    32,    -1,    31,    64,    32,    -1,
      65,    -1,    64,    65,    -1,    79,    39,    -1,    80,    -1,
      54,    -1,    66,    12,    -1,    66,    36,     3,    29,    30,
      -1,    66,    36,     3,    29,    67,    30,    -1,    66,    36,
       3,    -1,     3,    29,    30,    -1,     3,    29,    67,    30,
      -1,    68,    -1,    67,    37,    68,    -1,     3,    38,    79,
      -1,    79,    -1,    66,    -1,    70,    69,    -1,     6,    -1,
       7,    -1,     8,    -1,    12,    -1,    69,    -1,    71,     6,
      69,    -1,    71,    -1,    72,     7,    71,    -1,    72,    -1,
      73,     8,    72,    -1,    73,    -1,    74,     9,    73,    -1,
      74,    -1,    75,    10,    74,    -1,    75,    -1,    76,    11,
      75,    -1,    76,    -1,    77,    41,    76,    -1,    15,     3,
      83,    -1,    15,     3,    -1,    77,    -1,    78,    -1,    78,
      41,    77,    -1,    60,    -1,    61,    -1,    80,    -1,    79,
      -1,    79,    -1,    82,    37,    79,    -1,    84,    -1,    85,
      -1,     3,    -1,    26,    -1,    87,    -1,    90,    -1,    92,
      -1,    86,    -1,    84,    35,    84,    -1,    86,    35,    84,
      -1,    29,    88,    30,    -1,    89,    -1,    88,    37,    89,
      -1,    83,    -1,     3,    38,    83,    -1,    91,    -1,    94,
      -1,    91,    94,    -1,    84,    33,    93,    34,    -1,    83,
      -1,    93,    37,    83,    -1,    95,    -1,    99,    -1,   102,
      -1,   103,    -1,    96,    31,    32,    -1,    96,    31,    97,
      32,    -1,    18,    -1,    19,    -1,    98,    -1,    97,    98,
      -1,     3,    39,    -1,     3,    83,    39,    -1,    20,    31,
      32,    -1,    20,    31,   100,    32,    -1,   101,    -1,   100,
     101,    -1,     3,    -1,    21,     3,    -1,   104,    -1,   104,
      29,     4,    37,     4,    30,    -1,    22,     3,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    10,    12,    14,    17,    21,
      23,    26,    30,    35,    38,    41,    45,    48,    50,    54,
      56,    60,    62,    65,    67,    70,    73,    75,    79,    81,
      83,    87,    91,    95,    97,    99,   103,   107,   111,   118,
     120,   124,   128,   134,   142,   148,   158,   160,   163,   166,
     170,   172,   175,   178,   180,   182,   185,   191,   198,   202,
     206,   211,   213,   217,   221,   223,   225,   228,   230,   232,
     234,   236,   238,   242,   244,   248,   250,   254,   256,   260,
     262,   266,   268,   272,   274,   278,   282,   285,   287,   289,
     293,   295,   297,   299,   301,   303,   307,   309,   311,   313,
     315,   317,   319,   321,   323,   327,   331,   335,   337,   341,
     343,   347,   349,   351,   354,   359,   361,   365,   367,   369,
     371,   373,   377,   382,   384,   386,   388,   391,   394,   398,
     402,   407,   409,   412,   414,   417,   419,   426
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   132,   132,   135,   136,   139,   142,   149,   153,   160,
     161,   165,   169,   178,   183,   188,   196,   197,   201,   207,
     211,   217,   223,   234,   235,   243,   260,   266,   267,   273,
     279,   285,   291,   297,   301,   305,   310,   319,   325,   334,
     338,   343,   352,   358,   368,   374,   385,   386,   390,   394,
     402,   406,   411,   412,   416,   417,   425,   432,   441,   448,
     454,   465,   469,   475,   482,   490,   491,   500,   500,   500,
     500,   503,   504,   515,   516,   527,   528,   539,   540,   551,
     552,   563,   564,   575,   576,   585,   592,   601,   602,   603,
     611,   612,   615,   615,   618,   622,   637,   638,   642,   648,
     651,   652,   653,   658,   667,   672,   679,   688,   692,   698,
     703,   714,   723,   727,   734,   743,   747,   756,   757,   758,
     759,   764,   765,   772,   777,   785,   786,   790,   796,   807,
     811,   820,   821,   825,   830,   840,   841,   850
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
  const int Parser::yylast_ = 311;
  const int Parser::yynnts_ = 63;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 19;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 42;

  const unsigned int Parser::yyuser_token_number_max_ = 296;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace driver

#line 858 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
 /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}
