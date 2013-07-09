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
#line 90 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"

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
#line 83 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 216 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 4: /* "\"real number constant\"" */
#line 83 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 221 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 5: /* "\"integer number constant\"" */
#line 83 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 226 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 6: /* "\"string constant\"" */
#line 83 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 231 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 10: /* "OPERATOR" */
#line 83 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 112 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 6:
#line 115 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 7:
#line 120 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncDef* d = new FuncDef;
              d->setName(*(yysemantic_stack_[(3) - (2)].string)); delete (yysemantic_stack_[(3) - (2)].string);
              d->setBody(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
              (yyval.node) = d;
            ;}
    break;

  case 8:
#line 126 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncDef *d = new FuncDef;
              d->setName(*(yysemantic_stack_[(4) - (2)].string)); delete (yysemantic_stack_[(4) - (2)].string);
              d->setIn(shared_ptr<Node>((yysemantic_stack_[(4) - (3)].node)));
              d->setBody(shared_ptr<Node>((yysemantic_stack_[(4) - (4)].node)));
              (yyval.node) = d;
            ;}
    break;

  case 9:
#line 133 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncDef *d = new FuncDef;
              d->setName(*(yysemantic_stack_[(5) - (2)].string)); delete (yysemantic_stack_[(5) - (2)].string);
              d->setOut(shared_ptr<Node>((yysemantic_stack_[(5) - (4)].node)));
              d->setBody(shared_ptr<Node>((yysemantic_stack_[(5) - (5)].node)));
              (yyval.node) = d;
            ;}
    break;

  case 10:
#line 140 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 150 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = NULL; ;}
    break;

  case 12:
#line 151 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
                    FuncArgTuple *t = new FuncArgTuple;
                    Nodes args(1);
                    args[0] = shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node));
                    t->setArgs(args);
                    (yyval.node) = t;
                  ;}
    break;

  case 13:
#line 158 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
                    FuncArgTuple *t = new FuncArgTuple;
                    t->setArgs(*(yysemantic_stack_[(3) - (2)].nodes));
                    (yyval.node) = t;
                    delete (yysemantic_stack_[(3) - (2)].nodes);
                  ;}
    break;

  case 14:
#line 166 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yyval.nodes) = new Nodes;
              (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 15:
#line 170 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
            ;}
    break;

  case 16:
#line 175 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncArg *a = new FuncArg;
              a->setName(*(yysemantic_stack_[(1) - (1)].string));
              (yyval.node) = a;
              delete (yysemantic_stack_[(1) - (1)].string);
            ;}
    break;

  case 17:
#line 181 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              FuncArg *a = new FuncArg;
              a->setName(*(yysemantic_stack_[(2) - (1)].string));
              a->setType(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
              (yyval.node) = a;
              delete (yysemantic_stack_[(2) - (1)].string);
            ;}
    break;

  case 18:
#line 190 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              TypeDef *t = new TypeDef;
              t->setName(*(yysemantic_stack_[(2) - (2)].string));
              (yyval.node) = t;
              delete (yysemantic_stack_[(2) - (2)].string);
            ;}
    break;

  case 21:
#line 202 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
                        NamedType *n = new NamedType;
                        n->setName(*(yysemantic_stack_[(1) - (1)].string));
                        (yyval.node) = n;
                        delete (yysemantic_stack_[(1) - (1)].string);
                      ;}
    break;

  case 22:
#line 210 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
                    UnionType *t = new UnionType;
                    t->setTypes(*(yysemantic_stack_[(1) - (1)].nodes));
                    (yyval.node) = t;
                    delete (yysemantic_stack_[(1) - (1)].nodes);
                  ;}
    break;

  case 23:
#line 218 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
                      (yyval.nodes) = new Nodes;
                      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
                      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
                    ;}
    break;

  case 24:
#line 223 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
                      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
                    ;}
    break;

  case 25:
#line 228 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          FuncBody *b = new FuncBody;
          (yyval.node) = b;
        ;}
    break;

  case 26:
#line 232 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          FuncBody *b = new FuncBody;
          b->setStmts(*(yysemantic_stack_[(3) - (2)].nodes));
          (yyval.node) = b;
          delete (yysemantic_stack_[(3) - (2)].nodes);
        ;}
    break;

  case 27:
#line 240 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yyval.nodes) = new Nodes;
          (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
        ;}
    break;

  case 28:
#line 244 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yysemantic_stack_[(2) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
        ;}
    break;

  case 29:
#line 249 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          ExprStmt *s = new ExprStmt;
          s->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (1)].node)));
          (yyval.node) = s;
        ;}
    break;

  case 30:
#line 257 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IdentifierExpr *i = new IdentifierExpr;
      i->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = i;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 31:
#line 263 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); ;}
    break;

  case 33:
#line 268 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(true);
      u->setOperatorName(*(yysemantic_stack_[(2) - (2)].string));
      u->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (1)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 34:
#line 276 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      MemberAccessExpr *m = new MemberAccessExpr;
      m->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      m->setName(*(yysemantic_stack_[(3) - (3)].string));
      (yyval.node) = m;
      delete (yysemantic_stack_[(3) - (3)].string);
    ;}
    break;

  case 35:
#line 283 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      (yyval.node) = c;
    ;}
    break;

  case 36:
#line 288 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setExpr(shared_ptr<Node>((yysemantic_stack_[(4) - (1)].node)));
      c->setArgs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = c;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 37:
#line 298 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 38:
#line 302 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 39:
#line 308 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setName(*(yysemantic_stack_[(3) - (1)].string));
      a->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 40:
#line 315 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setExpr(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = a;
    ;}
    break;

  case 42:
#line 324 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(false);
      u->setOperatorName(*(yysemantic_stack_[(2) - (1)].string));
      u->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 48:
#line 337 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 349 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 52:
#line 361 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 54:
#line 372 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); ;}
    break;

  case 55:
#line 373 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yysemantic_stack_[(3) - (1)].varDefExpr)->setInitialExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
        ;}
    break;

  case 56:
#line 378 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              VarDefExpr *v = new VarDefExpr;
              v->setName(*(yysemantic_stack_[(3) - (2)].string));
              v->setType(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
              (yyval.varDefExpr) = v;
              delete (yysemantic_stack_[(3) - (2)].string);
            ;}
    break;

  case 57:
#line 385 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              VarDefExpr *v = new VarDefExpr;
              v->setName(*(yysemantic_stack_[(2) - (2)].string));
              (yyval.varDefExpr) = v;
              delete (yysemantic_stack_[(2) - (2)].string);
            ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 817 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
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
  const signed char Parser::yypact_ninf_ = -41;
  const signed char
  Parser::yypact_[] =
  {
        75,     3,    17,    43,    75,   -41,   -41,   -41,     1,   -41,
     -41,   -41,    26,     5,     4,    31,    -2,   -41,   -41,   -41,
     -41,    24,   -41,    27,   -41,     7,   -41,   -41,   -41,   -41,
     -41,   -41,    46,    58,   -41,    29,   -41,   -41,    18,   -41,
      76,    51,    56,    50,    44,    45,    61,    31,   -41,    26,
      26,   -41,    87,    26,    77,   -41,   -41,   -41,    47,    89,
     -41,    76,    76,    76,   -41,    76,   -41,    61,   -41,   -41,
     -41,   -41,   -41,    70,   -41,    65,   -41,   -41,   -41,   -41,
      51,    56,    50,   -41,    58,   -41,    67,   -41,   -41
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     0,     2,     4,     5,     6,     0,    18,
       1,     3,    16,     0,     0,     0,     0,    12,     7,    21,
      17,    20,    19,    22,    11,     0,    14,    30,    43,    44,
      45,    46,     0,     0,    25,     0,    27,    32,    41,    47,
       0,    49,    51,    53,     0,    54,     0,     0,     8,     0,
       0,    13,     0,    57,     0,    26,    28,    33,     0,     0,
      42,     0,     0,     0,    29,     0,     9,     0,    23,    24,
      15,    56,    31,    30,    35,     0,    37,    40,    34,    48,
      50,    52,    55,    10,     0,    36,     0,    39,    38
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -41,   -41,   -41,    91,   -41,   -12,   -41,   -11,   -41,    48,
     -40,   -41,   -41,   -15,   -41,    62,   -41,   -41,   -41,    10,
     -35,   -41,    36,    37,    34,   -33,   -41
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     3,     4,     5,     6,    16,    25,    17,     7,    20,
      21,    22,    23,    18,    35,    36,    37,    38,    75,    76,
      39,    40,    41,    42,    43,    44,    45
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        54,    48,    26,    46,    12,    60,     8,    27,    12,    68,
      69,    28,    29,    30,    31,    14,    13,    32,    14,    33,
       9,    24,    34,    51,    47,    77,    79,    15,    57,    19,
      52,    66,    27,    58,    12,    67,    28,    29,    30,    31,
      59,    70,    32,    10,    33,    49,    13,    55,    50,    53,
      73,    87,    83,    77,    28,    29,    30,    31,    61,    63,
      32,    27,    33,    74,    62,    28,    29,    30,    31,    64,
      73,    32,    65,    33,    28,    29,    30,    31,    14,    27,
      32,    85,    33,    28,    29,    30,    31,     1,    86,     2,
      12,    33,    78,    72,    84,    11,    88,    56,    80,    82,
      81,    71
  };

  /* YYCHECK.  */
  const unsigned char
  Parser::yycheck_[] =
  {
        33,    16,    13,    15,     3,    40,     3,     3,     3,    49,
      50,     7,     8,     9,    10,    17,    15,    13,    17,    15,
       3,    16,    18,    16,    26,    58,    61,    26,    10,     3,
      23,    46,     3,    15,     3,    47,     7,     8,     9,    10,
      22,    52,    13,     0,    15,    21,    15,    18,    21,     3,
       3,    84,    67,    86,     7,     8,     9,    10,     7,     9,
      13,     3,    15,    16,     8,     7,     8,     9,    10,    25,
       3,    13,    27,    15,     7,     8,     9,    10,    17,     3,
      13,    16,    15,     7,     8,     9,    10,    12,    23,    14,
       3,    15,     3,    16,    24,     4,    86,    35,    62,    65,
      63,    53
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    12,    14,    29,    30,    31,    32,    36,     3,     3,
       0,    31,     3,    15,    17,    26,    33,    35,    41,     3,
      37,    38,    39,    40,    16,    34,    35,     3,     7,     8,
       9,    10,    13,    15,    18,    42,    43,    44,    45,    48,
      49,    50,    51,    52,    53,    54,    33,    26,    41,    21,
      21,    16,    23,     3,    53,    18,    43,    10,    15,    22,
      48,     7,     8,     9,    25,    27,    41,    33,    38,    38,
      35,    37,    16,     3,    16,    46,    47,    53,     3,    48,
      50,    51,    52,    41,    24,    16,    23,    53,    47
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
      37,    38,    39,    40,    40,    41,    41,    42,    42,    43,
      44,    44,    45,    45,    45,    45,    45,    46,    46,    47,
      47,    48,    48,    49,    49,    49,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    53,    54,    54
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     2,     1,     1,     1,     3,     4,     5,
       6,     2,     1,     3,     1,     3,     1,     2,     2,     1,
       1,     1,     1,     3,     3,     2,     3,     1,     2,     2,
       1,     3,     1,     2,     3,     3,     4,     1,     3,     3,
       1,     1,     2,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     3,     1,     1,     3,     3,     2
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
  "func_arg", "type_decl", "type_expr", "nonunion_type_expr",
  "union_type_expr", "union_type_exprs", "body", "stmts", "stmt",
  "primary_expr", "postfix_expr", "call_args", "call_arg", "prefix_expr",
  "prefix_op", "multiplicative_expr", "additive_expr", "relational_expr",
  "expr", "var_expr", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        29,     0,    -1,    30,    -1,    30,    31,    -1,    31,    -1,
      32,    -1,    36,    -1,    12,     3,    41,    -1,    12,     3,
      33,    41,    -1,    12,     3,    26,    33,    41,    -1,    12,
       3,    33,    26,    33,    41,    -1,    15,    16,    -1,    35,
      -1,    15,    34,    16,    -1,    35,    -1,    34,    23,    35,
      -1,     3,    -1,     3,    37,    -1,    14,     3,    -1,    39,
      -1,    38,    -1,     3,    -1,    40,    -1,    38,    21,    38,
      -1,    40,    21,    38,    -1,    17,    18,    -1,    17,    42,
      18,    -1,    43,    -1,    42,    43,    -1,    53,    25,    -1,
       3,    -1,    15,    53,    16,    -1,    44,    -1,    45,    10,
      -1,    45,    22,     3,    -1,    45,    15,    16,    -1,    45,
      15,    46,    16,    -1,    47,    -1,    46,    23,    47,    -1,
       3,    24,    53,    -1,    53,    -1,    45,    -1,    49,    48,
      -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,    48,
      -1,    50,     7,    48,    -1,    50,    -1,    51,     8,    50,
      -1,    51,    -1,    52,     9,    51,    -1,    52,    -1,    54,
      -1,    54,    27,    52,    -1,    13,     3,    37,    -1,    13,
       3,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    10,    12,    14,    18,    23,
      29,    36,    39,    41,    45,    47,    51,    53,    56,    59,
      61,    63,    65,    67,    71,    75,    78,    82,    84,    87,
      90,    92,    96,    98,   101,   105,   109,   114,   116,   120,
     124,   126,   128,   131,   133,   135,   137,   139,   141,   145,
     147,   151,   153,   157,   159,   161,   165,   169
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   105,   105,   108,   109,   112,   115,   120,   126,   133,
     140,   150,   151,   158,   166,   170,   175,   181,   190,   198,
     199,   202,   210,   218,   223,   228,   232,   240,   244,   249,
     257,   263,   267,   268,   276,   283,   288,   298,   302,   308,
     315,   323,   324,   333,   333,   333,   333,   336,   337,   348,
     349,   360,   361,   371,   372,   373,   378,   385
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
  const int Parser::yylast_ = 101;
  const int Parser::yynnts_ = 27;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 10;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 28;

  const unsigned int Parser::yyuser_token_number_max_ = 282;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace driver

#line 394 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
 /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}
