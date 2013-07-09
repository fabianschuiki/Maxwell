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
	Node& call = node("@call")
		.attr("callName", "string")
		.child("callArgs", "[CallArg]")
		.child("callCandidates", "[CallCandidate]")
		.attr("selectedCallCandidate", "&CallCandidate");
	Node& type = node("@type")
		.attr("possibleType", "any")
		.attr("requiredType", "any")
		.attr("actualType", "any");

	// Call Support.
	node("CallArg")
		.attr("name", "string")
		.attr("expr", "&any");
	node("CallCandidate")
		.attr("func", "&any");

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
		.intf(graph).intf(type)
		.attr("name", "string")
		.attr("bindingTarget", "&any");
	node("VarDefExpr")
		.intf(graph).intf(type)
		.attr("name", "string")
		.child("type", "any")
		.child("initialExpr", "any");
	node("CallExpr")
		.intf(graph).intf(call).intf(type)
		.attr("name", "string")
		.child("args", "[any]");
	node("BinaryOpExpr")
		.intf(graph).intf(call).intf(type)
		.attr("operatorName", "string") // 'operator' would be a keyword
		.child("lhs", "any")
		.child("rhs", "any");
	node("UnaryOpExpr")
		.intf(graph).intf(call).intf(type)
		.attr("operatorName", "string")
		.attr("postfix", "bool")
		.child("expr", "any");

	// Type Expressions
	node("GenericType")
		.intf(graph); // actually no required, but there's a bug ;)
	node("NamedType")
		.intf(graph)
		.attr("name", "string")
		.attr("definition", "&any");
	node("UnionType")
		.intf(graph)
		.child("types", "[any]");
}