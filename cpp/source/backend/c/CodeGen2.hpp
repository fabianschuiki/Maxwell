/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include <ast/nodes/nodes.hpp>
#include <sqlite3.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

#define DECL_ROOT(type) void generate##type(const ast::type::Ptr& node)
#define DECL_EXPR(type) void generate##type(const ast::type::Ptr& node, Context& ctx)
#define DECL_TYPE(type) void generate##type(const ast::type::Ptr& node)


namespace ast {
	struct Node;
	struct NodeId;
	struct Repository;
}

namespace backendc {

struct Fragment;

struct CodeGen2
{
	typedef ast::Repository Repository;
	typedef ast::NodeId NodeId;
	typedef boost::shared_ptr<ast::Node> NodePtr;

	CodeGen2(Repository& repo, sqlite3* db);
	~CodeGen2();

	template<class T> void run(const T& t) {
		root(t);
		postprocess();
	}

	template<class Iterator> void run(Iterator first, Iterator last) {
		for (Iterator i = first; i != last; i++)
			root(*i);
		postprocess();
	}

private:
	Repository& repo;
	sqlite3* db;

	// sqlite statements
	sqlite3_statement insertFragStmt;
	sqlite3_statement insertDepStmt;

	void root(const NodeId& id);
	void root(const NodePtr& node);
	void expr(const NodePtr& node);
	void type(const NodePtr& node);
	void postprocess();

	void addFragment(const Fragment& frag);
	void addDependency(const std::string& frag, const std::string& dep, bool after);

	// Declare nodes that can be compiled as root.
	DECL_ROOT(FuncDef);
	DECL_ROOT(TypeDef);

	// Declare nodes that can be compiled as expressions.

	// Declare nodes that can be compiled as types.
};

} // namespace backendc
