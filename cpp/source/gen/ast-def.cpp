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
		.child("in", "FuncArgTuple")
		.child("out", "FuncArgTuple")
		.child("body", "FuncBody");

	node("FuncArgTuple")
		.intf(graph)
		.child("args", "[FuncArg]");
	node("FuncArg")
		.intf(graph)
		.attr("name", "string")
		.attr("type", "string");

	node("FuncBody")
		.intf(graph)
		.child("stmts", "[Stmt]");
}