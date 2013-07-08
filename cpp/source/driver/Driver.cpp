/* Copyright © 2013 Fabian Schuiki */
#include "Driver.hpp"
#include "Scanner.hpp"
#include <fstream>

using driver::Driver;

Driver::Driver()
{
}

bool Driver::parseStream(std::istream& in, const std::string& name)
{
	streamname = name; // for error messages;
	Scanner scanner(&in);
	this->lexer = &scanner;
	Parser parser(*this);
	return (parser.parse() == 0);
}

bool Driver::parseFile(const std::string& filename)
{
	std::ifstream in(filename.c_str());
	if (!in.good()) return false;
	return parseStream(in, filename);
}

void Driver::error(const class location& l, const std::string& m)
{
	std::cerr << l << ": " << m << std::endl;
}

void Driver::error(const std::string& m)
{
	std::cerr << m << std::endl;
}

void Driver::add(const NodePtr& node)
{
	nodes.push_back(node);
}