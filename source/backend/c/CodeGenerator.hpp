/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include <ast/nodes/nodes.hpp>
#include <sqlite3.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <set>
#include <string>

#define DECL_ROOT(type) void generate##type(const ast::type::Ptr& node)
#define DECL_EXPR(type) void generate##type(const ast::type::Ptr& node, ExprCode& out, Context& ctx)
#define DECL_TYPE(type) void generate##type(const ast::type::Ptr& node, TypeCode& out)

#define DECL_EXPR_INTF(type) void generate##type##Intf(ast::type##Interface* node, ExprCode& out, Context& ctx)
#define DECL_TYPE_INTF(type) void generate##type##Intf(ast::type##Interface* node, TypeCode& out)


namespace ast {
	struct Node;
	struct NodeId;
	struct Repository;
}

namespace backendc {

struct Fragment;
struct Context;
struct ExprCode;
struct TypeCode;

struct CodeGenerator
{
	typedef ast::Repository Repository;
	typedef ast::NodeId NodeId;
	typedef boost::shared_ptr<ast::Node> NodePtr;

	CodeGenerator(Repository& repo, sqlite3* db);
	~CodeGenerator();

	template<class T> void run(const T& t) {
		generateRoot(t);
		postprocess();
	}

	template<class Iterator> void run(Iterator first, Iterator last) {
		for (Iterator i = first; i != last; i++)
			generateRoot(*i);
		postprocess();
	}

	std::map<NodeId,std::string> names;

private:
	Repository& repo;
	sqlite3* db;
	std::set<std::string> existingTypesCache;

	// sqlite statements
	sqlite3_statement insertFragStmt;
	sqlite3_statement insertDepStmt;
	sqlite3_statement typeExistsStmt;
	sqlite3_statement refUnusedStmt;

	void generateRoot(const NodeId& id);
	void generateRoot(const NodePtr& node);
	void generateExpr(const NodePtr& node, ExprCode& out, Context& ctx);
	void generateType(const NodePtr& node, TypeCode& out);
	void postprocess();

	bool lookupType(TypeCode& out);
	bool isRefUnused(const std::string& ref);

	void addFragment(const Fragment& frag);
	void addDependency(const std::string& frag, const std::string& dep, bool after);

	std::string makeFriendly(const std::string& name);
	std::string makeFuncName(const ast::FuncDef::Ptr& node);
	std::string makeTypeName(const ast::TypeDef::Ptr& node);

	// Declare nodes that can be compiled as root.
	DECL_ROOT(FuncDef);
	DECL_ROOT(TypeDef);

	// Declare nodes that can be compiled as expressions.
	DECL_EXPR(AssignmentExpr);
	DECL_EXPR(BlockExpr);
	DECL_EXPR(ForExpr);
	DECL_EXPR(FuncExpr);
	DECL_EXPR(IdentifierExpr);
	DECL_EXPR(IfCaseExpr);
	DECL_EXPR(IfExpr);
	DECL_EXPR(IndexOpExpr);
	DECL_EXPR(NumberConstExpr);
	DECL_EXPR(TupleExpr);
	DECL_EXPR(TypelessVarDefExpr);
	DECL_EXPR(VarDefExpr);
	DECL_EXPR_INTF(Call);

	// Declare nodes that can be compiled as types.
	DECL_TYPE(DefinedType);
	DECL_TYPE(FuncType);
	DECL_TYPE(TupleType);
};

} // namespace backendc
