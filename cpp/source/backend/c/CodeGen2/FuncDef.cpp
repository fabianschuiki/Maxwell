/* Copyright (c) 2014 Fabian Schuiki */
#include "detail.hpp"

DEF_ROOT(FuncDef)
{
	Context ctx;
	std::set<std::string> argsDeps; // fragments the arguments depend on
	std::set<std::string> bodyDeps; // fragments the body depends on

	// Generate the function arguments.
	std::stringstream argsCode;
	const NodeVector& args = node->getIn();

	for (NodeVector::const_iterator i = args.begin(); i != args.end(); i++) {
		const FuncArg::Ptr& arg = FuncArg::needFrom(*i);

		// Generate a C-friendly name for this argument.
		std::string name = ctx.makeSymbol(arg->getName());
		ctx.vars[arg->getId()] = name;
		ctx.usedSymbols.insert(name);

		// Generate the code for this argument.
		TypeCode tc;
		generateType(arg->getActualType(), tc);
		argsDeps.insert(tc.deps.begin(), tc.deps.end());

		if (i != args.begin())
			argsCode << ", ";
		argsCode << tc.code << " " << name;
	}


	// Generate the code for the function body.
	ExprCode ec;
	generateExpr(node->getBody(), ec, ctx);
	bodyDeps.insert(ec.deps.begin(), ec.deps.end());


	// Generate the return type of the function.
	const FuncType::Ptr& nodeType = FuncType::needFrom(node->getType());
	const NodePtr& outType = nodeType->getOut();
	std::string returnType;

	if (outType->isKindOf(kNilType)) {
		returnType = "void";
	} else {
		TypeCode tc;
		generateType(outType, tc);
		argsDeps.insert(tc.deps.begin(), tc.deps.end());
		returnType = tc.code;
	}


	// Pick a name.
	std::string name = makeFuncName(node);

	// Synthesize the declaration of the function.
	Fragment decl;
	decl.name  = node->getId().str() + "_decl";
	decl.code  = returnType + " " + name + "(" + argsCode.str() + ");";
	decl.ref   = name;
	decl.group = "funcs.h";

	// Synthesize the definition of the function.
	Fragment def;
	def.name  = node->getId().str() + "_def";
	def.ref   = name;
	def.group = "funcs.c";
	def.code  = returnType + " " + name + "(" + argsCode.str() + ")\n{\n";

	for (std::vector<std::string>::const_iterator i = ctx.stmts.begin(); i != ctx.stmts.end(); i++) {
		def.code += "    " + indent(*i) + "\n";
	}
	if (node->getImplOut())
		def.code += "    return " + ec.code + ";\n";
	else if (!ec.isRef)
		def.code += "    " + ec.code + ";\n";

	def.code += "}";


	// std::string prototype = "void " + node->getName() + "()";
	// std::string body = prototype + " { /* ... */ }";

	// Fragment decl;
	// decl.code  = prototype + ";";
	// decl.ref   = node->getName();
	// decl.group = "funcs.h";

	// Fragment def;
	// def.name  = node->getId().str() + "_def";
	// def.code  = body;
	// def.ref   = node->getName();
	// def.group = "funcs.c";

	addFragment(decl);
	addFragment(def);
	addDependency(decl.name, def.name, false); // declaration pulls in the definition somewhere in the code

	// The dependencies of the arguments contribute cascade to both the
	// declaration and the definition.
	for (std::set<std::string>::const_iterator i = argsDeps.begin(); i != argsDeps.end(); i++) {
		addDependency(decl.name, *i, true);
		addDependency(def.name, *i, true);
	}

	// The dependencies of the body only contribute to the definition.
	for (std::set<std::string>::const_iterator i = ec.deps.begin(); i != ec.deps.end(); i++) {
		addDependency(def.name, *i, true);
	}
}
