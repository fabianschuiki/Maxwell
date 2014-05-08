/* Copyright © 2013 Fabian Schuiki */
#include "Driver.hpp"
#include <ast/nodes/ast.hpp>
#include <vector>

using namespace ast;
typedef std::vector<NodePtr> Nodes;

#include "Scanner.hpp"
#include <fstream>
#include <sstream>

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
	std::stringstream s;
	s << l << ": " << m;
	throw std::runtime_error(s.str());
}

void Driver::error(const std::string& m)
{
	throw std::runtime_error(m);
}

void Driver::add(const NodePtr& node)
{
	nodes.push_back(node);
}