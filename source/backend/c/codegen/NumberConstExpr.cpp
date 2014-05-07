/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "detail.hpp"

DEF_EXPR(NumberConstExpr)
{
	out.code = node->getValue();
	out.isRef = false;
	out.precedence = kPrimaryPrec;
}
