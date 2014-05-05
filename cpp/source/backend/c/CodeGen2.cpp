/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "CodeGen2.hpp"
#include <ast/Node.hpp>
#include <ast/Repository.hpp>
#include <base64.hpp>
#include "code.hpp"
using namespace backendc;


// Defines that make the handling of the different node types easier.
#define REGISTER_ROOT(type) if (const ast::type::Ptr& n = ast::type::from(node)) { return generate##type(n); }
#define REGISTER_EXPR(type) if (const ast::type::Ptr& n = ast::type::from(node)) { return generate##type(n, out, ctx); }
#define REGISTER_TYPE(type) if (const ast::type::Ptr& n = ast::type::from(node)) { return generate##type(n, out); }


CodeGen2::CodeGen2(Repository& repo, sqlite3* db): repo(repo), db(db)
{
	insertFragStmt.prepare(db,
		"REPLACE INTO fragments (name,code,ref,grp) VALUES (?,?,?,?)");
	insertDepStmt.prepare(db,
		"REPLACE INTO dependencies (frag,name,after) VALUES ("
			"(SELECT id FROM fragments WHERE name = ?),?,?)");
	typeExistsStmt.prepare(db,
		"SELECT id FROM fragments WHERE name = ?");
	refUnusedStmt.prepare(db,
		"SELECT id FROM fragments WHERE ref = ?");
}

CodeGen2::~CodeGen2()
{
}


void CodeGen2::generateRoot(const NodeId& id)
{
	generateRoot(repo.getNode(id));
}

void CodeGen2::generateRoot(const NodePtr& node)
{
	REGISTER_ROOT(FuncDef);
	REGISTER_ROOT(TypeDef);

	// Throw an exception if no code could be generated.
	throw std::runtime_error(
		"Unable to generate code as root for node " + node->getId().str() +
		" (a " + node->getClassName() + ")");
}

void CodeGen2::generateExpr(const NodePtr& node, ExprCode& out, Context& ctx)
{
	REGISTER_EXPR(BlockExpr);

	// Throw an exception if no code could be generated.
	throw std::runtime_error(
		"Unable to generate code as expression for node " + node->getId().str() +
		" (a " + node->getClassName() + ")");
}

void CodeGen2::generateType(const NodePtr& node, TypeCode& out)
{
	// Calculate the type's hash which will be used as its name in the
	// database. The hash is used to coordinate lookupType() and the name
	// assigned to a type upon generation.
	out.hash = base64::encode(node->describe());

	// Register the types.
	REGISTER_TYPE(DefinedType);
	REGISTER_TYPE(TupleType);

	// Throw an exception if no code could be generated.
	throw std::runtime_error(
		"Unable to generate code as type for node " + node->getId().str() +
		" (a " + node->getClassName() + "), hash '" + out.hash + "'");
}


void CodeGen2::postprocess()
{
	std::cout << "postprocessing\n";
}


bool CodeGen2::lookupType(TypeCode& out)
{
	out.code = "%{" + out.hash + "}";
	out.deps.insert(out.hash);

	if (existingTypesCache.count(out.hash)) {
		return true;
	} else {
		sqlite3_throw(bind_text(typeExistsStmt, 1, out.hash.c_str(), -1, SQLITE_STATIC));
		bool exists = typeExistsStmt.step();
		typeExistsStmt.reset();
		if (exists) {
			existingTypesCache.insert(out.hash);
			return true;
		}
	}

	return false;
}

/** Returns true if the given ref does not yet exist in the fragments database.
 * Useful for determining whether a chosen name is unique. */
bool CodeGen2::isRefUnused(const std::string& ref)
{
	sqlite3_throw(bind_text(refUnusedStmt, 1, ref.c_str(), -1, SQLITE_STATIC));
	bool result = !refUnusedStmt.step();
	refUnusedStmt.reset();
	return result;
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

/** Returns the unique name for the given function. It is unique within the
 * current database, and multiple calls with the same node will yield the same
 * name. */
std::string CodeGen2::makeFuncName(const ast::FuncDef::Ptr& node)
{
	return makeFriendly(node->getName());
}

/** Returns the unique name for the given type. It is unique within the current
 * database, and multiple calls with the same node will yield the same name. */
std::string CodeGen2::makeTypeName(const ast::TypeDef::Ptr& node)
{
	return makeFriendly(node->getName());
}

/** Returns a C-friendly version of the given name, potentially replacing
 * disallowed characters. */
std::string CodeGen2::makeFriendly(const std::string& name)
{
	return name;
}
