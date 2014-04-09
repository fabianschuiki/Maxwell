/* Copyright © 2013 Fabian Schuiki */
#include "ast-gen.hpp"

/**
 * This function generates all AST nodes. It is called by the main function
 * to build the AST before the nodes are generated.
 */
void buildAST(Builder &node)
{
	// Groups
	node.groups["type"] = "GenericType|InvalidType|NilType|DefinedType|UnionType|TupleType|FuncType|TypeSet|QualifiedType|SpecializedType|UnionMappedType|OneTupleMappedType|CastType";
	node.groups["typeExpr"] = "NamedTypeExpr|NilTypeExpr|UnionTypeExpr|TupleTypeExpr|QualifiedTypeExpr|SpecializedTypeExpr";
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
		.child("typeExpr", "#typeExpr");
	Node& callArg = node("@CallArg") // everything that looks like a call argument (expr and optional name)
		.attr("name", "string")
		.attr("expr", "@Type");
	Node& callable = node("@Callable") // everything that looks like a function that can be called
		.attr("name", "string")
		// .attr("in", "[@CallableArg]")
		// .attr("out", "[@CallableArg]")
		.attr("type", "FuncType");
	// Node& callableArg = node("@CallableArg")
	// 	.intf(type)
	// 	.attr("name", "string");

	// Anonymous interfaces.
	node("@Named").attr("name", "string");

	// Call Support.
	node("CallArg")
		.attr("name", "string")
		.attr("expr", "&@Type");
	node("CallCandidate")
		.attr("func", "&@Callable")
		.child("args", "[CallCandidateArg]")
		.attr("feasible", "bool")
		.attr("cost", "int")
		.intf(type).intf(graph);
	node("CallCandidateArg")
		.attr("arg", "&@CallArg")
		.intf(type).intf(graph);

	// Nodes
	node("FuncDef")
		.intf(graph).intf(callable)
		.attr("name", "string")
		.child("in", "[FuncArg]")
		.child("out", "[FuncArg]")
		.child("body", "@Type")
		.child("type", "FuncType")
		.child("implOut", "bool");
	node("FuncArg")
		.intf(graph).intf(variable)/*.intf(callableArg)*/;
	node("TypeDef")
		.intf(graph)
		.attr("name", "string")
		.child("type", "#typeExpr");

	// Expressions
	node("NumberConstExpr")
		.intf(graph).intf(type)
		.attr("value", "string");
	node("StringConstExpr")
		.intf(graph).intf(type)
		.attr("value", "string");
	node("ArrayConstExpr")
		.intf(graph).intf(type)
		.child("exprs", "[@Type]")
		.attr("exprsType", "#type");
	node("SetConstExpr")
		.intf(graph).intf(type)
		.child("exprs", "[@Type]")
		.attr("exprsType", "#type");
	node("MapConstExpr")
		.intf(graph).intf(type)
		.child("pairs", "[MapConstExprPair]")
		.attr("keysType", "#type")
		.attr("valuesType", "#type");
	node("MapConstExprPair")
		.intf(graph)
		.child("key", "@Type")
		.child("value", "@Type");
	node("IdentifierExpr")
		.intf(graph).intf(type)
		.attr("name", "string")
		.attr("bindingTarget", "&any");
	node("VarDefExpr")
		.intf(graph).intf(variable)
		.child("initialExpr", "@Type");
	node("TypelessVarDefExpr")
		.intf(graph).intf(variable)
		.child("initialExpr", "@Type");
	node("CallExpr")
		.intf(graph)
		.attr("name", "string")
		.child("context", "any")
		.child("args", "[CallExprArg]")
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
		.intf(graph)
		.child("expr", "any")
		.attr("name", "string")
		.intf(type).intf(call);
	node("AssignmentExpr")
		.child("rhs", "any") // having the rhs first allows for easier handling of implicit setter calls
		.child("lhs", "any")
		.intf(graph).intf(type);
	node("IfCaseExpr")
		.child("conds", "[IfCaseExprCond]")
		.child("otherwise", "@Type")
		.intf(graph).intf(type);
	node("IfCaseExprCond")
		.child("expr", "@Type")
		.child("cond", "@Type")
		.intf(graph);
	node("IfExpr")
		.intf(graph).intf(type)
		.child("cond", "@Type")
		.child("body", "@Type")
		.child("elseExpr", "@Type");
	node("ForExpr")
		.intf(graph).intf(type)
		.child("init", "any")
		.child("cond", "@Type")
		.child("step", "any")
		.child("body", "@Type");
	node("BlockExpr")
		.intf(graph).intf(type)
		.child("exprs", "[@Type]");
	node("FuncExpr")
		.intf(graph).intf(type)
		.child("args", "[any]")
		.child("expr", "@Type");

	// Type Expressions
	node("NamedTypeExpr")
		.intf(graph).intf(typeExpr)
		.attr("name", "string")
		.attr("definition", "&any");
	node("NilTypeExpr")
		.intf(typeExpr);
	node("UnionTypeExpr")
		.intf(graph).intf(typeExpr)
		.child("types", "[#typeExpr]");
	node("TupleTypeExpr")
		.intf(graph).intf(typeExpr)
		.child("args", "[TupleTypeExprArg]");
	node("TupleTypeExprArg")
		.intf(graph)
		.attr("name", "string")
		.child("expr", "#typeExpr");
	node("QualifiedTypeExpr")
		.intf(graph).intf(typeExpr)
		.child("exprs", "[#qualifier]");
	node("SpecializedTypeExpr")
		.intf(graph).intf(typeExpr)
		.child("expr", "#typeExpr")
		.child("specExprs", "[#typeExpr]");

	// Type Qualifiers
	node("StructureQualifier")
		.intf(graph)
		.attr("mode", "string")
		.child("stmts", "[StructureQualifierMember]");
	node("StructureQualifierMember")
		.intf(graph)
		.attr("name", "string")
		.child("type", "#typeExpr")
		.child("implSetter", "ImplAccessor")
		.child("implGetter", "ImplAccessor");
	node("ImplAccessor")
		.intf(graph).intf(callable);
		// .child("in", "[ImplAccessorArg]")
		// .child("out", "[ImplAccessorArg]");
	// node("ImplAccessorArg")
	// 	.intf(graph).intf(callableArg);
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
	node("NilType").describe("str << \"nil\";");
	node("DefinedType")
		.attr("definition", "&any")
		.describe("str << (getDefinition()->implements(kNamedInterface) ? getDefinition()->needNamed()->getName() : getDefinition()->getId().str());");
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
			str << \"(\";\
			for (NodeVector::iterator it = args.begin(); it != args.end(); it++) {\
				if (!first) str << \", \";\
				first = false;\
				str << (*it)->describe(depth-1);\
			}\
			str << \")\";");
	node("TupleTypeArg")
		.attr("name", "string")
		.child("type", "#type")
		.describe("if (!name.empty()) str << name << \": \"; str << type->describe(depth-1);");
	node("FuncType")
		.child("in", "#type")
		.child("out", "#type")
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
	node("QualifiedType")
		.child("members", "[QualifiedTypeMember]")
		.child("funcs", "[any]")
		.child("natives", "[QualifiedTypeNative]")
		.child("ranges", "[any]");
	node("QualifiedTypeMember")
		.attr("name", "string")
		.child("type", "#type")
		.describe("str << name << \": \" << type->describe(depth-1);");
	node("QualifiedTypeNative")
		.attr("name", "string")
		.describe("str << \"native \" << name;");
	node("SpecializedType")
		.child("type", "#type")
		.child("specs", "[#type]")
		.describe("\
			str << type->describe(depth-1) << \"[\";\
			bool first = true;\
			for (NodeVector::iterator it = specs.begin(); it != specs.end(); it++) {\
				if (!first) str << \",\";\
				first = false;\
				str << (*it)->describe(depth-1);\
			}\
			str << \"]\";");
	node("UnionMappedType")
		.child("in", "#type")
		.child("out", "#type")
		.describe("str << out->describe(depth-1) << '(' << in->describe(depth-1) << ')';");
	node("OneTupleMappedType")
		.child("tuple", "#type")
		.describe("str << tuple->describe(depth-1) << \".0\";");
	node("CastType")
		.child("func", "&@Callable")
		.child("in", "#type")
		.child("out", "#type")
		.describe("str << out->describe(depth-1) << '(' << func.id << '<' << in->describe(depth-1) << ')';");
}