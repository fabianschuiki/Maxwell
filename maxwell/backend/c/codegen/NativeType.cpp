/* Copyright (c) 2015 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_TYPE(NativeType)
{
	out.code.clear();
	bool first = true;
	for (const auto& s : node->getSegments()) {
		if (!first)
			out.code += ' ';
		else
			first = false;
		out.code += s;
	}
}
