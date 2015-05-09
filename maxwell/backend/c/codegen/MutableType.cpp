/* Copyright (c) 2015 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_TYPE(MutableType) {
	TypeCode tc;
	generateType(node->getType(), tc);
	out += tc;
	out.code = tc.code + "*";
}
