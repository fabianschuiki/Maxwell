%option c++

%{
	int yyFlexLexer::yywrap() { }
%}

/* Define some standard regex components. */
space		[ \t\n\r]


%%

{space}				; //ignore spaces

\/\/.*				; //ignore comments
\/\*(.|\n)*?\*\/	;

%%
