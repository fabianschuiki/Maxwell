/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/test/parser/detail.hpp"

driver::Driver drv;

void parse(const std::string& input)
{
	std::stringstream s(input);
	drv.nodes.clear();
	if (!drv.parseStream(s, "stream", maxwell::SourceLocation()))
		throw std::runtime_error("failed to parse");
}

std::string structure(const NodePtr& node, int depth)
{
	std::string desc = node->describe(depth);
	std::string output;
	bool wasWhitespace = false;
	bool wasEscape = false;
	for (std::string::const_iterator i = desc.begin(); i != desc.end(); i++) {
		if (*i == ' ' || *i == '\t' || *i == '\n' || *i == '\r') {
			wasWhitespace = true;
		} else if (*i == '\033') {
			wasEscape = true;
		} else if (wasEscape) {
			wasEscape = (*i != 'm');
		} else {
			if (wasWhitespace)
				output += ' ';
			output += *i;
			wasWhitespace = false;
		}
	}
	return output;
}
