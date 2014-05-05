/* Copyright (c) 2014 Fabian Schuiki */
#include "code.hpp"
#include <sstream>
#include <stdexcept>
using namespace backendc;


std::string Context::makeSymbol(const std::string& name)
{
	if (!usedSymbols.count(name))
		return name;

	for (int i = 2; i < 100000; i++) {
		std::stringstream s;
		s << name << i;
		if (!usedSymbols.count(s.str()))
			return s.str();
	}

	throw std::runtime_error("Unable to find a symbol name for '" + name + "'");
}


ExprCode::ExprCode()
{
	isRef = false;
	precedence = 0;
}

/** Returns a copy of the input string with each non-empty line indented. */
std::string backendc::indent(const std::string& in)
{
	std::string out;
	bool ind = true;
	for (std::string::const_iterator it = in.begin(); it != in.end(); it++) {
		if (*it != '\n' && ind) {
			out += "    ";
			ind = false;
		}
		out += *it;
		if (*it == '\n')
			ind = true;
	}
	return out;
}

/** @brief Wraps the given string in parentheses if needed.
 *
 * If prec is larger or equal to the outer_prec, the given string is returned
 * with surrounding paranthesis. Otherwise the unmodified string is returned.
 * This allows for automated precedence wrapping. */
std::string backendc::precedenceWrap(const std::string& s, int prec, int outer_prec)
{
	if (prec >= outer_prec)
		return "(" + s + ")";
	else
		return s;
}

/** Wraps the given expression code in parentheses if needed. Refer to the
 * std::string version of precedenceWrap for more details. */
std::string backendc::precedenceWrap(const ExprCode& ec, int outer_prec)
{
	return precedenceWrap(ec.code, ec.precedence, outer_prec);
}
