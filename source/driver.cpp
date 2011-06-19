#include <fstream>
#include <sstream>

#include "driver.h"
#include "scanner/scanner.h"

using namespace Maxwell;


bool Driver::parse(std::istream & input, const std::string & name)
{
	//Store the stream name for later reference.
	streamName = name;
	
	//Initialize a new scanner.
	Scanner scanner(&input);
	this->scanner = &scanner;
	
	//Initialize a new parser.
	Parser parser(*this);
	
	//Parse.
	return (parser.parse() == 0);
}

bool Driver::parse(const std::string & filename)
{
	//Try to open the given file for parsing.
	std::ifstream input(filename.c_str());
	if (!input.good())
		return false;
	
	//Return the result of the parsing procedure.
	return parse(input, filename);
}

void Driver::error(const class location & l, const std::string & message)
{
	std::cerr << l << ": " << message << std::endl;
}

void Driver::error(const std::string & message)
{
	std::cerr << message << std::endl;
}
