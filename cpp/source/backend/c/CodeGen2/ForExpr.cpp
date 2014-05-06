/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "detail.hpp"

DEF_EXPR(ForExpr)
{
	std::cout << "resultVar for ForExpr is '" << ctx.resultVar << "'\n";
}
