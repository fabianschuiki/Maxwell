#include <iostream>
#include <fstream>


int main(int argc, char * argv[])
{
    //For debugging, fetch the input file.
    if (argc < 2) {
        std::cerr << "no input file\n";
        return 1;
    }
    char * input = argv[1];
    std::ifstream fin(input);
    
    
    
	return 0;
}
