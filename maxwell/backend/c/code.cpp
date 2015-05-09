/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/ast/NodeId.hpp"
#include "maxwell/backend/c/code.hpp"
#include <sstream>
#include <stdexcept>
using namespace backendc;


Context::Context()
{
	tmpIndex = 0;
	// omitResultVar = false;
}

Context::Context(const Context& parent)
{
	usedSymbols = parent.usedSymbols;
	vars = parent.vars;
	tmpIndex = parent.tmpIndex;
	// omitResultVar = false;
}


/** Returns either the name passed to the function, or a slightly altered name
 * if it is already in use. Useful for making sure that a name is unique within
 * a context. Also adds the symbol to the list of used symbols. */
std::string Context::makeSymbol(const std::string& name)
{
	std::string result = name;
	int i = 2;

	while (usedSymbols.count(result)) {
		std::stringstream s;
		s << name << i++;
		result = s.str();
	}

	usedSymbols.insert(result);
	return result;
}

/** Returns the name for a temporary symbol and adds it to the symbol table.
 * Useful for creating temporary variables and the like. */
std::string Context::makeTempSymbol()
{
	std::string name;
	do {
		std::stringstream s;
		s << "tmp" << tmpIndex++;
		name = s.str();
	} while (usedSymbols.count(name));
	usedSymbols.insert(name);
	return name;
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


/// Adds the dependencies and includes of \a b to \a a.
ExprCode& backendc::operator+= (ExprCode& a, const ExprCode& b) {
	a.deps.insert(b.deps.begin(), b.deps.end());
	a.incs.insert(b.incs.begin(), b.incs.end());
	return a;
}

/// Adds the dependencies and includes of \a b to \a a.
ExprCode& backendc::operator+= (ExprCode& a, const TypeCode& b) {
	a.deps.insert(b.deps.begin(), b.deps.end());
	a.incs.insert(b.incs.begin(), b.incs.end());
	return a;
}

/// Adds the dependencies and includes of \a b to \a a.
TypeCode& backendc::operator+= (TypeCode& a, const TypeCode& b) {
	a.deps.insert(b.deps.begin(), b.deps.end());
	a.incs.insert(b.incs.begin(), b.incs.end());
	return a;
}
