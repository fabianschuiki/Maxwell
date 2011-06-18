#include <iostream>
#include <fstream>
#include <FlexLexer.h>


int main(int argc, char * argv[])
{
	std::ifstream fin("../examples/class.mw");
	FlexLexer * lexer = new yyFlexLexer(&fin/*, &std::cout*/);
	while (int result = lexer->yylex())
		std::cout << "result = " << result << "\n";
	return 0;
}
