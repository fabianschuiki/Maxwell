/* A Bison parser, made by GNU Bison 2.5.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* First part of user declarations.  */

/* Line 293 of lalr1.cc  */
#line 3 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"

#include <iostream>
#include <string>
#include <vector>
#include <ast/nodes/ast.hpp>
#include <boost/smart_ptr.hpp>

using namespace ast;
using boost::shared_ptr;
typedef std::vector<NodePtr> Nodes;


/* Line 293 of lalr1.cc  */
#line 54 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"


#include "Parser.hpp"

/* User implementation prologue.  */

/* Line 299 of lalr1.cc  */
#line 117 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"

#include "Driver.hpp"
#include "Scanner.hpp"

/* This connects the Bison parser to the Flex scanner. */
#undef yylex
#define yylex driver.lexer->lex

using std::cout;
using std::endl;


/* Line 299 of lalr1.cc  */
#line 76 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"

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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                               \
 do                                                                    \
   if (N)                                                              \
     {                                                                 \
       (Current).begin = YYRHSLOC (Rhs, 1).begin;                      \
       (Current).end   = YYRHSLOC (Rhs, N).end;                        \
     }                                                                 \
   else                                                                \
     {                                                                 \
       (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;        \
     }                                                                 \
 while (false)
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

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

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace driver {

/* Line 382 of lalr1.cc  */
#line 162 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"

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


  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
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
#endif

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

/* Line 480 of lalr1.cc  */
#line 110 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };

/* Line 480 of lalr1.cc  */
#line 267 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 4: /* "\"number constant\"" */

/* Line 480 of lalr1.cc  */
#line 110 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };

/* Line 480 of lalr1.cc  */
#line 276 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 5: /* "\"string constant\"" */

/* Line 480 of lalr1.cc  */
#line 110 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };

/* Line 480 of lalr1.cc  */
#line 285 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 6: /* "MULTIPLICATIVE_OPERATOR" */

/* Line 480 of lalr1.cc  */
#line 110 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };

/* Line 480 of lalr1.cc  */
#line 294 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 7: /* "ADDITIVE_OPERATOR" */

/* Line 480 of lalr1.cc  */
#line 110 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };

/* Line 480 of lalr1.cc  */
#line 303 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 8: /* "RELATIONAL_OPERATOR" */

/* Line 480 of lalr1.cc  */
#line 110 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };

/* Line 480 of lalr1.cc  */
#line 312 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"
	break;
      case 12: /* "OPERATOR" */

/* Line 480 of lalr1.cc  */
#line 110 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
	{ delete (yyvaluep->string); };

/* Line 480 of lalr1.cc  */
#line 321 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"
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

#if YYDEBUG
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
#endif

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 565 of lalr1.cc  */
#line 28 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
{
	// initialize the location object
	yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}

/* Line 565 of lalr1.cc  */
#line 419 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"

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

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
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
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
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

/* Line 690 of lalr1.cc  */
#line 139 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(NodePtr((yysemantic_stack_[(1) - (1)].node)));
            }
    break;

  case 6:

/* Line 690 of lalr1.cc  */
#line 142 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
              driver.add(NodePtr((yysemantic_stack_[(1) - (1)].node)));
            }
    break;

  case 7:

/* Line 690 of lalr1.cc  */
#line 149 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].funcDef)->setBody(NodePtr((yysemantic_stack_[(2) - (2)].node)));
      (yysemantic_stack_[(2) - (1)].funcDef)->setImplOut(false);
    }
    break;

  case 8:

/* Line 690 of lalr1.cc  */
#line 153 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].funcDef)->setBody(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yysemantic_stack_[(3) - (1)].funcDef)->setImplOut(true);
    }
    break;

  case 10:

/* Line 690 of lalr1.cc  */
#line 161 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].funcDef)->setIn(*(yysemantic_stack_[(2) - (2)].nodes));
      delete (yysemantic_stack_[(2) - (2)].nodes);
    }
    break;

  case 11:

/* Line 690 of lalr1.cc  */
#line 165 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].funcDef)->setOut(*(yysemantic_stack_[(3) - (3)].nodes));
      delete (yysemantic_stack_[(3) - (3)].nodes);
    }
    break;

  case 12:

/* Line 690 of lalr1.cc  */
#line 169 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(4) - (1)].funcDef)->setIn(*(yysemantic_stack_[(4) - (2)].nodes));
      (yysemantic_stack_[(4) - (1)].funcDef)->setOut(*(yysemantic_stack_[(4) - (4)].nodes));
      delete (yysemantic_stack_[(4) - (2)].nodes);
      delete (yysemantic_stack_[(4) - (4)].nodes);
     }
    break;

  case 13:

/* Line 690 of lalr1.cc  */
#line 178 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName(*(yysemantic_stack_[(2) - (2)].string)); delete (yysemantic_stack_[(2) - (2)].string);
      (yyval.funcDef) = d;
    }
    break;

  case 14:

/* Line 690 of lalr1.cc  */
#line 183 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName(*(yysemantic_stack_[(2) - (2)].string)); delete (yysemantic_stack_[(2) - (2)].string);
      (yyval.funcDef) = d;
    }
    break;

  case 15:

/* Line 690 of lalr1.cc  */
#line 188 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncDef* d = new FuncDef;
      d->setName("_" + *(yysemantic_stack_[(3) - (3)].string)); delete (yysemantic_stack_[(3) - (3)].string);
      (yyval.funcDef) = d;
    }
    break;

  case 16:

/* Line 690 of lalr1.cc  */
#line 196 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; }
    break;

  case 17:

/* Line 690 of lalr1.cc  */
#line 197 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    }
    break;

  case 18:

/* Line 690 of lalr1.cc  */
#line 201 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = (yysemantic_stack_[(3) - (2)].nodes);
    }
    break;

  case 19:

/* Line 690 of lalr1.cc  */
#line 207 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    }
    break;

  case 20:

/* Line 690 of lalr1.cc  */
#line 211 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    }
    break;

  case 21:

/* Line 690 of lalr1.cc  */
#line 217 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncArg *a = new FuncArg;
      a->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = a;
      delete (yysemantic_stack_[(1) - (1)].string);
    }
    break;

  case 22:

/* Line 690 of lalr1.cc  */
#line 223 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      FuncArg *a = new FuncArg;
      a->setName(*(yysemantic_stack_[(2) - (1)].string));
      a->setTypeExpr(NodePtr((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(2) - (1)].string);
    }
    break;

  case 23:

/* Line 690 of lalr1.cc  */
#line 234 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].typeDef); }
    break;

  case 24:

/* Line 690 of lalr1.cc  */
#line 235 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].typeDef)->setType(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    }
    break;

  case 25:

/* Line 690 of lalr1.cc  */
#line 243 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      TypeDef *t = new TypeDef;
      t->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.typeDef) = t;
      delete (yysemantic_stack_[(2) - (2)].string);
    }
    break;

  case 26:

/* Line 690 of lalr1.cc  */
#line 260 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      IdentifierExpr *i = new IdentifierExpr;
      i->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = i;
      delete (yysemantic_stack_[(1) - (1)].string);
    }
    break;

  case 27:

/* Line 690 of lalr1.cc  */
#line 266 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (2)].node); }
    break;

  case 28:

/* Line 690 of lalr1.cc  */
#line 267 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
     NumberConstExpr *n = new NumberConstExpr;
     n->setValue(*(yysemantic_stack_[(1) - (1)].string));
     (yyval.node) = n;
     delete (yysemantic_stack_[(1) - (1)].string);
    }
    break;

  case 29:

/* Line 690 of lalr1.cc  */
#line 273 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      StringConstExpr *s = new StringConstExpr;
      s->setValue(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(1) - (1)].string);
    }
    break;

  case 30:

/* Line 690 of lalr1.cc  */
#line 279 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { /* array literals */
      ArrayConstExpr *a = new ArrayConstExpr;
      a->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    }
    break;

  case 31:

/* Line 690 of lalr1.cc  */
#line 285 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { /* set literals */
      SetConstExpr *s = new SetConstExpr;
      s->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    }
    break;

  case 32:

/* Line 690 of lalr1.cc  */
#line 291 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { /* map literals */
      MapConstExpr *m = new MapConstExpr;
      m->setPairs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = m;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    }
    break;

  case 34:

/* Line 690 of lalr1.cc  */
#line 301 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    }
    break;

  case 35:

/* Line 690 of lalr1.cc  */
#line 305 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    }
    break;

  case 36:

/* Line 690 of lalr1.cc  */
#line 310 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      MapConstExprPair *p = new MapConstExprPair;
      p->setKey(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      p->setValue(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = p;
    }
    break;

  case 37:

/* Line 690 of lalr1.cc  */
#line 319 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    }
    break;

  case 38:

/* Line 690 of lalr1.cc  */
#line 325 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExpr *i = new IfCaseExpr;
      i->setConds(*(yysemantic_stack_[(6) - (2)].nodes));
      i->setOtherwise(NodePtr((yysemantic_stack_[(6) - (4)].node)));
      (yyval.node) = i;
      delete (yysemantic_stack_[(6) - (2)].nodes);
    }
    break;

  case 39:

/* Line 690 of lalr1.cc  */
#line 334 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    }
    break;

  case 40:

/* Line 690 of lalr1.cc  */
#line 338 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    }
    break;

  case 41:

/* Line 690 of lalr1.cc  */
#line 343 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfCaseExprCond *c = new IfCaseExprCond;
      c->setExpr(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      c->setCond(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = c;
    }
    break;

  case 42:

/* Line 690 of lalr1.cc  */
#line 352 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfExpr *s = new IfExpr;
      s->setCond(NodePtr((yysemantic_stack_[(5) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
      (yyval.node) = s;
    }
    break;

  case 43:

/* Line 690 of lalr1.cc  */
#line 358 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      IfExpr *s = new IfExpr;
      s->setCond(NodePtr((yysemantic_stack_[(7) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(7) - (5)].node)));
      s->setElseExpr(NodePtr((yysemantic_stack_[(7) - (7)].node)));
      (yyval.node) = s;
    }
    break;

  case 44:

/* Line 690 of lalr1.cc  */
#line 368 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      ForExpr *s = new ForExpr;
      s->setCond(NodePtr((yysemantic_stack_[(5) - (3)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(5) - (5)].node)));
      (yyval.node) = s;
    }
    break;

  case 45:

/* Line 690 of lalr1.cc  */
#line 374 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      ForExpr *s = new ForExpr;
      s->setInit(NodePtr((yysemantic_stack_[(9) - (3)].node)));
      s->setCond(NodePtr((yysemantic_stack_[(9) - (5)].node)));
      s->setStep(NodePtr((yysemantic_stack_[(9) - (7)].node)));
      s->setBody(NodePtr((yysemantic_stack_[(9) - (9)].node)));
      (yyval.node) = s;
    }
    break;

  case 48:

/* Line 690 of lalr1.cc  */
#line 390 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      BlockExpr *b = new BlockExpr;
      (yyval.node) = b;
    }
    break;

  case 49:

/* Line 690 of lalr1.cc  */
#line 394 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      BlockExpr *b = new BlockExpr;
      b->setExprs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = b;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    }
    break;

  case 50:

/* Line 690 of lalr1.cc  */
#line 402 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    }
    break;

  case 51:

/* Line 690 of lalr1.cc  */
#line 406 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    }
    break;

  case 55:

/* Line 690 of lalr1.cc  */
#line 417 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(true);
      u->setOperatorName(*(yysemantic_stack_[(2) - (2)].string));
      u->setExpr(NodePtr((yysemantic_stack_[(2) - (1)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (2)].string);
    }
    break;

  case 56:

/* Line 690 of lalr1.cc  */
#line 425 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(5) - (3)].string));
      c->setContext(NodePtr((yysemantic_stack_[(5) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(5) - (3)].string);
    }
    break;

  case 57:

/* Line 690 of lalr1.cc  */
#line 432 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(6) - (3)].string));
      c->setArgs(*(yysemantic_stack_[(6) - (5)].nodes));
      c->setContext(NodePtr((yysemantic_stack_[(6) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(6) - (3)].string);
      delete (yysemantic_stack_[(6) - (5)].nodes);
    }
    break;

  case 58:

/* Line 690 of lalr1.cc  */
#line 441 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (3)].string));
      c->setContext(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (3)].string);
    }
    break;

  case 59:

/* Line 690 of lalr1.cc  */
#line 448 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(3) - (1)].string));
      (yyval.node) = c;
      delete (yysemantic_stack_[(3) - (1)].string);
    }
    break;

  case 60:

/* Line 690 of lalr1.cc  */
#line 454 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExpr *c = new CallExpr;
      c->setName(*(yysemantic_stack_[(4) - (1)].string));
      c->setArgs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = c;
      delete (yysemantic_stack_[(4) - (1)].string);
      delete (yysemantic_stack_[(4) - (3)].nodes);
    }
    break;

  case 61:

/* Line 690 of lalr1.cc  */
#line 465 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    }
    break;

  case 62:

/* Line 690 of lalr1.cc  */
#line 469 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    }
    break;

  case 63:

/* Line 690 of lalr1.cc  */
#line 475 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setName(*(yysemantic_stack_[(3) - (1)].string));
      a->setExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = a;
      delete (yysemantic_stack_[(3) - (1)].string);
    }
    break;

  case 64:

/* Line 690 of lalr1.cc  */
#line 482 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      CallExprArg *a = new CallExprArg;
      a->setExpr(NodePtr((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = a;
    }
    break;

  case 66:

/* Line 690 of lalr1.cc  */
#line 491 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnaryOpExpr *u = new UnaryOpExpr;
      u->setPostfix(false);
      u->setOperatorName(*(yysemantic_stack_[(2) - (1)].string));
      u->setExpr(NodePtr((yysemantic_stack_[(2) - (2)].node)));
      (yyval.node) = u;
      delete (yysemantic_stack_[(2) - (1)].string);
    }
    break;

  case 72:

/* Line 690 of lalr1.cc  */
#line 504 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    }
    break;

  case 74:

/* Line 690 of lalr1.cc  */
#line 516 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    }
    break;

  case 76:

/* Line 690 of lalr1.cc  */
#line 528 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    }
    break;

  case 78:

/* Line 690 of lalr1.cc  */
#line 540 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    }
    break;

  case 80:

/* Line 690 of lalr1.cc  */
#line 552 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    }
    break;

  case 82:

/* Line 690 of lalr1.cc  */
#line 564 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      BinaryOpExpr *e = new BinaryOpExpr;
      e->setOperatorName(*(yysemantic_stack_[(3) - (2)].string));
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
      delete (yysemantic_stack_[(3) - (2)].string);
    }
    break;

  case 84:

/* Line 690 of lalr1.cc  */
#line 576 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      AssignmentExpr *e = new AssignmentExpr;
      e->setLhs(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      e->setRhs(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = e;
    }
    break;

  case 85:

/* Line 690 of lalr1.cc  */
#line 585 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*(yysemantic_stack_[(3) - (2)].string));
      v->setTypeExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.varDefExpr) = v;
      delete (yysemantic_stack_[(3) - (2)].string);
    }
    break;

  case 86:

/* Line 690 of lalr1.cc  */
#line 592 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      VarDefExpr *v = new VarDefExpr;
      v->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.varDefExpr) = v;
      delete (yysemantic_stack_[(2) - (2)].string);
    }
    break;

  case 88:

/* Line 690 of lalr1.cc  */
#line 602 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].node); }
    break;

  case 89:

/* Line 690 of lalr1.cc  */
#line 603 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].varDefExpr)->setInitialExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    }
    break;

  case 94:

/* Line 690 of lalr1.cc  */
#line 618 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    }
    break;

  case 95:

/* Line 690 of lalr1.cc  */
#line 622 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    }
    break;

  case 98:

/* Line 690 of lalr1.cc  */
#line 642 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      NamedTypeExpr *n = new NamedTypeExpr;
      n->setName(*(yysemantic_stack_[(1) - (1)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(1) - (1)].string);
    }
    break;

  case 99:

/* Line 690 of lalr1.cc  */
#line 648 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.node) = new NilTypeExpr;
    }
    break;

  case 103:

/* Line 690 of lalr1.cc  */
#line 658 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      UnionTypeExpr *t = new UnionTypeExpr;
      t->setTypes(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    }
    break;

  case 104:

/* Line 690 of lalr1.cc  */
#line 667 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (1)].node)));
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    }
    break;

  case 105:

/* Line 690 of lalr1.cc  */
#line 672 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    }
    break;

  case 106:

/* Line 690 of lalr1.cc  */
#line 679 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExpr *t = new TupleTypeExpr;
      t->setArgs(*(yysemantic_stack_[(3) - (2)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (2)].nodes);
    }
    break;

  case 107:

/* Line 690 of lalr1.cc  */
#line 688 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    }
    break;

  case 108:

/* Line 690 of lalr1.cc  */
#line 692 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    }
    break;

  case 109:

/* Line 690 of lalr1.cc  */
#line 698 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setExpr(NodePtr((yysemantic_stack_[(1) - (1)].node)));
      (yyval.node) = t;
    }
    break;

  case 110:

/* Line 690 of lalr1.cc  */
#line 703 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      TupleTypeExprArg *t = new TupleTypeExprArg;
      t->setName(*(yysemantic_stack_[(3) - (1)].string));
      t->setExpr(NodePtr((yysemantic_stack_[(3) - (3)].node)));
      (yyval.node) = t;
      delete (yysemantic_stack_[(3) - (1)].string);
    }
    break;

  case 111:

/* Line 690 of lalr1.cc  */
#line 714 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      QualifiedTypeExpr *q = new QualifiedTypeExpr;
      q->setExprs(*(yysemantic_stack_[(1) - (1)].nodes));
      (yyval.node) = q;
      delete (yysemantic_stack_[(1) - (1)].nodes);
    }
    break;

  case 112:

/* Line 690 of lalr1.cc  */
#line 723 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    }
    break;

  case 113:

/* Line 690 of lalr1.cc  */
#line 727 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node)));
    }
    break;

  case 114:

/* Line 690 of lalr1.cc  */
#line 734 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      SpecializedTypeExpr *t = new SpecializedTypeExpr;
      t->setExpr(NodePtr((yysemantic_stack_[(4) - (1)].node)));
      t->setSpecExprs(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = t;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    }
    break;

  case 115:

/* Line 690 of lalr1.cc  */
#line 743 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yyval.nodes) = new Nodes;
      (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node)));
    }
    break;

  case 116:

/* Line 690 of lalr1.cc  */
#line 747 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(3) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(3) - (3)].node)));
    }
    break;

  case 121:

/* Line 690 of lalr1.cc  */
#line 764 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(3) - (1)].structureQualifier); }
    break;

  case 122:

/* Line 690 of lalr1.cc  */
#line 765 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(4) - (1)].structureQualifier)->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      delete (yysemantic_stack_[(4) - (3)].nodes);
    }
    break;

  case 123:

/* Line 690 of lalr1.cc  */
#line 772 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("value");
      (yyval.structureQualifier) = s;
    }
    break;

  case 124:

/* Line 690 of lalr1.cc  */
#line 777 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifier *s = new StructureQualifier;
      s->setMode("object");
      (yyval.structureQualifier) = s;
    }
    break;

  case 125:

/* Line 690 of lalr1.cc  */
#line 785 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); }
    break;

  case 126:

/* Line 690 of lalr1.cc  */
#line 786 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); }
    break;

  case 127:

/* Line 690 of lalr1.cc  */
#line 790 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(2) - (1)].string));
      (yyval.node) = s;
      delete (yysemantic_stack_[(2) - (1)].string);
    }
    break;

  case 128:

/* Line 690 of lalr1.cc  */
#line 796 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      StructureQualifierMember *s = new StructureQualifierMember;
      s->setName(*(yysemantic_stack_[(3) - (1)].string));
      s->setType(NodePtr((yysemantic_stack_[(3) - (2)].node)));
      (yyval.node) = s;
      delete (yysemantic_stack_[(3) - (1)].string);
    }
    break;

  case 129:

/* Line 690 of lalr1.cc  */
#line 807 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      (yyval.node) = i;
    }
    break;

  case 130:

/* Line 690 of lalr1.cc  */
#line 811 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      InterfaceQualifier *i = new InterfaceQualifier;
      i->setStmts(*(yysemantic_stack_[(4) - (3)].nodes));
      (yyval.node) = i;
      delete (yysemantic_stack_[(4) - (3)].nodes);
    }
    break;

  case 131:

/* Line 690 of lalr1.cc  */
#line 820 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.nodes) = new Nodes; (yyval.nodes)->push_back(NodePtr((yysemantic_stack_[(1) - (1)].node))); }
    break;

  case 132:

/* Line 690 of lalr1.cc  */
#line 821 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yysemantic_stack_[(2) - (1)].nodes)->push_back(NodePtr((yysemantic_stack_[(2) - (2)].node))); }
    break;

  case 133:

/* Line 690 of lalr1.cc  */
#line 825 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = new InvalidType; delete (yysemantic_stack_[(1) - (1)].string); /* dummy */ }
    break;

  case 134:

/* Line 690 of lalr1.cc  */
#line 830 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      NativeQualifier *n = new NativeQualifier;
      n->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.node) = n;
      delete (yysemantic_stack_[(2) - (2)].string);
    }
    break;

  case 135:

/* Line 690 of lalr1.cc  */
#line 840 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    { (yyval.node) = (yysemantic_stack_[(1) - (1)].rangeQualifier); }
    break;

  case 136:

/* Line 690 of lalr1.cc  */
#line 841 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMin(*(yysemantic_stack_[(6) - (3)].string));
      (yysemantic_stack_[(6) - (1)].rangeQualifier)->setMax(*(yysemantic_stack_[(6) - (5)].string));
      delete (yysemantic_stack_[(6) - (3)].string);
      delete (yysemantic_stack_[(6) - (5)].string);
    }
    break;

  case 137:

/* Line 690 of lalr1.cc  */
#line 850 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
    {
      RangeQualifier *r = new RangeQualifier;
      r->setName(*(yysemantic_stack_[(2) - (2)].string));
      (yyval.rangeQualifier) = r;
      delete (yysemantic_stack_[(2) - (2)].string);
    }
    break;



/* Line 690 of lalr1.cc  */
#line 1626 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"
	default:
          break;
      }
    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
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
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
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

    /* Else will try to reuse lookahead token after shifting the error
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

    yyerror_range[1] = yylocation_stack_[yylen - 1];
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
	if (!yy_pact_value_is_default_ (yyn))
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

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

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
  Parser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = 0;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
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

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
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
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
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
	       << " (line " << yylno << "):" << std::endl;
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


} // driver

/* Line 1136 of lalr1.cc  */
#line 2371 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.cpp"


/* Line 1138 of lalr1.cc  */
#line 858 "/home/fabian/Documents/Maxwell/cpp/source/driver/Parser.yy"
 /*** Additional Code ***/

void driver::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}
