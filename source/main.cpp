#include <iostream>
#include <fstream>

#include "tokenizer/tokenizer.h"
#include "analyzer/analyzer.h"


int main(int argc, char * argv[])
{
    //For debugging, fetch the input file.
    if (argc < 2) {
        std::cerr << "no input file\n";
        return 1;
    }
    char * input = argv[1];
    std::ifstream fin(input);
    
    //Tokenize the input.
    Tokenizer t;
    t.process(fin);
    
    //Analyze the tokens.
    Analyzer a;
    a.process(t.getFirstToken());
    
	return 0;
}
