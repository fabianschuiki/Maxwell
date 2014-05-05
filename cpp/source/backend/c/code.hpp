/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <string>

namespace backendc {

std::string indent(const std::string& in);

struct Fragment
{
	std::string name;
	std::string code;
	std::string ref;
	std::string group;
};

/** A code fragment representing an expression. */
struct ExprCode
{
	std::string code;
	bool isRef;
	int precedence;
	ExprCode();
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
