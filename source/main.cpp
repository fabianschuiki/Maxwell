#include <iostream>
#include <fstream>
#include "lexer.h"


int main(int argc, char * argv[])
{
    //For debugging, fetch the input file.
    if (argc < 2) {
        std::cerr << "no input file\n";
        return 1;
    }
    char * input = argv[1];
    std::ifstream fin(input);
	
	//Parse the input.
	Lexer::Group * root = Lexer::parse(&fin);
	std::cout << "read:\n" << root->describe() << "\n";
	
	return 0;
}
