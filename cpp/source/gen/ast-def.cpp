/* Copyright © 2013 Fabian Schuiki */
#include "ast-def.hpp"

/**
 * This function generates all AST nodes. It is called by the main function
 * to build the AST before the nodes are generated.
 */
void buildAST(Builder &node)
{
	// Groups
	node.groups["type"] = "GenericType|DefinedType|UnionType|TupleType";
	node.groups["typeExpr"] = "NamedTypeExpr|UnionTypeExpr|TupleTypeExpr";

	// Interfaces
	Node& graph = node("@Graph")
		.attr("graphPrev", "&any");
	Node& call = node("@Call")
		.attr("callName", "string")
		.child("callArgs", "[CallArg]")
		.child("callCandidates", "[CallCandidate]")
		.attr("selectedCallCandidate", "&CallCandidate");
	Node& type = node("@Type")
		.attr("possibleType", "#type")
		.attr("requiredType", "#type")
		.attr("actualType", "#type");
	Node& typeExpr = node("@TypeExpr")
		.child("evaluatedType", "#type");
	Node& variable = node("@Variable") // everything that looks like a variable (var, val, func arg, ...)
		.intf(type)
		.attr("name", "string")
		.child("type", "#typeExpr");

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
		.intf(graph)./*intf(type)*/intf(variable)
		/*.attr("name", "string")
		.child("type", "any")*/;
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
		.intf(graph)./*intf(type).*/intf(variable)
		/*.attr("name", "string")
		.child("type", "#typeExpr")*/
		.child("initialExpr", "@Type");
	node("CallExpr")
		.intf(graph).intf(call).intf(type)
		.attr("name", "string")
		.child("context", "any")
		.child("args", "[CallExprArg]");
	node("CallExprArg")
		.intf(graph)
		.attr("name", "string")
		.child("expr", "@Type");
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
	node("MemberAccessExpr")
		.intf(graph).intf(type)
		.child("expr", "any")
		.attr("name", "string");

	// Type Expressions
	node("NamedTypeExpr")
		.intf(graph).intf(typeExpr)
		.attr("name", "string")
		.attr("definition", "&any");
	node("UnionTypeExpr")
		.intf(graph).intf(typeExpr)
		.child("types", "[#typeExpr]");
	node("TupleTypeExpr")
		.intf(graph).intf(typeExpr)
		.child("args", "[TupleTypeExprArg]");
	node("TupleTypeExprArg")
		.intf(graph).intf(typeExpr)
		.attr("name", "string")
		.child("expr", "#typeExpr");

	// Types
	node("GenericType");
	node("DefinedType")
		.attr("definition", "&any");
	node("UnionType")
		.child("types", "[#type]");
	node("TupleType")
		.child("args", "[TupleTypeArg]");
	node("TupleTypeArg")
		.attr("name", "string")
		.child("type", "#type");
}