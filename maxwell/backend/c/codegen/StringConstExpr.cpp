/* Copyright (c) 2013-2015 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_EXPR(StringConstExpr)
{
	out.code = node->getValue();
	out.isRef = false;
	out.precedence = kPrimaryPrec;
}
