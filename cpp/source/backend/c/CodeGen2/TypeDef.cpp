/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "detail.hpp"

DEF_ROOT(TypeDef)
{
	// Generate the code for the type that is being wrapped by this definition.
	TypeCode tc;
	generateType(node->getType()->needTypeExpr()->getEvaluatedType(), tc);

	// Pick a name.
	std::string name = makeTypeName(node);

	// Synthesize the definition for this type.
	Fragment def;
	def.name  = node->getId().str() + "_def";
	def.code  = "typedef " + tc.code + " " + name + ";";
	def.ref   = name;
	def.group = "types.h";

	// Add the fragment and dependencies.
	addFragment(def);
	for (std::set<std::string>::const_iterator i = tc.deps.begin(); i != tc.deps.end(); i++) {
		addDependency(def.name, *i, false);
	}
}
