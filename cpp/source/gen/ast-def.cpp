/* Copyright © 2013 Fabian Schuiki */
#include "ast-def.hpp"

/**
 * This function generates all AST nodes. It is called by the main function
 * to build the AST before the nodes are generated.
 */
void buildAST(Builder &node)
{
	// Interfaces
	Node& graph = node("@graph")
		.attr("graphPrev", "&any");
	/*Node& typeDef = node("@typeDef")
		.attr("name", "string");*/

	// Nodes
	node("FuncDef")
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
		.child("type", "any");
	node("FuncBody")
		.intf(graph)
		.child("stmts", "[any]");
	node("ExprStmt")
		.intf(graph)
		.child("expr", "any");

	node("TypeDef")
		.intf(graph)
		.attr("name", "string");

	// Expressions
	node("IdentifierExpr")
		.intf(graph)
		.attr("name", "string")
		.attr("bindingTarget", "&any");
	node("VarDefExpr")
		.intf(graph)
		.attr("name", "string")
		.child("type", "any")
		.child("initialExpr", "any");

	// Type Expressions
	node("NamedType")
		.intf(graph)
		.attr("name", "string")
		.attr("definition", "&any");
	node("UnionType")
		.intf(graph)
		.child("types", "[any]");
}