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
#line 91 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"

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
#line 84 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 216 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 4: /* "\"real number constant\"" */
#line 84 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 221 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 5: /* "\"integer number constant\"" */
#line 84 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 226 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 6: /* "\"string constant\"" */
#line 84 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 231 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 10: /* "OPERATOR" */
#line 84 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 236 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
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
#line 318 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
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
#line 113 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 6:
#line 116 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 7:
#line 121 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncDef* d = new FuncDef;
              d->setName(*(yysemantic_stack_[(3) - (2)].string)); delete (yysemantic_stack_[(3) - (2)].string);
              d->setBody(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
              (yyval.node) = d;
            ;}
    break;

  case 8:
#line 127 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncDef *d = new FuncDef;
              d->setName(*(yysemantic_stack_[(4) - (2)].string)); delete (yysemantic_stack_[(4) - (2)].string);
              d->setIn(shared_ptr<Node>((yysemantic_stack_[(4) - (3)].node)));
              d->setBody(shared_ptr<Node>((yysemantic_stack_[(4) - (4)].node)));
              (yyval.node) = d;
            ;}
    break;

  case 9:
#line 134 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncDef *d = new FuncDef;
              d->setName(*(yysemantic_stack_[(5) - (2)].string)); delete (yysemantic_stack_[(5) - (2)].string);
              d->setOut(shared_ptr<Node>((yysemantic_stack_[(5) - (4)].node)));
              d->setBody(shared_ptr<Node>((yysemantic_stack_[(5) - (5)].node)));
              (yyval.node) = d;
            ;}
    break;

  case 10:
#line 141 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncDef *d = new FuncDef;
              d->setName(*(yysemantic_stack_[(6) - (2)].string)); delete (yysemantic_stack_[(6) - (2)].string);
              d->setIn(shared_ptr<Node>((yysemantic_stack_[(6) - (3)].node)));
              d->setOut(shared_ptr<Node>((yysemantic_stack_[(6) - (5)].node)));
              d->setBody(shared_ptr<Node>((yysemantic_stack_[(6) - (6)].node)));
              (yyval.node) = d;
             ;}
    break;

  case 11:
#line 151 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = NULL; ;}
    break;

  case 12:
#line 152 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
                    FuncArgTuple *t = new FuncArgTuple;
                    Nodes args(1);
                    args[0] = shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node));
                    t->setArgs(args);
                    (yyval.node) = t;
                  ;}
    break;

  case 13:
#line 159 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
                    FuncArgTuple *t = new FuncArgTuple;
                    t->setArgs(*(yysemantic_stack_[(3) - (2)].nodes));
                    (yyval.node) = t;
                    delete (yysemantic_stack_[(3) - (2)].nodes);
                  ;}
    break;

  case 14:
#line 167 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yyval.nodes) = new Nodes;
              (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 15:
#line 171 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
            ;}
    break;

  case 16:
#line 176 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncArg *a = new FuncArg;
              a->setName(*(yysemantic_stack_[(1) - (1)].string));
              (yyval.node) = a;
              delete (yysemantic_stack_[(1) - (1)].string);
            ;}
    break;

  case 17:
#line 182 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncArg *a = new FuncArg;
              a->setName(*(yysemantic_stack_[(2) - (1)].string));
              a->setType(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
              (yyval.node) = a;
              delete (yysemantic_stack_[(2) - (1)].string);
            ;}
    break;

  case 18:
#line 191 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              TypeDef *t = new TypeDef;
              t->setName(*(yysemantic_stack_[(2) - (2)].string));
              (yyval.node) = t;
              delete (yysemantic_stack_[(2) - (2)].string);
            ;}
    break;

  case 19:
#line 199 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          FuncBody *b = new FuncBody;
          (yyval.node) = b;
        ;}
    break;

  case 20:
#line 203 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          FuncBody *b = new FuncBody;
          b->setStmts(*(yysemantic_stack_[(3) - (2)].nodes));
          (yyval.node) = b;
          delete (yysemantic_stack_[(3) - (2)].nodes);
        ;}
    break;

  case 21:
#line 211 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yyval.nodes) = new Nodes;
          (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
        ;}
    break;

  case 22:
#line 215 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yysemantic_stack_[(2) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
        ;}
    break;

  case 23:
#line 220 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          ExprStmt *s = new ExprStmt;
          s->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (1)].node)));
          (yyval.node) = s;
        ;}
    break;

  case 24:
#line 231 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IdentifierExpr *i = new IdentifierExpr;
      i->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = i;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 25:
#line 237 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); ;}
    break;

  case 27:
#line 242 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(true);
      u->setOperatorName(*(yysemantic_stack_[(2) - (2)].string));
      u->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (1)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 28:
#line 250 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(5) - (3)].string));
      c->setContext(shared_ptr<Node>((yysemantic_stack_[(5) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(5) - (3)].string);
    ;}
    break;

  case 29:
#line 257 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(6) - (3)].string));
      c->setCallArgs(*(yysemantic_stack_[(6) - (5)].nodes));
      c->setContext(shared_ptr<Node>((yysemantic_stack_[(6) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(6) - (3)].string);
      delete (yysemantic_stack_[(6) - (5)].nodes);
    ;}
    break;

  case 30:
#line 266 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      MemberAccessExpr *m = new MemberAccessExpr;
      m->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      m->setName(*(yysemantic_stack_[(3) - (3)].string));
      (yyval.node) = m;
      delete (yysemantic_stack_[(3) - (3)].string);
    ;}
    break;

  case 31:
#line 273 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (1)].string));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 32:
#line 279 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(4) - (1)].string));
      c->setCallArgs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = c;
      delete (yysemantic_stack_[(4) - (1)].string);
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 33:
#line 290 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 34:
#line 294 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 35:
#line 300 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setName(*(yysemantic_stack_[(3) - (1)].string));
      a->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 36:
#line 307 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setExpr(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = a;
    ;}
    break;

  case 38:
#line 316 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(false);
      u->setOperatorName(*(yysemantic_stack_[(2) - (1)].string));
      u->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 44:
#line 329 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 46:
#line 341 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 48:
#line 353 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 50:
#line 364 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); ;}
    break;

  case 51:
#line 365 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yysemantic_stack_[(3) - (1)].varDefExpr)->setInitialExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
        ;}
    break;

  case 52:
#line 370 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              VarDefExpr *v = new VarDefExpr;
              v->setName(*(yysemantic_stack_[(3) - (2)].string));
              v->setType(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
              (yyval.varDefExpr) = v;
              delete (yysemantic_stack_[(3) - (2)].string);
            ;}
    break;

  case 53:
#line 377 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              VarDefExpr *v = new VarDefExpr;
              v->setName(*(yysemantic_stack_[(2) - (2)].string));
              (yyval.varDefExpr) = v;
              delete (yysemantic_stack_[(2) - (2)].string);
            ;}
    break;

  case 56:
#line 392 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NamedTypeExpr *n = new NamedTypeExpr;
      n->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 58:
#line 402 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnionTypeExpr *t = new UnionTypeExpr;
      t->setTypes(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 59:
#line 411 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 60:
#line 416 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 61:
#line 423 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExpr *t = new TupleTypeExpr;
      t->setArgs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 62:
#line 432 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 63:
#line 437 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 64:
#line 443 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setExpr(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = t;
    ;}
    break;

  case 65:
#line 448 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setName(*(yysemantic_stack_[(3) - (1)].string));
      t->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 889 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
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
  const signed char Parser::yypact_ninf_ = -47;
  const signed char
  Parser::yypact_[] =
  {
        67,    40,    48,    68,    67,   -47,   -47,   -47,     5,   -47,
     -47,   -47,    13,     1,    29,    15,    -2,   -47,   -47,   -47,
      26,   -47,    53,   -47,    55,   -47,   -47,    30,   -47,    11,
     -47,   -47,   -47,   -47,    79,    88,   -47,    49,   -47,   -47,
      23,   -47,     4,    87,    91,    93,    83,    82,    94,    15,
     -47,    89,   -47,    32,    92,    13,    13,   -47,   111,    62,
      13,   100,   -47,   -47,   -47,   114,   -47,     4,     4,     4,
     -47,     4,   -47,    94,    13,   -47,    26,    26,   -47,   -47,
     -47,    10,   -47,    38,   -47,   -47,   -47,   -47,   103,   -47,
      87,    91,    93,   -47,   -47,   -47,   -47,    88,   -47,    97,
      77,   -47,   -47,   -47,    50,   -47
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     0,     2,     4,     5,     6,     0,    18,
       1,     3,    16,     0,     0,     0,     0,    12,     7,    56,
       0,    17,    54,    55,    58,    57,    11,     0,    14,    24,
      39,    40,    41,    42,     0,     0,    19,     0,    21,    26,
      37,    43,     0,    45,    47,    49,     0,    50,     0,     0,
       8,    56,    64,     0,     0,     0,     0,    13,     0,     0,
      53,     0,    20,    22,    27,     0,    38,     0,     0,     0,
      23,     0,     9,     0,     0,    61,     0,     0,    59,    60,
      15,    24,    31,     0,    33,    36,    52,    25,    30,    44,
      46,    48,    51,    10,    65,    63,    62,     0,    32,     0,
       0,    35,    34,    28,     0,    29
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -47,   -47,   -47,   115,   -47,    -9,   -47,    -8,   -47,   -13,
     -47,    84,   -47,   -47,    20,    24,   -40,   -47,    54,    56,
      57,   -14,   -47,   -11,   -46,   -47,   -47,   -47,   -47,    12
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     3,     4,     5,     6,    16,    27,    17,     7,    18,
      37,    38,    39,    40,    83,    84,    41,    42,    43,    44,
      45,    85,    47,    52,    22,    23,    24,    25,    53,    54
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        46,    21,    66,    50,    12,    28,    48,    29,    12,    78,
      79,    30,    31,    32,    33,    14,    19,    26,    12,    35,
      13,    61,    14,    46,    49,    59,    59,    89,    20,    51,
      13,    15,    29,    64,    97,    72,    30,    31,    32,    33,
      73,    20,    34,     8,    35,    65,    57,    36,    75,    86,
      80,     9,    29,    58,    98,    76,    30,    31,    32,    33,
      93,    99,    34,    94,    35,    81,   105,    62,    10,    30,
      31,    32,    33,    99,    55,    34,    56,    35,    82,     1,
      81,     2,    60,   101,    30,    31,    32,    33,    95,    96,
      34,    29,    35,   103,    67,    30,    31,    32,    33,    68,
      81,    34,    69,    35,    30,    31,    32,    33,    70,    71,
      34,    14,    35,    74,    12,    77,    87,    88,   100,    11,
     104,    63,    90,   102,     0,    91,     0,     0,    92
  };

  /* YYCHECK.  */
  const signed char
  Parser::yycheck_[] =
  {
        14,    12,    42,    16,     3,    13,    15,     3,     3,    55,
      56,     7,     8,     9,    10,    17,     3,    16,     3,    15,
      15,    35,    17,    37,    26,    15,    15,    67,    15,     3,
      15,    26,     3,    10,    24,    48,     7,     8,     9,    10,
      49,    15,    13,     3,    15,    22,    16,    18,    16,    60,
      58,     3,     3,    23,    16,    23,     7,     8,     9,    10,
      73,    23,    13,    74,    15,     3,    16,    18,     0,     7,
       8,     9,    10,    23,    21,    13,    21,    15,    16,    12,
       3,    14,     3,    97,     7,     8,     9,    10,    76,    77,
      13,     3,    15,    16,     7,     7,     8,     9,    10,     8,
       3,    13,     9,    15,     7,     8,     9,    10,    25,    27,
      13,    17,    15,    24,     3,    23,    16,     3,    15,     4,
     100,    37,    68,    99,    -1,    69,    -1,    -1,    71
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    12,    14,    29,    30,    31,    32,    36,     3,     3,
       0,    31,     3,    15,    17,    26,    33,    35,    37,     3,
      15,    51,    52,    53,    54,    55,    16,    34,    35,     3,
       7,     8,     9,    10,    13,    15,    18,    38,    39,    40,
      41,    44,    45,    46,    47,    48,    49,    50,    33,    26,
      37,     3,    51,    56,    57,    21,    21,    16,    23,    15,
       3,    49,    18,    39,    10,    22,    44,     7,     8,     9,
      25,    27,    37,    33,    24,    16,    23,    23,    52,    52,
      35,     3,    16,    42,    43,    49,    51,    16,     3,    44,
      46,    47,    48,    37,    51,    57,    57,    24,    16,    23,
      15,    49,    43,    16,    42,    16
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    28,    29,    30,    30,    31,    31,    32,    32,    32,
      32,    33,    33,    33,    34,    34,    35,    35,    36,    37,
      37,    38,    38,    39,    40,    40,    41,    41,    41,    41,
      41,    41,    41,    42,    42,    43,    43,    44,    44,    45,
      45,    45,    45,    46,    46,    47,    47,    48,    48,    49,
      49,    49,    50,    50,    51,    51,    52,    52,    53,    54,
      54,    55,    56,    56,    57,    57
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     2,     1,     1,     1,     3,     4,     5,
       6,     2,     1,     3,     1,     3,     1,     2,     2,     2,
       3,     1,     2,     2,     1,     3,     1,     2,     5,     6,
       3,     3,     4,     1,     3,     3,     1,     1,     2,     1,
       1,     1,     1,     1,     3,     1,     3,     1,     3,     1,
       1,     3,     3,     2,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     1,     3
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of input\"", "error", "$undefined", "\"identifier\"",
  "\"real number constant\"", "\"integer number constant\"",
  "\"string constant\"", "MULTIPLICATIVE_OPERATOR", "ADDITIVE_OPERATOR",
  "RELATIONAL_OPERATOR", "OPERATOR", "\"symbol\"", "\"func keyword\"",
  "\"var keyword\"", "\"type keyword\"", "\"opening paranthesis (\"",
  "\"closing paranthesis )\"", "\"opening braces {\"",
  "\"closing braces }\"", "\"opening bracket [\"", "\"closing bracket ]\"",
  "\"vertical pipe |\"", "\".\"", "\",\"", "\":\"", "\";\"",
  "\"right arrow ->\"", "\"assignment operator =\"", "$accept", "root",
  "root_stmts", "root_stmt", "func_decl", "func_arg_tuple", "func_args",
  "func_arg", "type_decl", "body", "stmts", "stmt", "primary_expr",
  "postfix_expr", "call_args", "call_arg", "prefix_expr", "prefix_op",
  "multiplicative_expr", "additive_expr", "relational_expr", "expr",
  "var_expr", "typeexpr", "nonunion_typeexpr", "union_typeexpr",
  "union_typeexprs", "tuple_typeexpr", "tuple_typeexpr_args",
  "tuple_typeexpr_arg", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        29,     0,    -1,    30,    -1,    30,    31,    -1,    31,    -1,
      32,    -1,    36,    -1,    12,     3,    37,    -1,    12,     3,
      33,    37,    -1,    12,     3,    26,    33,    37,    -1,    12,
       3,    33,    26,    33,    37,    -1,    15,    16,    -1,    35,
      -1,    15,    34,    16,    -1,    35,    -1,    34,    23,    35,
      -1,     3,    -1,     3,    51,    -1,    14,     3,    -1,    17,
      18,    -1,    17,    38,    18,    -1,    39,    -1,    38,    39,
      -1,    49,    25,    -1,     3,    -1,    15,    49,    16,    -1,
      40,    -1,    41,    10,    -1,    41,    22,     3,    15,    16,
      -1,    41,    22,     3,    15,    42,    16,    -1,    41,    22,
       3,    -1,     3,    15,    16,    -1,     3,    15,    42,    16,
      -1,    43,    -1,    42,    23,    43,    -1,     3,    24,    49,
      -1,    49,    -1,    41,    -1,    45,    44,    -1,     7,    -1,
       8,    -1,     9,    -1,    10,    -1,    44,    -1,    46,     7,
      44,    -1,    46,    -1,    47,     8,    46,    -1,    47,    -1,
      48,     9,    47,    -1,    48,    -1,    50,    -1,    50,    27,
      48,    -1,    13,     3,    51,    -1,    13,     3,    -1,    52,
      -1,    53,    -1,     3,    -1,    55,    -1,    54,    -1,    52,
      21,    52,    -1,    54,    21,    52,    -1,    15,    56,    16,
      -1,    57,    23,    57,    -1,    56,    23,    57,    -1,    51,
      -1,     3,    24,    51,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    10,    12,    14,    18,    23,
      29,    36,    39,    41,    45,    47,    51,    53,    56,    59,
      62,    66,    68,    71,    74,    76,    80,    82,    85,    91,
      98,   102,   106,   111,   113,   117,   121,   123,   125,   128,
     130,   132,   134,   136,   138,   142,   144,   148,   150,   154,
     156,   158,   162,   166,   169,   171,   173,   175,   177,   179,
     183,   187,   191,   195,   199,   201
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   106,   106,   109,   110,   113,   116,   121,   127,   134,
     141,   151,   152,   159,   167,   171,   176,   182,   191,   199,
     203,   211,   215,   220,   231,   237,   241,   242,   250,   257,
     266,   273,   279,   290,   294,   300,   307,   315,   316,   325,
     325,   325,   325,   328,   329,   340,   341,   352,   353,   363,
     364,   365,   370,   377,   387,   388,   392,   398,   402,   411,
     416,   423,   432,   437,   443,   448
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
      25,    26,    27
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 128;
  const int Parser::yynnts_ = 30;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 10;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 28;

  const unsigned int Parser::yyuser_token_number_max_ = 282;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace driver

#line 457 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
 /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}
