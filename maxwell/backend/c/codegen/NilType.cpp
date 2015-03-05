/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_TYPE(NilType)
{
	out.code = "void";
	return;
}
