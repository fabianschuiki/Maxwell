/* Copyright © 2013 Fabian Schuiki */
#include "ast-gen.hpp"

/**
 * This function generates all AST nodes. It is called by the main function
 * to build the AST before the nodes are generated.
 */
void buildAST(Builder &node)
{
	// Groups
	node.groups["type"] = "GenericType|InvalidType|DefinedType|UnionType|TupleType|FuncType|TypeSet";
	node.groups["typeExpr"] = "NamedTypeExpr|UnionTypeExpr|TupleTypeExpr|QualifiedTypeExpr";
	node.groups["qualifier"] = "StructureQualifier|InterfaceQualifier|NativeQualifier|RangeQualifier";

	// Interfaces
	Node& graph = node("@Graph")
		.attr("graphPrev", "&any");
	Node& call = node("@Call")
		.attr("callName", "string")
		.child("callArgs", "[@CallArg]")
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
	Node& callArg = node("@CallArg") // everything that looks like a call argument (expr and optional name)
		.attr("name", "string")
		.attr("expr", "@Type");

	// Anonymous interfaces.
	node("@Named").attr("name", "string");

	// Call Support.
	node("CallArg")
		.attr("name", "string")
		.attr("expr", "&@Type");
	node("CallCandidate")
		.attr("func", "&FuncDef")
		.child("args", "[CallCandidateArg]")
		.attr("feasible", "bool")
		.attr("cost", "int")
		.intf(type);
	node("CallCandidateArg")
		.attr("arg", "&@CallArg")
		.intf(type);

	// Nodes
	node("FuncDef")
		.intf(graph)
		.attr("name", "string")
		.child("in", "[FuncArg]")
		.child("out", "[FuncArg]")
		.child("body", "FuncBody")
		.child("type", "FuncType");
	node("FuncArg")
		.intf(graph).intf(variable);
	node("FuncBody")
		.intf(graph)
		.child("stmts", "[any]");
	node("ExprStmt")
		.intf(graph)
		.child("expr", "any");

	node("TypeDef")
		.intf(graph)
		.attr("name", "string")
		.child("type", "#typeExpr");

	// Expressions
	node("IdentifierExpr")
		.intf(graph).intf(type)
		.attr("name", "string")
		.attr("bindingTarget", "&any");
	node("VarDefExpr")
		.intf(graph).intf(variable)
		.child("initialExpr", "@Type");
	node("CallExpr")
		.intf(graph)
		.attr("name", "string")
		.child("context", "any")
		.child("callArgs", "[CallExprArg]")
		.intf(call).intf(type);
	node("CallExprArg")
		.intf(graph)
		.attr("name", "string")
		.child("expr", "@Type");
	node("BinaryOpExpr")
		.intf(graph)
		.attr("operatorName", "string") // 'operator' would be a keyword
		.child("lhs", "any")
		.child("rhs", "any")
		.intf(call).intf(type);
	node("UnaryOpExpr")
		.intf(graph)
		.attr("operatorName", "string")
		.attr("postfix", "bool")
		.child("expr", "any")
		.intf(call).intf(type);
	node("MemberAccessExpr")
		.intf(graph).intf(type)
		.child("expr", "any")
		.attr("name", "string");
	node("AssignmentExpr")
		.child("lhs", "any")
		.child("rhs", "any")
		.intf(graph).intf(type);

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
	node("QualifiedTypeExpr")
		.intf(graph).intf(typeExpr)
		.child("exprs", "[#qualifier]");

	// Type Qualifiers
	node("StructureQualifier")
		.intf(graph)
		.attr("mode", "string")
		.child("stmts", "[StructureQualifierMember]");
	node("StructureQualifierMember")
		.intf(graph)
		.attr("name", "string")
		.child("type", "#typeExpr");
	node("InterfaceQualifier")
		.intf(graph)
		.child("stmts", "[any]");
	node("NativeQualifier")
		.intf(graph)
		.attr("name", "string");
	node("RangeQualifier")
		.intf(graph)
		.attr("name", "string")
		.attr("min", "string")
		.attr("max", "string");

	// Types
	node("GenericType").describe("str << \"*\";");
	node("InvalidType").describe("str << \"<invalid>\";");
	node("DefinedType")
		.attr("definition", "&any")
		.describe("str << getDefinition()->needNamed()->getName();");
	node("UnionType")
		.child("types", "[#type]")
		.describe("\
			bool first = true;\
			for (NodeVector::iterator it = types.begin(); it != types.end(); it++) {\
				if (!first) str << \"|\";\
				first = false;\
				str << (*it)->describe(depth-1);\
			}");
	node("TupleType")
		.child("args", "[TupleTypeArg]")
		.describe("\
			bool first = true;\
			for (NodeVector::iterator it = args.begin(); it != args.end(); it++) {\
				if (!first) str << \", \";\
				first = false;\
				str << (*it)->describe(depth-1);\
			}");
	node("TupleTypeArg")
		.attr("name", "string")
		.child("type", "#type")
		.describe("if (!name.empty()) str << name << \": \"; str << type->describe(depth-1);");
	node("FuncType")
		.child("in", "TupleType")
		.child("out", "TupleType")
		.describe("str << in->describe(depth-1) << \"->\" << out->describe(depth-1);");
	node("TypeSet")
		.child("types", "[#type]")
		.describe("\
			str << \"{\";\
			bool first = true;\
			for (NodeVector::iterator it = types.begin(); it != types.end(); it++) {\
				if (!first) str << \", \";\
				first = false;\
				str << (*it)->describe(depth-1);\
			}\
			str << \"}\";");
}