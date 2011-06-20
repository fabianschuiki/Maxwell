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
#line 100 "../parser.yy"

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
#line 114 "../parser.yy"
    { driver.programBlock = (yysemantic_stack_[(1) - (1)].block); ;}
    break;

  case 3:
#line 117 "../parser.yy"
    { (yyval.block) = new Block(); (yyval.block)->statements.push_back((yysemantic_stack_[(1) - (1)].stmt)); ;}
    break;

  case 4:
#line 118 "../parser.yy"
    { (yysemantic_stack_[(2) - (1)].block)->statements.push_back((yysemantic_stack_[(2) - (2)].stmt)); ;}
    break;

  case 5:
#line 123 "../parser.yy"
    { (yyval.stmt) = (yysemantic_stack_[(2) - (1)].class_def); ;}
    break;

  case 6:
#line 124 "../parser.yy"
    { (yyval.stmt) = (yysemantic_stack_[(1) - (1)].class_def); ;}
    break;

  case 7:
#line 130 "../parser.yy"
    { (yyval.ident) = new Identifier(*(yysemantic_stack_[(1) - (1)].string)); delete (yysemantic_stack_[(1) - (1)].string); ;}
    break;

  case 8:
#line 133 "../parser.yy"
    { (yyval.idents) = new Identifiers(); (yyval.idents)->push_back((yysemantic_stack_[(1) - (1)].ident)); ;}
    break;

  case 9:
#line 134 "../parser.yy"
    { (yysemantic_stack_[(3) - (1)].idents)->push_back((yysemantic_stack_[(3) - (3)].ident)); ;}
    break;

  case 10:
#line 145 "../parser.yy"
    {
	(yyval.class_def) = new ClassDefinition();
	(yyval.class_def)->name = (yysemantic_stack_[(2) - (2)].ident);
 ;}
    break;

  case 11:
#line 149 "../parser.yy"
    {
	(yyval.class_def) = new ClassDefinition();
	(yyval.class_def)->name = (yysemantic_stack_[(5) - (2)].ident);
	(yyval.class_def)->interfaces = (yysemantic_stack_[(5) - (4)].idents);
 ;}
    break;

  case 12:
#line 154 "../parser.yy"
    {
	(yyval.class_def) = new ClassDefinition();
	(yyval.class_def)->name = (yysemantic_stack_[(4) - (2)].ident);
	(yyval.class_def)->super = (yysemantic_stack_[(4) - (4)].ident);
 ;}
    break;

  case 13:
#line 159 "../parser.yy"
    {
	(yyval.class_def) = new ClassDefinition();
	(yyval.class_def)->name = (yysemantic_stack_[(7) - (2)].ident);
	(yyval.class_def)->super = (yysemantic_stack_[(7) - (4)].ident);
	(yyval.class_def)->interfaces = (yysemantic_stack_[(7) - (6)].idents);
 ;}
    break;

  case 14:
#line 170 "../parser.yy"
    { (yyval.class_def) = (yysemantic_stack_[(3) - (1)].class_def); ;}
    break;

  case 15:
#line 171 "../parser.yy"
    { (yyval.class_def) = (yysemantic_stack_[(4) - (1)].class_def); (yyval.class_def)->statements = (yysemantic_stack_[(4) - (3)].block); ;}
    break;

  case 16:
#line 176 "../parser.yy"
    { (yyval.block) = new Block(); (yyval.block)->statements.push_back((yysemantic_stack_[(1) - (1)].stmt)); ;}
    break;

  case 17:
#line 177 "../parser.yy"
    { (yysemantic_stack_[(2) - (1)].block)->statements.push_back((yysemantic_stack_[(2) - (2)].stmt)); ;}
    break;

  case 18:
#line 180 "../parser.yy"
    { (yyval.stmt) = (yysemantic_stack_[(2) - (1)].func_def); ;}
    break;

  case 19:
#line 181 "../parser.yy"
    { (yyval.stmt) = (yysemantic_stack_[(1) - (1)].func_def); ;}
    break;

  case 21:
#line 190 "../parser.yy"
    {
	(yyval.func_def) = new FunctionDefinition();
	(yyval.func_def)->shared = ((yysemantic_stack_[(3) - (1)].token) == token::PLUS);
	(yyval.func_def)->returnType = (yysemantic_stack_[(3) - (2)].type);
	(yyval.func_def)->arguments = (yysemantic_stack_[(3) - (3)].func_args);
 ;}
    break;

  case 22:
#line 201 "../parser.yy"
    {
	FunctionArgument * arg = new FunctionArgument();
	arg->name = (yysemantic_stack_[(1) - (1)].ident);
	(yyval.func_args) = new FunctionArguments();
	(yyval.func_args)->push_back(arg);
 ;}
    break;

  case 23:
#line 207 "../parser.yy"
    { (yyval.func_args) = (yysemantic_stack_[(1) - (1)].func_args); ;}
    break;

  case 24:
#line 210 "../parser.yy"
    { (yyval.func_args) = new FunctionArguments(); (yyval.func_args)->push_back((yysemantic_stack_[(1) - (1)].func_arg)); ;}
    break;

  case 25:
#line 211 "../parser.yy"
    { (yysemantic_stack_[(2) - (1)].func_args)->push_back((yysemantic_stack_[(2) - (2)].func_arg)); ;}
    break;

  case 26:
#line 214 "../parser.yy"
    {
	(yyval.func_arg) = new FunctionArgument();
	(yyval.func_arg)->name = (yysemantic_stack_[(5) - (1)].ident);
	(yyval.func_arg)->argument = (yysemantic_stack_[(5) - (4)].type);
 ;}
    break;

  case 27:
#line 224 "../parser.yy"
    { (yyval.func_def) = (yysemantic_stack_[(3) - (1)].func_def); ;}
    break;

  case 28:
#line 225 "../parser.yy"
    { (yyval.func_def) = (yysemantic_stack_[(4) - (1)].func_def); (yyval.func_def)->statements = (yysemantic_stack_[(4) - (3)].block); ;}
    break;

  case 29:
#line 228 "../parser.yy"
    { (yyval.block) = new Block(); (yyval.block)->statements.push_back((yysemantic_stack_[(1) - (1)].stmt)); ;}
    break;

  case 30:
#line 229 "../parser.yy"
    { (yysemantic_stack_[(2) - (1)].block)->statements.push_back((yysemantic_stack_[(2) - (2)].stmt)); ;}
    break;

  case 32:
#line 241 "../parser.yy"
    {
	(yyval.type) = new ConcreteType();
	((ConcreteType *)(yyval.type))->name = (yysemantic_stack_[(1) - (1)].ident);
 ;}
    break;

  case 33:
#line 245 "../parser.yy"
    {
	(yyval.type) = new TupleType();
	((TupleType *)(yyval.type))->types = (yysemantic_stack_[(3) - (2)].types);
 ;}
    break;

  case 34:
#line 251 "../parser.yy"
    { (yyval.types) = new Types(); (yyval.types)->push_back((yysemantic_stack_[(1) - (1)].type)); ;}
    break;

  case 35:
#line 252 "../parser.yy"
    { (yysemantic_stack_[(3) - (1)].types)->push_back((yysemantic_stack_[(3) - (3)].type)); ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 599 "parser.cpp"
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
  const signed char Parser::yypact_ninf_ = -25;
  const signed char
  Parser::yypact_[] =
  {
       -21,     2,    21,   -21,   -25,     0,   -25,   -25,    -8,   -25,
     -25,    -6,   -25,     2,     2,   -25,   -25,    24,    -4,   -25,
       1,   -25,   -25,     8,    -2,    24,   -25,     2,   -25,   -25,
      22,   -25,   -25,     2,     2,   -25,     4,    17,   -25,     2,
     -25,   -25,    27,   -25,   -25,    11,   -25,    24,    31,    17,
     -25,   -25,   -25,   -25,   -25,    24,    33,   -25
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     2,     3,     0,     6,     7,    10,     1,
       4,     0,     5,     0,     0,    14,    20,     0,     0,    16,
       0,    19,     8,     0,    12,     0,    32,     0,    15,    17,
       0,    18,    11,     0,     0,    34,     0,    22,    21,    23,
      24,    27,     0,    29,     9,     0,    33,     0,     0,     0,
      25,    28,    30,    13,    35,     0,     0,    26
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -25,   -25,   -25,    34,    -1,     6,   -25,   -25,   -25,    23,
     -25,   -25,   -25,     3,   -25,   -25,     5,   -24,   -25
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     2,     3,     4,    26,    23,     5,     6,    18,    19,
      20,    38,    39,    40,    21,    42,    43,    27,    36
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
         8,    35,    15,     1,    28,    13,     7,    11,    30,    14,
      46,    34,    22,    24,    16,    17,    16,    17,    12,    31,
      47,     9,    32,    54,    33,    53,    37,    33,     7,    25,
      41,    56,    44,    22,    48,    51,    55,    10,    49,    57,
      45,    29,    50,     0,     0,     0,     0,    52
  };

  /* YYCHECK.  */
  const signed char
  Parser::yycheck_[] =
  {
         1,    25,     8,    24,     8,    13,     4,     7,     7,    17,
       6,    13,    13,    14,    20,    21,    20,    21,    18,    18,
      16,     0,    14,    47,    16,    14,    27,    16,     4,     5,
       8,    55,    33,    34,    17,     8,     5,     3,    39,     6,
      34,    18,    39,    -1,    -1,    -1,    -1,    42
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    24,    27,    28,    29,    32,    33,     4,    30,     0,
      29,     7,    18,    13,    17,     8,    20,    21,    34,    35,
      36,    40,    30,    31,    30,     5,    30,    43,     8,    35,
       7,    18,    14,    16,    13,    43,    44,    30,    37,    38,
      39,     8,    41,    42,    30,    31,     6,    16,    17,    30,
      39,     8,    42,    14,    43,     5,    43,     6
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    26,    27,    28,    28,    29,    29,    30,    31,    31,
      32,    32,    32,    32,    33,    33,    34,    34,    35,    35,
      36,    36,    37,    37,    38,    38,    39,    40,    40,    41,
      41,    42,    43,    43,    44,    44
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     1,     2,     2,     1,     1,     1,     3,
       2,     5,     4,     7,     3,     4,     1,     2,     2,     1,
       1,     3,     1,     1,     1,     2,     5,     3,     4,     1,
       2,     0,     1,     3,     1,     3
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "IDENTIFIER", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK",
  "CEQ", "CNE", "CLT", "CGT", "DOT", "COMMA", "COLON", "SEMICOLON",
  "EQUAL", "PLUS", "MINUS", "ASTERISK", "SLASH", "CLASS", "PROPERTY",
  "$accept", "root", "root_stmts", "root_stmt", "ident", "idents",
  "class_decl", "class_def", "class_stmts", "class_stmt", "func_decl",
  "func_sel", "func_args", "func_arg", "func_def", "func_stmts",
  "func_stmt", "type", "types", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        27,     0,    -1,    28,    -1,    29,    -1,    28,    29,    -1,
      32,    18,    -1,    33,    -1,     4,    -1,    30,    -1,    31,
      16,    30,    -1,    24,    30,    -1,    24,    30,    13,    31,
      14,    -1,    24,    30,    17,    30,    -1,    24,    30,    17,
      30,    13,    31,    14,    -1,    32,     7,     8,    -1,    32,
       7,    34,     8,    -1,    35,    -1,    34,    35,    -1,    36,
      18,    -1,    40,    -1,    20,    -1,    21,    43,    37,    -1,
      30,    -1,    38,    -1,    39,    -1,    38,    39,    -1,    30,
      17,     5,    43,     6,    -1,    36,     7,     8,    -1,    36,
       7,    41,     8,    -1,    42,    -1,    41,    42,    -1,    -1,
      30,    -1,     5,    44,     6,    -1,    43,    -1,    44,    16,
      43,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,    10,    13,    15,    17,    19,
      23,    26,    32,    37,    45,    49,    54,    56,    59,    62,
      64,    66,    70,    72,    74,    76,    79,    85,    89,    94,
      96,    99,   100,   102,   106,   108
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  Parser::yyrline_[] =
  {
         0,   114,   114,   117,   118,   123,   124,   130,   133,   134,
     145,   149,   154,   159,   170,   171,   176,   177,   180,   181,
     190,   190,   201,   207,   210,   211,   214,   224,   225,   228,
     229,   231,   241,   245,   251,   252
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
      25
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 47;
  const int Parser::yynnts_ = 19;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 9;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 26;

  const unsigned int Parser::yyuser_token_number_max_ = 280;
  const Parser::token_number_type Parser::yyundef_token_ = 2;

} // namespace Maxwell

#line 255 "../parser.yy"




/*** Additional Code ***/
using namespace Maxwell;

/* Capture errors that occur in the parser and pass them onto the driver. */
void Parser::error(const Parser::location_type & l, const std::string & m)
{
	driver.error(l, m);
}

