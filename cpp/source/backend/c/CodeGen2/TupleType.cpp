/* Copyright (c) 2014 Fabian Schuiki */
#include "detail.hpp"

DEF_TYPE(TupleType)
{
	const NodeVector& args = node->getArgs();

	// Simplify tuples with only one field.
	if (args.size() == 1) {
		const TupleTypeArg::Ptr& arg = TupleTypeArg::needFrom(args[0]);
		return generateType(arg->getType(), out);
	}

	// If the has already been generated, there's no need to do anything.
	if (lookupType(out))
		return;


	// Generate the code for each field.
	std::string body;
	std::set<std::string> bodyDeps;
	int n = 0;

	for (NodeVector::const_iterator i = args.begin(); i != args.end(); i++) {
		const TupleTypeArg::Ptr& arg = TupleTypeArg::needFrom(*i);

		// Generate the type for this field.
		TypeCode tc;
		generateType(arg->getType(), tc);
		bodyDeps.insert(tc.deps.begin(), tc.deps.end());
		body += tc.code + " ";

		// Generate a C-friendly name for this field, either from the name
		// given to it by the author, or an indexed name.
		string name = makeFriendly(arg->getName(false));
		if (name.empty()) {
			char buffer[16];
			snprintf(buffer, 16, "v%i", n++);
			body += buffer;
		} else {
			body += name;
		}

		body += ";\n";
	}


	// Pick a name.
	std::string name;
	do {
		char buffer[32];
		snprintf(buffer, 32, "tuple%i", rand());
		name = buffer;
	} while (!isRefUnused(name));


	// Synthesize the definition.
	Fragment def;
	def.name  = out.hash;
	def.code  = "struct " + name + " {\n" + indent(body) + "};";
	def.ref   = "struct " + name;
	def.group = "tuples.h";

	// Add the fragment to the database and add all dependencies.
	addFragment(def);
	for (std::set<std::string>::const_iterator i = bodyDeps.begin(); i != bodyDeps.end(); i++) {
		addDependency(def.name, *i, false);
	}
}
