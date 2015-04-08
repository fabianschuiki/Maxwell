/* Copyright (c) 2015 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_TYPE(QualifiedType) {

	if (lookupType(out))
		return;


	// Generate the code for the struct body.
	std::string body = "";
	std::set<std::string> bodyDeps;

	for (const auto& m : node->getMembers()) {
		const auto& member = QualifiedTypeMember::needFrom(m);

		// Generate the type for this field.
		TypeCode tc;
		generateType(member->getType(), tc);
		bodyDeps.insert(tc.deps.begin(), tc.deps.end());

		// Generate a C-friendly name for this field.
		string name = makeFriendly(member->getName());

		body += tc.code + " " + name + ";\n";
	}


	// Pick a name.
	std::string name;
	do {
		std::stringstream s;
		s << "struct" << rand();
		name = makeFriendly(s.str());
	} while (!isRefUnused(name));


	// Synthesize the definition.
	Fragment def;
	def.name  = out.hash;
	def.code  = "struct " + name + " {\n" + indent(body) + "};";
	def.ref   = "struct " + name;
	def.group = "types.h";

	// Add the fragment to the database and add all dependencies.
	addFragment(def);
	for (auto& i : bodyDeps) {
		addDependency(def.name, i, false);
	}
}
