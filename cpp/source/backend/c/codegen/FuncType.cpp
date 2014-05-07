/* Copyright (c) 2014 Fabian Schuiki */
#include "detail.hpp"

DEF_TYPE(FuncType)
{
	if (lookupType(out))
		return;

	// Generate the function arguments. If the input type is a tuple, it is
	// translated into a list of arguments. If it is the nil type, it is
	// translated into an empty argument list.
	std::string argsCode;
	std::set<std::string> argsDeps; // fragments the arguments depend on

	if (const TupleType::Ptr& inType = TupleType::from(node->getIn())) {
		const NodeVector& args = inType->getArgs();

		for (NodeVector::const_iterator i = args.begin(); i != args.end(); i++) {
			const TupleTypeArg::Ptr& arg = TupleTypeArg::needFrom(*i);

			TypeCode tc;
			generateType(arg->getType(), tc);
			argsDeps.insert(tc.deps.begin(), tc.deps.end());

			if (i != args.begin())
				argsCode += ", ";
			argsCode += tc.code;
		}
	}
	else if (!node->getIn()->isKindOf(kNilType)) {
		throw std::runtime_error("FuncType " + node->getId().str() + " '" + node->describe() + "' must either have TupleType or NilType as input");
	}

	// Generate the return type. This is either 'void' if the output of the
	// function is the nil type, or the appropriate type otherwise.
	std::string returnType;
	if (node->getOut()->isKindOf(kNilType)) {
		returnType = "void";
	} else {
		TypeCode tc;
		generateType(node->getOut(), tc);
		returnType = tc.code;
		argsDeps.insert(tc.deps.begin(), tc.deps.end());
	}


	// Pick a name.
	std::string name;
	do {
		std::stringstream s;
		s << "func" << rand() << "_t";
		name = makeFriendly(s.str());
	} while (!isRefUnused(name));


	// Synthesize the definition of the type.
	Fragment def;
	def.name  = out.hash;
	def.code  = "typedef " + returnType + " (*" + name + ")(" + argsCode + ");";
	def.ref   = name;
	def.group = "types.h";

	// Add the fragment to the database, together with all its dependencies.
	addFragment(def);
	for (std::set<std::string>::const_iterator i = argsDeps.begin(); i != argsDeps.end(); i++) {
		addDependency(def.name, *i, false);
	}
}
