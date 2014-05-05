/* Copyright (c) 2014 Fabian Schuiki */
#include "detail.hpp"

DEF_ROOT(FuncDef)
{
	std::cout << "generating FuncDef\n";

	std::string prototype = "void " + node->getName() + "()";
	std::string body = prototype + " { /* ... */ }";

	Fragment decl;
	decl.name  = node->getId().str() + "_decl";
	decl.code  = prototype + ";";
	decl.ref   = node->getName();
	decl.group = "funcs.h";

	Fragment def;
	def.name  = node->getId().str() + "_def";
	def.code  = body;
	def.ref   = node->getName();
	def.group = "funcs.c";

	addFragment(decl);
	addFragment(def);
	addDependency(decl.name, def.name, false); // declaration pulls in the definition somewhere in the code
}
