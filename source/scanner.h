#pragma once

/* Define the signature of yylex in the YY_DECL macro so it gets picked up by flex. */
#ifndef YY_DECL
#define YY_DECL						\
Maxwell::Parser::token_type Maxwell::Scanner::lex(	\
	Maxwell::Parser::semantic_type * yylval,	\
	Maxwell::Parser::location_type * yylloc	\
)
#endif

/* Substitute the default lexer name. */
#ifndef __FLEX_LEXER_H
#define yyFlexLexer MaxwellFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

/* Include the parser whose constants we require. */
#include "parser.h"


namespace Maxwell {
	class Scanner : public MaxwellFlexLexer
	{
	public:
		Scanner(
			std::istream* yyin = 0,
			std::ostream* yyout = 0
		);
		virtual ~Scanner();
		
		virtual Parser::token_type lex(
			Parser::semantic_type * yylval,
			Parser::location_type * yylloc
		);
	};
}
