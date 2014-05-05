/* Copyright (c) 2014 Fabian Schuiki */
#include "detail.hpp"

DEF_TYPE(TupleType)
{
	// Simplify tuples with only one field.
	const NodeVector& args = node->getArgs();
	if (args.size() == 1) {
		const TupleTypeArg::Ptr& arg = TupleTypeArg::needFrom(args[0]);
		return generateType(arg->getType(), out);
	}

	// If the has already been generated, there's no need to do anything.
	if (lookupType(out))
		return;

	throw std::runtime_error("TupleType not implemented");
	Fragment def;
	def.name  = out.hash;
	def.code  = "struct sometuple {};";
	def.ref   = "struct sometuple";
	def.group = "tuples.h";
	addFragment(def);
}
