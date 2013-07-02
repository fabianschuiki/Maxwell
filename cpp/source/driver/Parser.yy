/* Copyright © 2013 Fabian Schuiki */

%{
#include <iostream>
#include <string>
%}

/* Require Bison 2.3 */
%require "2.3"

/* Produce debug output. Disable this for the release version. */
%debug

/* Use the modern C++ skeleton file. */
%skeleton "lalr1.cc"
%name-prefix="example" /* namespace the parser will be enclosed in */
%define "parser_class_name" "Parser" /* class name of the parser */

/* Keep track of the current position within the input. */
%locations
%initial-action {
	// initialize the location object
	@$.begin.filename = @$.end.filename = &driver.streamname;
};

/* Pass the driver by reference into the parser and the lexer. */
%parse-param { class Driver& driver }

/* Produce some verbose error messages. */
%error-verbose


/*** BEGIN GRAMMAR TOKENS ***/

%union {
    std::string *string;
    int token;
}

%token <string> IDENTIFIER REAL INTEGER
%token END 0 "end of filet"

%left "+" "-"
%left "*" "/"

%destructor { delete $$; } IDENTIFIER REAL INTEGER

%start root

/*** END GRAMMAR TOKENS ***/

/* Add the glue code require to hook up the Bison parser to the Flex lexer class. */
%{
#include "Driver.hpp"
#include "Scanner.hpp"

/* This connects the Bison parser to the Flex scanner. */
#undef yylex
#define yylex driver.lexer->lex
%}


%% /*** Grammar Rules ***/

root : somethings
     ;

somethings : somethings something
           | something
           ;

something : IDENTIFIER { std::cout << "found identifier " << *$1 << "\n"; delete $1; }
          | REAL       { std::cout << "found real " << *$1 << "\n"; delete $1; }
          | INTEGER    { std::cout << "found integer " << *$1 << "\n"; delete $1; }
          ;


%% /*** Additional Code ***/

void example::Parser::error(const Parser::location_type& l, const std::string& m)
{
	driver.error(l,m);
}