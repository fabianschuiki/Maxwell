/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include <ast/nodes/nodes.hpp>
#include <sqlite3.hpp>
#include <boost/shared_ptr.hpp>
#include <set>
#include <string>

#define DECL_ROOT(type) void generate##type(const ast::type::Ptr& node)
#define DECL_EXPR(type) void generate##type(const ast::type::Ptr& node, ExprCode& out, Context& ctx)
#define DECL_TYPE(type) void generate##type(const ast::type::Ptr& node, TypeCode& out)


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

struct CodeGen2
{
	typedef ast::Repository Repository;
	typedef ast::NodeId NodeId;
	typedef boost::shared_ptr<ast::Node> NodePtr;

	CodeGen2(Repository& repo, sqlite3* db);
	~CodeGen2();

	template<class T> void run(const T& t) {
		generateRoot(t);
		postprocess();
	}

	template<class Iterator> void run(Iterator first, Iterator last) {
		for (Iterator i = first; i != last; i++)
			generateRoot(*i);
		postprocess();
	}

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
	DECL_EXPR(BlockExpr);

	// Declare nodes that can be compiled as types.
	DECL_TYPE(DefinedType);
	DECL_TYPE(TupleType);
};

} // namespace backendc
