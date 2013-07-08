/* Copyright © 2013 Fabian Schuiki */
#include "ast-def.hpp"

/**
 * This function generates all AST nodes. It is called by the main function
 * to build the AST before the nodes are generated.
 */
void buildAST(Builder &node)
{
	Node& graph = node("@graph")
		.attr("graphPrev", "&any");

	node("FunctionDefinition")
		.intf(graph)
		.attr("name", "string")
		.attr("in", "FuncArgTuple")
		.attr("out", "FuncArgTuple")
		.attr("body", "FuncBody");

	node("FuncArgTuple")
		.intf(graph)
		.attr("args", "[FuncArg]");
	node("FuncArg")
		.intf(graph)
		.attr("name", "string")
		.attr("type", "string");

	node("FuncBody")
		.intf(graph)
		.attr("stmts", "[Stmt]");
}