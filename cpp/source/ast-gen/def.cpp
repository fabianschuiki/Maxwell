/* Copyright © 2013 Fabian Schuiki */
#include "def.hpp"

/**
 * This function generates all AST nodes. It is called by the main function
 * to build the AST before the nodes are generated.
 */
void buildAST(Builder &node)
{
	node("FunctionDefinition")
		.attr("name", "string")
		.attr("in", "FuncArgTuple")
		.attr("out", "FuncArgTuple")
		.attr("body", "FuncBody");

	node("FuncArgTuple")
		.attr("args", "[FuncArg]");
	node("FuncArg")
		.attr("name", "string")
		.attr("type", "string");

	node("FuncBody")
		.attr("stmts", "[Stmt]");
}