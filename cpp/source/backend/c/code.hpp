/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>

namespace ast { struct NodeId; }

namespace backendc {

std::string indent(const std::string& in);

struct Fragment
{
	std::string name;
	std::string code;
	std::string ref;
	std::string group;
};

/** A code generator context, corresponding roughly to a C scope. This
 * structure holds declared variables, used symbols and statements for a scope
 * in the final C code. */
struct Context
{
	std::vector<std::string> stmts;
	std::set<std::string> usedSymbols;
	std::map<ast::NodeId,std::string> vars;
	std::string resultVar;
	bool omitResultVar;

	Context();
	Context(const Context& parent);

	std::string makeSymbol(const std::string& name);
	std::string makeTempSymbol();

private:
	int tmpIndex;
};

/** A code fragment representing an expression. */
struct ExprCode
{
	std::string code;
	std::set<std::string> deps;
	bool isRef;
	int precedence;
	ExprCode();
};

/** A code fragment representing a type. */
struct TypeCode
{
	std::string code;
	std::set<std::string> deps;
	std::string hash;
};


/** Enumeration that simplifies precedence handling. */
enum {
	kPrimaryPrec = 0,
	kPrefixPrec,
	kMultiplicativePrec,
	kAdditivePrec,
	kRelationalPrec,
	kEqualityPrec,
	kAndPrec,
	kOrPrec,
	kAssignmentPrec,
	kLowestPrec
};

std::string precedenceWrap(const std::string& s, int prec, int outer_prec);
std::string precedenceWrap(const ExprCode& ec, int outer_prec);

} // namespace backendc
