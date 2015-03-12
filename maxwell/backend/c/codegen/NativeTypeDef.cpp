/* Copyright (c) 2015 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_ROOT(NativeTypeDef)
{
	// Generate the code for the type that is being wrapped by this definition.
	TypeCode tc;
	generateType(node->getType()->needTypeExpr()->getEvaluatedType(), tc);

	// Pick a name.
	std::string name = makeNativeTypeName(node);

	// Synthesize the definition for this type.
	Fragment def;
	def.name  = node->getId().str() + "_def";
	def.code  = "typedef " + tc.code + " " + name + ";";
	def.ref   = name;
	def.group = "types.h";

	// Add the fragment and dependencies.
	addFragment(def);
	for (const auto& i : tc.deps) {
		addDependency(def.name, i, false);
	}
	for (const auto& i : tc.incs) {
		addInclude(def.name, i);
	}

	// Keep the definition and declaration fragment names around for later
	// stages.
	names[node->getId()] = def.name;
}
