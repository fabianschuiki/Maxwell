#include <iostream>
#include <fstream>

#include "driver.h"

using namespace Maxwell;


int main(int argc, char * argv[])
{
	/*std::ifstream fin("../examples/class.mw");
	FlexLexer * lexer = new yyFlexLexer(&fin);
	while (int result = lexer->yylex())
		std::cout << "result = " << result << "\n";*/
	
	//Create a new driver to read stuff.
	Driver driver;
	driver.parse("debug.mw");
	
	return 0;
}
