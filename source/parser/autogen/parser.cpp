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


#include "parser.h"

/* User implementation prologue.  */
#line 109 "../parser.yy"

#include "../../driver.h"
#include "../../scanner/scanner.h"
#undef yylex
#define yylex driver.scanner->lex


/* Line 317 of lalr1.cc.  */
#line 49 "parser.cpp"

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

namespace Maxwell
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
  Parser::Parser (class Driver & driver_yyarg)
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
    #line 25 "../parser.yy"
{
	//Initialize the location object.
	yylloc.begin.filename = yylloc.end.filename = &driver.streamName;
}
  /* Line 555 of yacc.c.  */
#line 286 "parser.cpp"
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
	  case 2:
#line 123 "../parser.yy"
    { driver.programBlock = (yysemantic_stack_[(1) - (1)].block); ;}
    break;

  case 3:
#line 126 "../parser.yy"
    { (yyval.block) = new Block(); (yyval.block)->statements.push_back((yysemantic_stack_[(1) - (1)].stmt)); ;}
    break;

  case 4:
#line 127 "../parser.yy"
    { (yysemantic_stack_[(2) - (1)].block)->statements.push_back((yysemantic_stack_[(2) - (2)].stmt)); ;}
    break;

  case 5:
#line 132 "../parser.yy"
    { (yyval.stmt) = (yysemantic_stack_[(2) - (1)].class_def); ;}
    break;

  case 6:
#line 133 "../parser.yy"
    { (yyval.stmt) = (yysemantic_stack_[(1) - (1)].class_def); ;}
    break;

  case 7:
#line 139 "../parser.yy"
    { (yyval.ident) = new Identifier(*(yysemantic_stack_[(1) - (1)].string)); delete (yysemantic_stack_[(1) - (1)].string); ;}
    break;

  case 8:
#line 142 "../parser.yy"
    { (yyval.idents) = new Identifiers(); (yyval.idents)->push_back((yysemantic_stack_[(1) - (1)].ident)); ;}
    break;

  case 9:
#line 143 "../parser.yy"
    { (yysemantic_stack_[(3) - (1)].idents)->push_back((yysemantic_stack_[(3) - (3)].ident)); ;}
    break;

  case 10:
#line 154 "../parser.yy"
    {
	(yyval.class_def) = new ClassDefinition();
	(yyval.class_def)->name = (yysemantic_stack_[(2) - (2)].ident);
 ;}
    break;

  case 11:
#line 158 "../parser.yy"
    {
	(yyval.class_def) = new ClassDefinition();
	(yyval.class_def)->name = (yysemantic_stack_[(5) - (2)].ident);
	(yyval.class_def)->interfaces = (yysemantic_stack_[(5) - (4)].idents);
 ;}
    break;

  case 12:
#line 163 "../parser.yy"
    {
	(yyval.class_def) = new ClassDefinition();
	(yyval.class_def)->name = (yysemantic_stack_[(4) - (2)].ident);
	(yyval.class_def)->super = (yysemantic_stack_[(4) - (4)].ident);
 ;}
    break;

  case 13:
#line 168 "../parser.yy"
    {
	(yyval.class_def) = new ClassDefinition();
	(yyval.class_def)->name = (yysemantic_stack_[(7) - (2)].ident);
	(yyval.class_def)->super = (yysemantic_stack_[(7) - (4)].ident);
	(yyval.class_def)->interfaces = (yysemantic_stack_[(7) - (6)].idents);
 ;}
    break;

  case 14:
#line 179 "../parser.yy"
    { (yyval.class_def) = (yysemantic_stack_[(3) - (1)].class_def); ;}
    break;

  case 15:
#line 180 "../parser.yy"
    { (yyval.class_def) = (yysemantic_stack_[(4) - (1)].class_def); (yyval.class_def)->statements = (yysemantic_stack_[(4) - (3)].block); ;}
    break;

  case 16:
#line 185 "../parser.yy"
    { (yyval.block) = new Block(); (yyval.block)->statements.push_back((yysemantic_stack_[(1) - (1)].stmt)); ;}
    break;

  case 17:
#line 186 "../parser.yy"
    { (yysemantic_stack_[(2) - (1)].block)->statements.push_back((yysemantic_stack_[(2) - (2)].stmt)); ;}
    break;

  case 18:
#line 189 "../parser.yy"
    { (yyval.stmt) = (yysemantic_stack_[(2) - (1)].func_def); ;}
    break;

  case 19:
#line 190 "../parser.yy"
    { (yyval.stmt) = (yysemantic_stack_[(1) - (1)].func_def); ;}
    break;

  case 20:
#line 191 "../parser.yy"
    { (yyval.stmt) = (yysemantic_stack_[(2) - (1)].var_def); ;}
    break;

  case 21:
#line 200 "../parser.yy"
    { (yyval.func_def) = (yysemantic_stack_[(2) - (2)].func_def); (yysemantic_stack_[(2) - (2)].func_def)->shared = true; ;}
    break;

  case 22:
#line 201 "../parser.yy"
    { (yyval.func_def) = (yysemantic_stack_[(2) - (2)].func_def); (yysemantic_stack_[(2) - (2)].func_def)->shared = false; ;}
    break;

  case 23:
#line 204 "../parser.yy"
    {
	(yyval.func_def) = new FunctionDefinition();
	(yyval.func_def)->returnType = (yysemantic_stack_[(2) - (1)].expr);
	(yyval.func_def)->arguments = (yysemantic_stack_[(2) - (2)].func_args);
 ;}
    break;

  case 24:
#line 214 "../parser.yy"
    {
	FunctionArgument * arg = new FunctionArgument();
	arg->name = (yysemantic_stack_[(1) - (1)].ident);
	(yyval.func_args) = new FunctionArguments();
	(yyval.func_args)->push_back(arg);
 ;}
    break;

  case 25:
#line 220 "../parser.yy"
    { (yyval.func_args) = (yysemantic_stack_[(1) - (1)].func_args); ;}
    break;

  case 26:
#line 223 "../parser.yy"
    { (yyval.func_args) = new FunctionArguments(); (yyval.func_args)->push_back((yysemantic_stack_[(1) - (1)].func_arg)); ;}
    break;

  case 27:
#line 224 "../parser.yy"
    { (yysemantic_stack_[(2) - (1)].func_args)->push_back((yysemantic_stack_[(2) - (2)].func_arg)); ;}
    break;

  case 28:
#line 227 "../parser.yy"
    {
	(yyval.func_arg) = new FunctionArgument();
	(yyval.func_arg)->name = (yysemantic_stack_[(5) - (1)].ident);
	(yyval.func_arg)->argument = (yysemantic_stack_[(5) - (4)].var_def);
 ;}
    break;

  case 29:
#line 234 "../parser.yy"
    { (yyval.var_def) = new VariableDefinition(); (yyval.var_def)->type = (yysemantic_stack_[(1) - (1)].expr); ;}
    break;

  case 30:
#line 235 "../parser.yy"
    { (yyval.var_def) = new VariableDefinition(); (yyval.var_def)->type = (yysemantic_stack_[(2) - (1)].expr); (yyval.var_def)->name = (yysemantic_stack_[(2) - (2)].ident); ;}
    break;

  case 31:
#line 241 "../parser.yy"
    { (yyval.func_def) = (yysemantic_stack_[(4) - (1)].func_def); (yyval.func_def)->statements = (yysemantic_stack_[(4) - (3)].block); ;}
    break;

  case 32:
#line 244 "../parser.yy"
    { (yyval.block) = new Block(); ;}
    break;

  case 33:
#line 245 "../parser.yy"
    { (yyval.block) = new Block(); (yyval.block)->statements.push_back((yysemantic_stack_[(1) - (1)].stmt)); ;}
    break;

  case 34:
#line 246 "../parser.yy"
    { (yysemantic_stack_[(2) - (1)].block)->statements.push_back((yysemantic_stack_[(2) - (2)].stmt)); ;}
    break;

  case 37:
#line 260 "../parser.yy"
    { (yyval.var_def) = new VariableDefinition(); (yyval.var_def)->type = (yysemantic_stack_[(2) - (1)].expr); (yyval.var_def)->name = (yysemantic_stack_[(2) - (2)].ident); ;}
    break;

  case 38:
#line 263 "../parser.yy"
    { (yyval.var_def) = (yysemantic_stack_[(1) - (1)].var_def); ;}
    break;

  case 39:
#line 264 "../parser.yy"
    { (yyval.var_def) = (yysemantic_stack_[(3) - (1)].var_def); (yyval.var_def)->initial = (yysemantic_stack_[(3) - (3)].expr); ;}
    break;

  case 41:
#line 283 "../parser.yy"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].ident); ;}
    break;

  case 42:
#line 284 "../parser.yy"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); ;}
    break;

  case 43:
#line 285 "../parser.yy"
    { (yyval.expr) = (yysemantic_stack_[(1) - (1)].expr); ;}
    break;

  case 44:
#line 288 "../parser.yy"
    { (yyval.expr) = (yysemantic_stack_[(3) - (2)].expr); ;}
    break;

  case 45:
#line 289 "../parser.yy"
    { (yyval.expr) = new Tuple(); ((Tuple *)(yyval.expr))->expressions = (yysemantic_stack_[(3) - (2)].exprs); ;}
    break;

  case 48:
#line 296 "../parser.yy"
    {
	(yyval.expr) = new MemberAccess();
	((MemberAccess *)(yyval.expr))->subject = (yysemantic_stack_[(3) - (1)].expr);
	((MemberAccess *)(yyval.expr))->member = (yysemantic_stack_[(3) - (3)].ident);
 ;}
    break;

  case 50:
#line 304 "../parser.yy"
    { (yyval.exprs) = new Expressions(); (yyval.exprs)->push_back((yysemantic_stack_[(3) - (1)].expr)); (yyval.exprs)->push_back((yysemantic_stack_[(3) - (3)].expr)); ;}
    break;

  case 51:
#line 305 "../parser.yy"
    { (yyval.exprs) = (yysemantic_stack_[(3) - (1)].exprs); (yysemantic_stack_[(3) - (1)].exprs)->push_back((yysemantic_stack_[(3) - (3)].expr)); ;}
    break;

  case 63:
#line 322 "../parser.yy"
    { (yyval.expr) = new Numeric(*(yysemantic_stack_[(1) - (1)].string)); delete (yysemantic_stack_[(1) - (1)].string); ;}
    break;

  case 64:
#line 323 "../parser.yy"
    { (yyval.expr) = new Numeric(*(yysemantic_stack_[(1) - (1)].string)); delete (yysemantic_stack_[(1) - (1)].string); ;}
    break;

  case 65:
#line 328 "../parser.yy"
    { (yyval.expr) = new String(*(yysemantic_stack_[(1) - (1)].string)); delete (yysemantic_stack_[(1) - (1)].string); ;}
    break;

  case 66:
#line 333 "../parser.yy"
    {
	FunctionCallArgument * arg = new FunctionCallArgument();
	arg->name = (yysemantic_stack_[(3) - (3)].ident);
	
	FunctionCallArguments * args = new FunctionCallArguments();
	args->push_back(arg);
	
	(yyval.func_call) = new FunctionCall();
	(yyval.func_call)->receiver = (yysemantic_stack_[(3) - (1)].expr);
	(yyval.func_call)->arguments = args;
 ;}
    break;

  case 67:
#line 344 "../parser.yy"
    {
	(yyval.func_call) = new FunctionCall();
	(yyval.func_call)->receiver = (yysemantic_stack_[(5) - (1)].expr);
	(yyval.func_call)->arguments = (yysemantic_stack_[(5) - (4)].func_call_args);
 ;}
    break;

  case 68:
#line 351 "../parser.yy"
    { (yyval.func_call_args) = new FunctionCallArguments(); (yyval.func_call_args)->push_back((yysemantic_stack_[(1) - (1)].func_call_arg)); ;}
    break;

  case 69:
#line 352 "../parser.yy"
    { (yyval.func_call_args) = (yysemantic_stack_[(2) - (1)].func_call_args); (yyval.func_call_args)->push_back((yysemantic_stack_[(2) - (2)].func_call_arg)); ;}
    break;

  case 70:
#line 355 "../parser.yy"
    {
	(yyval.func_call_arg) = new FunctionCallArgument();
	(yyval.func_call_arg)->name = (yysemantic_stack_[(3) - (1)].ident);
	(yyval.func_call_arg)->argument = (yysemantic_stack_[(3) - (3)].expr);
 ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 714 "parser.cpp"
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
       -23,     5,    14,   -23,   -41,    -3,   -41,   -41,     8,   -41,
     -41,    11,   -41,     5,     5,   -41,   -41,   -41,    70,   -41,
      70,    70,   -41,    36,   -41,    -2,   -41,     7,     3,     5,
     121,   -41,   -41,   -41,   -41,    17,     9,    91,     2,   -41,
       5,   -41,   -41,   -41,    70,   -41,    70,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,     5,    44,   -41,   -41,   -41,
     -41,   -41,    70,    70,   -41,     5,     5,   -41,    70,   -41,
      70,    10,   -41,     5,   -41,    62,   -41,    26,   106,   121,
     -41,     5,   -41,   121,   121,   -41,    39,   121,   121,    25,
      10,   -41,   -41,   -41,   -41,   -41,    28,     1,   -41,   -41,
      70,    70,   -41,   -41,    48,     5,   121,   -41,   -41
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     2,     3,     0,     6,     7,    10,     1,
       4,     0,     5,     0,     0,    64,    63,    65,     0,    14,
       0,     0,    41,     0,    16,     0,    19,    38,     0,     0,
      40,    42,    43,    49,     8,     0,    12,     0,     0,    21,
       0,    22,    15,    17,    32,    18,     0,    20,    37,    52,
      53,    54,    57,    56,    55,     0,     0,    62,    58,    59,
      60,    61,     0,     0,    11,     0,     0,    44,     0,    45,
       0,    24,    23,    25,    26,     0,    33,     0,    40,    39,
      48,     0,    66,    46,    47,     9,     0,    50,    51,     0,
       0,    27,    31,    34,    36,    35,     0,     0,    68,    13,
       0,     0,    67,    69,     0,    29,    70,    28,    30
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -41,   -41,   -41,    56,    -1,    13,   -41,   -41,   -41,    40,
     -41,    50,   -41,   -41,    12,   -41,   -41,   -41,     6,   -41,
     -40,   -18,   -17,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -14
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     2,     3,     4,    22,    35,     5,     6,    23,    24,
      25,    39,    72,    73,    74,   104,    26,    75,    76,    27,
      28,    29,    30,    38,    62,    63,    31,    32,    33,    97,
      98
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
         8,    37,    40,    40,    77,     7,     1,    11,    44,     7,
     102,    69,    34,    36,     9,     7,    15,    16,    17,    18,
      12,    45,    19,    70,    13,    66,    47,    78,    48,    79,
      14,    46,    89,   100,    64,    77,    20,    21,    65,    71,
       7,    15,    16,    17,    18,    83,    84,    42,     7,    94,
     101,    87,    81,    88,    80,    82,    99,   107,    78,    10,
      65,    20,    21,    43,    85,    34,     7,    15,    16,    17,
      18,    41,    90,    92,     7,    15,    16,    17,    18,    86,
      96,    93,   105,   103,   106,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,     0,     0,     0,
      67,     0,     0,     0,   108,    49,    50,    51,    52,    53,
      54,    55,    68,    56,     0,    57,    58,    59,    60,    61,
      49,    50,    51,    52,    53,    54,    55,     0,    56,    95,
      57,    58,    59,    60,    61,    49,    50,    51,    52,    53,
      54,    55,     0,    56,     0,    57,    58,    59,    60,    61
  };

  /* YYCHECK.  */
  const signed char
  Parser::yycheck_[] =
  {
         1,    18,    20,    21,    44,     4,    29,    10,    10,     4,
       9,     9,    13,    14,     0,     4,     5,     6,     7,     8,
      23,    23,    11,    21,    16,    16,    23,    44,    29,    46,
      22,    24,    22,     8,    17,    75,    25,    26,    21,    40,
       4,     5,     6,     7,     8,    62,    63,    11,     4,    23,
      22,    68,     8,    70,    55,    56,    17,     9,    75,     3,
      21,    25,    26,    23,    65,    66,     4,     5,     6,     7,
       8,    21,    73,    11,     4,     5,     6,     7,     8,    66,
      81,    75,   100,    97,   101,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,    -1,
       9,    -1,    -1,    -1,   105,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    27,    28,
      14,    15,    16,    17,    18,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    28,    14,    15,    16,    17,    18,
      19,    20,    -1,    22,    -1,    24,    25,    26,    27,    28
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    29,    32,    33,    34,    37,    38,     4,    35,     0,
      34,    10,    23,    16,    22,     5,     6,     7,     8,    11,
      25,    26,    35,    39,    40,    41,    47,    50,    51,    52,
      53,    57,    58,    59,    35,    36,    35,    53,    54,    42,
      52,    42,    11,    40,    10,    23,    24,    23,    35,    14,
      15,    16,    17,    18,    19,    20,    22,    24,    25,    26,
      27,    28,    55,    56,    17,    21,    16,     9,    21,     9,
      21,    35,    43,    44,    45,    48,    49,    51,    53,    53,
      35,     8,    35,    53,    53,    35,    36,    53,    53,    22,
      35,    45,    11,    49,    23,    23,    35,    60,    61,    17,
       8,    22,     9,    61,    46,    52,    53,     9,    35
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
     285
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    31,    32,    33,    33,    34,    34,    35,    36,    36,
      37,    37,    37,    37,    38,    38,    39,    39,    40,    40,
      40,    41,    41,    42,    43,    43,    44,    44,    45,    46,
      46,    47,    48,    48,    48,    49,    49,    50,    51,    51,
      52,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    56,    57,    57,    58,    59,    59,    60,    60,
      61
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     1,     2,     2,     1,     1,     1,     3,
       2,     5,     4,     7,     3,     4,     1,     2,     2,     1,
       2,     2,     2,     2,     1,     1,     1,     2,     5,     1,
       2,     4,     0,     1,     2,     2,     2,     2,     1,     3,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     1,     2,
       3
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "IDENTIFIER", "FLOAT", "INTEGER", "STRING", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "LBRACK", "RBRACK", "CEQ", "CNE", "CLT", "CGT", "CLE", "CGE",
  "DOT", "COMMA", "COLON", "SEMICOLON", "EQUAL", "PLUS", "MINUS",
  "ASTERISK", "SLASH", "CLASS", "PROPERTY", "$accept", "root",
  "root_stmts", "root_stmt", "ident", "idents", "class_decl", "class_def",
  "class_stmts", "class_stmt", "func_decl", "func_rest", "func_sel",
  "func_args", "func_arg", "func_arg_var", "func_def", "func_stmts",
  "func_stmt", "var_decl", "var_def", "type", "expr", "exprs",
  "bin_operator", "assignment", "numeric", "string", "func_call",
  "func_call_args", "func_call_arg", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        32,     0,    -1,    33,    -1,    34,    -1,    33,    34,    -1,
      37,    23,    -1,    38,    -1,     4,    -1,    35,    -1,    36,
      21,    35,    -1,    29,    35,    -1,    29,    35,    16,    36,
      17,    -1,    29,    35,    22,    35,    -1,    29,    35,    22,
      35,    16,    36,    17,    -1,    37,    10,    11,    -1,    37,
      10,    39,    11,    -1,    40,    -1,    39,    40,    -1,    41,
      23,    -1,    47,    -1,    51,    23,    -1,    25,    42,    -1,
      26,    42,    -1,    52,    43,    -1,    35,    -1,    44,    -1,
      45,    -1,    44,    45,    -1,    35,    22,     8,    46,     9,
      -1,    52,    -1,    52,    35,    -1,    41,    10,    48,    11,
      -1,    -1,    49,    -1,    48,    49,    -1,    53,    23,    -1,
      51,    23,    -1,    52,    35,    -1,    50,    -1,    50,    24,
      53,    -1,    53,    -1,    35,    -1,    57,    -1,    58,    -1,
       8,    53,     9,    -1,     8,    54,     9,    -1,    53,    55,
      53,    -1,    53,    56,    53,    -1,    53,    20,    35,    -1,
      59,    -1,    53,    21,    53,    -1,    54,    21,    53,    -1,
      14,    -1,    15,    -1,    16,    -1,    19,    -1,    18,    -1,
      17,    -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,
      24,    -1,     6,    -1,     5,    -1,     7,    -1,    53,    22,
      35,    -1,    53,    22,     8,    60,     9,    -1,    61,    -1,
      60,    61,    -1,    35,    22,    53,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,    10,    13,    15,    17,    19,
      23,    26,    32,    37,    45,    49,    54,    56,    59,    62,
      64,    67,    70,    73,    76,    78,    80,    82,    85,    91,
      93,    96,   101,   102,   104,   107,   110,   113,   116,   118,
     122,   124,   126,   128,   130,   134,   138,   142,   146,   150,
     152,   156,   160,   162,   164,   166,   168,   170,   172,   174,
     176,   178,   180,   182,   184,   186,   188,   192,   198,   200,
     203
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   123,   123,   126,   127,   132,   133,   139,   142,   143,
     154,   158,   163,   168,   179,   180,   185,   186,   189,   190,
     191,   200,   201,   204,   214,   220,   223,   224,   227,   234,
     235,   241,   244,   245,   246,   249,   250,   260,   263,   264,
     274,   283,   284,   285,   288,   289,   292,   293,   296,   301,
     304,   305,   311,   311,   311,   311,   311,   311,   312,   312,
     312,   312,   317,   322,   323,   328,   333,   344,   351,   352,
     355
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
      25,    26,    27,    28,    29,    30
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 149;
  const int Parser::yynnts_ = 31;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 9;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 31;

  const unsigned int Parser::yyuser_token_number_max_ = 285;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace Maxwell

#line 362 "../parser.yy"




/*** Additional Code ***/
using namespace Maxwell;

/* Capture errors that occur in the parser and pass them onto the driver. */
void Parser::error(const Parser::location_type & l, const std::string & m)
{
	driver.error(l, m);
}

