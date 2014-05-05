/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "CodeGen2.hpp"
#include <ast/Node.hpp>
#include <ast/Repository.hpp>
#include "code.hpp"
using namespace backendc;


#define REGISTER_ROOT(type) if (const ast::type::Ptr& n = ast::type::from(node)) { return generate##type(n); }
#define REGISTER_EXPR(type) if (const ast::type::Ptr& n = ast::type::from(node)) { return generate##type(n, ctx); }
#define REGISTER_TYPE(type) if (const ast::type::Ptr& n = ast::type::from(node)) { return generate##type(n); }


CodeGen2::CodeGen2(Repository& repo, sqlite3* db): repo(repo), db(db)
{
	insertFragStmt.prepare(db,
		"REPLACE INTO fragments (name,code,ref,grp) VALUES (?,?,?,?)");
	insertDepStmt.prepare(db,
		"REPLACE INTO dependencies (frag,name,after) VALUES ("
			"(SELECT id FROM fragments WHERE name = ?),?,?)");
}

CodeGen2::~CodeGen2()
{
}


void CodeGen2::root(const NodeId& id)
{
	root(repo.getNode(id));
}

void CodeGen2::root(const NodePtr& node)
{
	REGISTER_ROOT(FuncDef);
	REGISTER_ROOT(TypeDef);

	// Throw an exception if no code could be generated.
	throw std::runtime_error(
		"Unable to generate code as root for node " + node->getId().str() +
		" (a " + node->getClassName() + ")");
}

void CodeGen2::expr(const NodePtr& node)
{
	// Throw an exception if no code could be generated.
	throw std::runtime_error(
		"Unable to generate code as expression for node " + node->getId().str() +
		" (a " + node->getClassName() + ")");
}

void CodeGen2::type(const NodePtr& node)
{
	// Throw an exception if no code could be generated.
	throw std::runtime_error(
		"Unable to generate code as type for node " + node->getId().str() +
		" (a " + node->getClassName() + ")");
}


void CodeGen2::postprocess()
{
	std::cout << "postprocessing\n";
}


/** Adds a new fragment to the database. */
void CodeGen2::addFragment(const Fragment& frag)
{
	sqlite3_throw(bind_text(insertFragStmt, 1, frag.name.c_str(), -1, SQLITE_STATIC));
	sqlite3_throw(bind_text(insertFragStmt, 2, frag.code.c_str(), -1, SQLITE_STATIC));
	sqlite3_throw(bind_text(insertFragStmt, 3, frag.ref.c_str(), -1, SQLITE_STATIC));
	sqlite3_throw(bind_text(insertFragStmt, 4, frag.group.c_str(), -1, SQLITE_STATIC));
	insertFragStmt.step();
	insertFragStmt.reset();
}

/** Adds a new dependency to the database, indicating that the fragment named
 * %frag depends on the fragment named %dep. Note that the name %frag is
 * resolved to a fragment ID, which is only possible if %frag actually exists
 * in the database. */
void CodeGen2::addDependency(const std::string& frag, const std::string& dep, bool after)
{
	sqlite3_throw(bind_text(insertDepStmt, 1, frag.c_str(), -1, SQLITE_STATIC));
	sqlite3_throw(bind_text(insertDepStmt, 2, dep.c_str(), -1, SQLITE_STATIC));
	sqlite3_throw(bind_int(insertDepStmt, 3, after));
	insertDepStmt.step();
	insertDepStmt.reset();
}
