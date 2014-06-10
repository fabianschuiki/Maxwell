/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

static bool hashSort(const TypeCode& a, const TypeCode& b) {
	return a.hash < b.hash;
}

DEF_TYPE(UnionType)
{
	if (lookupType(out))
		return;

	// Generate the code for each individual type.
	const NodeVector& types = node->getTypes();
	std::vector<TypeCode> typeCodes;
	typeCodes.resize(types.size());

	int n = 0;
	for (NodeVector::const_iterator i = types.begin(); i != types.end(); i++, n++) {
		TypeCode& tc = typeCodes[n];
		generateType(*i, tc);
	}

	// Sort the types by hash.
	std::sort(typeCodes.begin(), typeCodes.end(), hashSort);


	// Generate the code for the struct body.
	std::string body = "int a;\nunion {\n";
	std::set<std::string> bodyDeps;

	n = 0;
	for (std::vector<TypeCode>::iterator i = typeCodes.begin(); i != typeCodes.end(); i++, n++) {
		const TypeCode& tc = *i;
		bodyDeps.insert(tc.deps.begin(), tc.deps.end());

		std::stringstream s;
		s << tc.code << " v" << n << ";\n";
		body += "    " + s.str();
	}

	body += "};\n";


	// Pick a name.
	std::string name;
	do {
		std::stringstream s;
		s << "union" << rand();
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
	for (std::set<std::string>::const_iterator i = bodyDeps.begin(); i != bodyDeps.end(); i++) {
		addDependency(def.name, *i, false);
	}
}
