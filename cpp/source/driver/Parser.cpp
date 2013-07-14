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
#line 108 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"

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
#line 101 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 216 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 4: /* "\"number constant\"" */
#line 101 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 221 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 5: /* "\"string constant\"" */
#line 101 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 226 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 6: /* "MULTIPLICATIVE_OPERATOR" */
#line 101 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 231 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 7: /* "ADDITIVE_OPERATOR" */
#line 101 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 236 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 8: /* "RELATIONAL_OPERATOR" */
#line 101 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };
#line 241 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 9: /* "OPERATOR" */
#line 101 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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
#line 130 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 6:
#line 133 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
            ;}
    break;

  case 7:
#line 139 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(2) - (1)].funcDef)->setBody(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
            ;}
    break;

  case 8:
#line 142 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(3) - (1)].funcDef)->setIn(*(yysemantic_stack_[(3) - (2)].nodes));
              (yysemantic_stack_[(3) - (1)].funcDef)->setBody(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
              delete (yysemantic_stack_[(3) - (2)].nodes);
            ;}
    break;

  case 9:
#line 147 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(4) - (1)].funcDef)->setOut(*(yysemantic_stack_[(4) - (3)].nodes));
              (yysemantic_stack_[(4) - (1)].funcDef)->setBody(shared_ptr<Node>((yysemantic_stack_[(4) - (4)].node)));
              delete (yysemantic_stack_[(4) - (3)].nodes);
            ;}
    break;

  case 10:
#line 152 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              (yysemantic_stack_[(5) - (1)].funcDef)->setIn(*(yysemantic_stack_[(5) - (2)].nodes));
              (yysemantic_stack_[(5) - (1)].funcDef)->setOut(*(yysemantic_stack_[(5) - (4)].nodes));
              (yysemantic_stack_[(5) - (1)].funcDef)->setBody(shared_ptr<Node>((yysemantic_stack_[(5) - (5)].node)));
              delete (yysemantic_stack_[(5) - (2)].nodes);
              delete (yysemantic_stack_[(5) - (4)].nodes);
             ;}
    break;

  case 11:
#line 162 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName(*(yysemantic_stack_[(2) - (2)].string)); delete (yysemantic_stack_[(2) - (2)].string);
      (yyval.funcDef) = d;
    ;}
    break;

  case 12:
#line 167 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName(*(yysemantic_stack_[(2) - (2)].string)); delete (yysemantic_stack_[(2) - (2)].string);
      (yyval.funcDef) = d;
    ;}
    break;

  case 13:
#line 172 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName("_" + *(yysemantic_stack_[(3) - (3)].string)); delete (yysemantic_stack_[(3) - (3)].string);
      (yyval.funcDef) = d;
    ;}
    break;

  case 14:
#line 180 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; ;}
    break;

  case 15:
#line 181 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 16:
#line 185 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 17:
#line 191 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 18:
#line 195 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 19:
#line 201 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncArg *a = new FuncArg;
      a->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = a;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 20:
#line 207 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncArg *a = new FuncArg;
      a->setName(*(yysemantic_stack_[(2) - (1)].string));
      a->setType(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 21:
#line 218 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].typeDef); ;}
    break;

  case 22:
#line 219 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].typeDef)->setType(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 23:
#line 227 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TypeDef *t = new TypeDef;
      t->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.typeDef) = t;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 24:
#line 235 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          FuncBody *b = new FuncBody;
          (yyval.node) = b;
        ;}
    break;

  case 25:
#line 239 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          FuncBody *b = new FuncBody;
          b->setStmts(*(yysemantic_stack_[(3) - (2)].nodes));
          (yyval.node) = b;
          delete (yysemantic_stack_[(3) - (2)].nodes);
        ;}
    break;

  case 26:
#line 247 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yyval.nodes) = new Nodes;
          (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
        ;}
    break;

  case 27:
#line 251 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yysemantic_stack_[(2) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
        ;}
    break;

  case 28:
#line 256 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          ExprStmt *s = new ExprStmt;
          s->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (1)].node)));
          (yyval.node) = s;
        ;}
    break;

  case 29:
#line 267 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      IdentifierExpr *i = new IdentifierExpr;
      i->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = i;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 30:
#line 273 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); ;}
    break;

  case 32:
#line 278 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(true);
      u->setOperatorName(*(yysemantic_stack_[(2) - (2)].string));
      u->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (1)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 33:
#line 286 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(5) - (3)].string));
      c->setContext(shared_ptr<Node>((yysemantic_stack_[(5) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(5) - (3)].string);
    ;}
    break;

  case 34:
#line 293 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
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

  case 35:
#line 302 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      MemberAccessExpr *m = new MemberAccessExpr;
      m->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      m->setName(*(yysemantic_stack_[(3) - (3)].string));
      (yyval.node) = m;
      delete (yysemantic_stack_[(3) - (3)].string);
    ;}
    break;

  case 36:
#line 309 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (1)].string));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 37:
#line 315 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(4) - (1)].string));
      c->setCallArgs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = c;
      delete (yysemantic_stack_[(4) - (1)].string);
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 38:
#line 326 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 39:
#line 330 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 40:
#line 336 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setName(*(yysemantic_stack_[(3) - (1)].string));
      a->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 41:
#line 343 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setExpr(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = a;
    ;}
    break;

  case 43:
#line 352 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(false);
      u->setOperatorName(*(yysemantic_stack_[(2) - (1)].string));
      u->setExpr(shared_ptr<Node>((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 49:
#line 365 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 51:
#line 377 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 53:
#line 389 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    ;}
    break;

  case 55:
#line 401 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      AssignmentExpr *e = new AssignmentExpr;
      e->setLhs(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
    ;}
    break;

  case 57:
#line 410 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); ;}
    break;

  case 58:
#line 411 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
          (yysemantic_stack_[(3) - (1)].varDefExpr)->setInitialExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
        ;}
    break;

  case 59:
#line 416 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              VarDefExpr *v = new VarDefExpr;
              v->setName(*(yysemantic_stack_[(3) - (2)].string));
              v->setType(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
              (yyval.varDefExpr) = v;
              delete (yysemantic_stack_[(3) - (2)].string);
            ;}
    break;

  case 60:
#line 423 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
              VarDefExpr *v = new VarDefExpr;
              v->setName(*(yysemantic_stack_[(2) - (2)].string));
              (yyval.varDefExpr) = v;
              delete (yysemantic_stack_[(2) - (2)].string);
            ;}
    break;

  case 63:
#line 446 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NamedTypeExpr *n = new NamedTypeExpr;
      n->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(1) - (1)].string);
    ;}
    break;

  case 66:
#line 458 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnionTypeExpr *t = new UnionTypeExpr;
      t->setTypes(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 67:
#line 467 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 68:
#line 472 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 69:
#line 479 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExpr *t = new TupleTypeExpr;
      t->setArgs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    ;}
    break;

  case 70:
#line 488 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 71:
#line 493 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
    ;}
    break;

  case 72:
#line 499 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setExpr(shared_ptr<Node>((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = t;
    ;}
    break;

  case 73:
#line 504 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setName(*(yysemantic_stack_[(3) - (1)].string));
      t->setExpr(shared_ptr<Node>((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 74:
#line 515 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      QualifiedTypeExpr *q = new QualifiedTypeExpr;
      q->setExprs(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = q;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    ;}
    break;

  case 75:
#line 524 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    ;}
    break;

  case 76:
#line 528 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    ;}
    break;

  case 81:
#line 545 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (1)].structureQualifier); ;}
    break;

  case 82:
#line 546 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(4) - (1)].structureQualifier)->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 83:
#line 553 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("value");
      (yyval.structureQualifier) = s;
    ;}
    break;

  case 84:
#line 558 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("object");
      (yyval.structureQualifier) = s;
    ;}
    break;

  case 85:
#line 566 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); ;}
    break;

  case 86:
#line 567 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); ;}
    break;

  case 87:
#line 571 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(2) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(2) - (1)].string);
    ;}
    break;

  case 88:
#line 577 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(3) - (1)].string));
      s->setType(NodePtr((yysemantic_stack_[(3) - (2)].node)));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (1)].string);
    ;}
    break;

  case 89:
#line 588 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      (yyval.node) = i;
    ;}
    break;

  case 90:
#line 592 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      i->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    ;}
    break;

  case 91:
#line 601 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); ;}
    break;

  case 92:
#line 602 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); ;}
    break;

  case 93:
#line 606 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = new InvalidType; delete (yysemantic_stack_[(1) - (1)].string); /* dummy */ ;}
    break;

  case 94:
#line 611 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      NativeQualifier *n = new NativeQualifier;
      n->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;

  case 95:
#line 621 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].rangeQualifier); ;}
    break;

  case 96:
#line 622 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMin(*(yysemantic_stack_[(6) - (3)].string));
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMax(*(yysemantic_stack_[(6) - (5)].string));
      delete (yysemantic_stack_[(6) - (3)].string);
      delete (yysemantic_stack_[(6) - (5)].string);
    ;}
    break;

  case 97:
#line 631 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
    {
      RangeQualifier *r = new RangeQualifier;
      r->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.rangeQualifier) = r;
      delete (yysemantic_stack_[(2) - (2)].string);
    ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 1089 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.cpp"
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
  const signed char Parser::yypact_ninf_ = -59;
  const short int
  Parser::yypact_[] =
  {
       126,   124,     7,    13,   126,   -59,   -59,     3,   -59,    73,
     -59,   -59,   -59,   -59,   -59,    94,   -59,   -59,   -59,   -59,
      73,    44,    37,     4,   -11,   -59,   -59,   -59,   -59,   -59,
      -1,    29,   123,    91,   -59,    71,   -59,   127,   -59,   -59,
     128,   -59,   -59,   118,   -59,   -59,   -59,   130,   -59,   -59,
     -59,   -13,   -59,   134,   152,   109,   -59,    47,   -59,   -59,
      42,   -59,    55,   150,   151,   149,   129,   132,   131,   137,
       4,   -59,    14,   -59,   -59,   135,   -59,   -12,   138,    73,
      73,   -59,    15,   156,   -59,   162,    65,    73,   146,   -59,
     -59,   -59,   165,   -59,    55,    55,    55,    55,   -59,    55,
     -59,   137,   -59,   -59,    16,   -59,    73,   -59,    91,    91,
     -59,   -59,    11,   -59,    19,   -59,   141,   -59,    85,   -59,
     113,   -59,   -59,   -59,   -59,   153,   -59,   150,   151,   149,
     129,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   140,   -59,
     -59,   167,   109,   -59,   116,    75,   -59,   154,   -59,   -59,
     -59,   114,   -59,   -59
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     0,     2,     4,     5,     0,     6,    21,
      11,    44,    45,    46,    47,     0,    12,    23,     1,     3,
      19,     0,     0,     0,     0,    15,     7,    63,    83,    84,
       0,     0,     0,     0,    22,    61,    62,    66,    64,    65,
      74,    75,    77,     0,    78,    79,    80,    95,    13,    20,
      14,     0,    17,    29,     0,     0,    24,     0,    26,    31,
      42,    48,     0,    50,    52,    54,    56,     0,    57,     0,
       0,     8,     0,    94,    97,    63,    72,     0,     0,     0,
       0,    76,     0,     0,    16,     0,     0,    60,     0,    25,
      27,    32,     0,    43,     0,     0,     0,     0,    28,     0,
       9,     0,    93,    89,     0,    91,     0,    69,     0,     0,
      67,    68,     0,    81,     0,    85,     0,    18,    29,    36,
       0,    38,    41,    59,    30,    35,    49,    51,    53,    55,
      58,    10,    90,    92,    73,    71,    70,    87,     0,    82,
      86,     0,     0,    37,     0,     0,    88,     0,    40,    39,
      33,     0,    96,    34
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
       -59,   -59,   -59,   168,   -59,   -59,   -18,   -59,   -19,   -59,
     -59,   -21,   -59,   117,   -59,   -59,    31,    33,   -58,    98,
      83,    84,    82,    86,   -22,   -59,    -8,    69,   -59,   -59,
     -59,   -59,    43,   -59,   -59,   142,   -59,   -59,   -59,    67,
     -59,   -59,    79,   -59,   -59,   -59
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     3,     4,     5,     6,     7,    24,    51,    25,     8,
       9,    26,    57,    58,    59,    60,   120,   121,    61,    62,
      63,    64,    65,    66,   122,    68,    76,    35,    36,    37,
      38,    77,    78,    39,    40,    41,    42,    43,   114,   115,
      44,   104,   105,    45,    46,    47
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        67,    34,    52,    71,    93,    69,    20,    20,    84,   107,
      17,    22,    49,    18,    27,    85,   108,   102,   112,   102,
      70,    72,   112,    21,    21,    22,    28,    29,    30,    31,
      32,    33,    73,    88,    23,    67,   126,   103,   113,   132,
      53,   137,   139,    11,    12,    13,    14,    20,   100,    54,
      53,    91,   101,    11,    12,    13,    14,    55,    53,    54,
      56,    11,    12,    13,    14,    50,   117,    55,   118,    92,
      89,    11,    12,    13,    14,    55,    27,    54,   118,   123,
     131,    11,    12,    13,    14,    55,   119,    54,    28,    29,
      30,    31,    32,    33,    75,    55,   150,    79,   134,    16,
      11,    12,    13,    14,   138,    86,    28,    29,    30,    31,
      32,    33,    53,    48,   142,    11,    12,    13,    14,   118,
     148,    54,    11,    12,    13,    14,    74,    10,    54,    55,
      11,    12,    13,    14,   143,   153,    55,     1,    15,     2,
      82,   144,   144,    28,    29,    30,    31,    32,   110,   111,
      83,   135,   136,    80,    86,    87,    94,    96,    95,    22,
     116,    97,    98,    99,   106,    20,   109,   124,   125,   141,
     146,   147,    19,   145,    90,   152,   151,   149,   127,   129,
     128,   140,    81,   133,     0,   130
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        22,     9,    21,    24,    62,    23,     3,     3,    21,    21,
       3,    22,    20,     0,     3,    28,    28,     3,     3,     3,
      31,    22,     3,    20,    20,    22,    15,    16,    17,    18,
      19,    20,     3,    55,    31,    57,    94,    23,    23,    23,
       3,    30,    23,     6,     7,     8,     9,     3,    69,    12,
       3,     9,    70,     6,     7,     8,     9,    20,     3,    12,
      23,     6,     7,     8,     9,    21,    85,    20,     3,    27,
      23,     6,     7,     8,     9,    20,     3,    12,     3,    87,
     101,     6,     7,     8,     9,    20,    21,    12,    15,    16,
      17,    18,    19,    20,     3,    20,    21,    26,   106,     1,
       6,     7,     8,     9,   112,    20,    15,    16,    17,    18,
      19,    20,     3,    15,    29,     6,     7,     8,     9,     3,
     142,    12,     6,     7,     8,     9,     3,     3,    12,    20,
       6,     7,     8,     9,    21,    21,    20,    11,    14,    13,
      22,    28,    28,    15,    16,    17,    18,    19,    79,    80,
      20,   108,   109,    26,    20,     3,     6,     8,     7,    22,
       4,    32,    30,    32,    29,     3,    28,    21,     3,    28,
      30,     4,     4,    20,    57,    21,   145,   144,    95,    97,
      96,   114,    40,   104,    -1,    99
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    11,    13,    34,    35,    36,    37,    38,    42,    43,
       3,     6,     7,     8,     9,    14,    52,     3,     0,    36,
       3,    20,    22,    31,    39,    41,    44,     3,    15,    16,
      17,    18,    19,    20,    59,    60,    61,    62,    63,    66,
      67,    68,    69,    70,    73,    76,    77,    78,    52,    59,
      21,    40,    41,     3,    12,    20,    23,    45,    46,    47,
      48,    51,    52,    53,    54,    55,    56,    57,    58,    39,
      31,    44,    22,     3,     3,     3,    59,    64,    65,    26,
      26,    68,    22,    20,    21,    28,    20,     3,    57,    23,
      46,     9,    27,    51,     6,     7,     8,    32,    30,    32,
      44,    39,     3,    23,    74,    75,    29,    21,    28,    28,
      60,    60,     3,    23,    71,    72,     4,    41,     3,    21,
      49,    50,    57,    59,    21,     3,    51,    53,    54,    55,
      56,    44,    23,    75,    59,    65,    65,    30,    59,    23,
      72,    28,    29,    21,    28,    20,    30,     4,    57,    50,
      21,    49,    21,    21
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
     285,   286,   287
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    33,    34,    35,    35,    36,    36,    37,    37,    37,
      37,    38,    38,    38,    39,    39,    39,    40,    40,    41,
      41,    42,    42,    43,    44,    44,    45,    45,    46,    47,
      47,    48,    48,    48,    48,    48,    48,    48,    49,    49,
      50,    50,    51,    51,    52,    52,    52,    52,    53,    53,
      54,    54,    55,    55,    56,    56,    57,    57,    57,    58,
      58,    59,    59,    60,    60,    60,    61,    62,    62,    63,
      64,    64,    65,    65,    66,    67,    67,    68,    68,    68,
      68,    69,    69,    70,    70,    71,    71,    72,    72,    73,
      73,    74,    74,    75,    76,    77,    77,    78
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     2,     1,     1,     1,     2,     3,     4,
       5,     2,     2,     3,     2,     1,     3,     1,     3,     1,
       2,     1,     2,     2,     2,     3,     1,     2,     2,     1,
       3,     1,     2,     5,     6,     3,     3,     4,     1,     3,
       3,     1,     1,     2,     1,     1,     1,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     1,     3,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     1,     3,     1,     1,     2,     1,     1,     1,
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
  "ADDITIVE_OPERATOR", "RELATIONAL_OPERATOR", "OPERATOR", "\"symbol\"",
  "\"func keyword\"", "\"var keyword\"", "\"type keyword\"",
  "\"unary keyword\"", "\"value keyword\"", "\"object keyword\"",
  "\"interface keyword\"", "\"native keyword\"", "\"range keyword\"",
  "\"opening paranthesis (\"", "\"closing paranthesis )\"",
  "\"opening braces {\"", "\"closing braces }\"", "\"opening bracket [\"",
  "\"closing bracket ]\"", "\"vertical pipe |\"", "\".\"", "\",\"",
  "\":\"", "\";\"", "\"right arrow ->\"", "\"assignment operator =\"",
  "$accept", "root", "root_stmts", "root_stmt", "func_decl",
  "func_decl_name", "func_args_tuple", "func_args", "func_arg",
  "type_decl", "type_decl_name", "body", "stmts", "stmt", "primary_expr",
  "postfix_expr", "call_args", "call_arg", "prefix_expr", "any_operator",
  "multiplicative_expr", "additive_expr", "relational_expr",
  "assignment_expr", "expr", "var_expr", "typeexpr", "nonunion_typeexpr",
  "union_typeexpr", "union_typeexprs", "tuple_typeexpr",
  "tuple_typeexpr_args", "tuple_typeexpr_arg", "qualified_typeexpr",
  "qualified_typeexpr_qualifiers", "qualified_typeexpr_qualifier",
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
        34,     0,    -1,    35,    -1,    35,    36,    -1,    36,    -1,
      37,    -1,    42,    -1,    38,    44,    -1,    38,    39,    44,
      -1,    38,    31,    39,    44,    -1,    38,    39,    31,    39,
      44,    -1,    11,     3,    -1,    11,    52,    -1,    11,    14,
      52,    -1,    20,    21,    -1,    41,    -1,    20,    40,    21,
      -1,    41,    -1,    40,    28,    41,    -1,     3,    -1,     3,
      59,    -1,    43,    -1,    43,    59,    -1,    13,     3,    -1,
      22,    23,    -1,    22,    45,    23,    -1,    46,    -1,    45,
      46,    -1,    57,    30,    -1,     3,    -1,    20,    57,    21,
      -1,    47,    -1,    48,     9,    -1,    48,    27,     3,    20,
      21,    -1,    48,    27,     3,    20,    49,    21,    -1,    48,
      27,     3,    -1,     3,    20,    21,    -1,     3,    20,    49,
      21,    -1,    50,    -1,    49,    28,    50,    -1,     3,    29,
      57,    -1,    57,    -1,    48,    -1,    52,    51,    -1,     6,
      -1,     7,    -1,     8,    -1,     9,    -1,    51,    -1,    53,
       6,    51,    -1,    53,    -1,    54,     7,    53,    -1,    54,
      -1,    55,     8,    54,    -1,    55,    -1,    56,    32,    55,
      -1,    56,    -1,    58,    -1,    58,    32,    56,    -1,    12,
       3,    59,    -1,    12,     3,    -1,    60,    -1,    61,    -1,
       3,    -1,    63,    -1,    66,    -1,    62,    -1,    60,    26,
      60,    -1,    62,    26,    60,    -1,    20,    64,    21,    -1,
      65,    28,    65,    -1,    64,    28,    65,    -1,    59,    -1,
       3,    29,    59,    -1,    67,    -1,    68,    -1,    67,    68,
      -1,    69,    -1,    73,    -1,    76,    -1,    77,    -1,    70,
      22,    23,    -1,    70,    22,    71,    23,    -1,    15,    -1,
      16,    -1,    72,    -1,    71,    72,    -1,     3,    30,    -1,
       3,    59,    30,    -1,    17,    22,    23,    -1,    17,    22,
      74,    23,    -1,    75,    -1,    74,    75,    -1,     3,    -1,
      18,     3,    -1,    78,    -1,    78,    20,     4,    28,     4,
      21,    -1,    19,     3,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    10,    12,    14,    17,    21,
      26,    32,    35,    38,    42,    45,    47,    51,    53,    57,
      59,    62,    64,    67,    70,    73,    77,    79,    82,    85,
      87,    91,    93,    96,   102,   109,   113,   117,   122,   124,
     128,   132,   134,   136,   139,   141,   143,   145,   147,   149,
     153,   155,   159,   161,   165,   167,   171,   173,   175,   179,
     183,   186,   188,   190,   192,   194,   196,   198,   202,   206,
     210,   214,   218,   220,   224,   226,   228,   231,   233,   235,
     237,   239,   243,   248,   250,   252,   254,   257,   260,   264,
     268,   273,   275,   278,   280,   283,   285,   292
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   123,   123,   126,   127,   130,   133,   139,   142,   147,
     152,   162,   167,   172,   180,   181,   185,   191,   195,   201,
     207,   218,   219,   227,   235,   239,   247,   251,   256,   267,
     273,   277,   278,   286,   293,   302,   309,   315,   326,   330,
     336,   343,   351,   352,   361,   361,   361,   361,   364,   365,
     376,   377,   388,   389,   400,   401,   409,   410,   411,   416,
     423,   441,   442,   446,   452,   453,   458,   467,   472,   479,
     488,   493,   499,   504,   515,   524,   528,   537,   538,   539,
     540,   545,   546,   553,   558,   566,   567,   571,   577,   588,
     592,   601,   602,   606,   611,   621,   622,   631
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
      25,    26,    27,    28,    29,    30,    31,    32
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 185;
  const int Parser::yynnts_ = 46;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 18;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 33;

  const unsigned int Parser::yyuser_token_number_max_ = 287;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace driver

#line 639 "/Users/fabian/Documents/Programmieren/Maxwell/cpp/source/driver/Parser.yy"
 /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}
