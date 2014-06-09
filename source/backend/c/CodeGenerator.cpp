/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "CodeGenerator.hpp"
#include <ast/Node.hpp>
#include <ast/Repository.hpp>
#include <base64.hpp>
#include "code.hpp"
using namespace backendc;


// Defines that make the handling of the different node types easier.
#define REGISTER_ROOT(type) if (const ast::type::Ptr& n = ast::type::from(node)) { return generate##type(n); }
#define REGISTER_EXPR(type) if (const ast::type::Ptr& n = ast::type::from(node)) { generate##type(n, out, ctx); goto done; }
#define REGISTER_TYPE(type) if (const ast::type::Ptr& n = ast::type::from(node)) { return generate##type(n, out); }

#define REGISTER_EXPR_INTF(type) if (ast::type##Interface* n = node->as##type()) { return generate##type##Intf(n, out, ctx); }
#define REGISTER_TYPE_INTF(type) if (ast::type##Interface* n = node->as##type()) { return generate##type##Intf(n, out); }


CodeGenerator::CodeGenerator(Repository& repo, sqlite3* db): repo(repo), db(db)
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

CodeGenerator::~CodeGenerator()
{
}


void CodeGenerator::generateRoot(const NodeId& id)
{
	generateRoot(repo.getNode(id));
}

void CodeGenerator::generateRoot(const NodePtr& node)
{
	REGISTER_ROOT(FuncDef);
	REGISTER_ROOT(TypeDef);

	// Throw an exception if no code could be generated.
	throw std::runtime_error(
		"Unable to generate root code for node " + node->getId().str() +
		" (a " + node->getClassName() + ")");
}

void CodeGenerator::generateExpr(const NodePtr& node, ExprCode& out, Context& ctx)
{
	REGISTER_EXPR(AssignmentExpr);
	REGISTER_EXPR(BlockExpr);
	REGISTER_EXPR(ForExpr);
	REGISTER_EXPR(FuncExpr);
	REGISTER_EXPR(IdentifierExpr);
	REGISTER_EXPR(IfCaseExpr);
	REGISTER_EXPR(IfExpr);
	REGISTER_EXPR(IndexOpExpr);
	REGISTER_EXPR(NumberConstExpr);
	REGISTER_EXPR(TupleExpr);
	REGISTER_EXPR(TypelessVarDefExpr);
	REGISTER_EXPR(VarDefExpr);
	REGISTER_EXPR_INTF(Call);

	// Throw an exception if no code could be generated.
	throw std::runtime_error(
		"Unable to generate expression code for node " + node->getId().str() +
		" (a " + node->getClassName() + ")");

done:
	// Upon completion, execution jumps here to generate mapped types.
	generateMappedType(node->needType()->getActualType(), out, ctx);
}

void CodeGenerator::generateType(const NodePtr& node, TypeCode& out)
{
	// Calculate the type's hash which will be used as its name in the
	// database. The hash is used to coordinate lookupType() and the name
	// assigned to a type upon generation.
	out.hash = base64::encode(node->describe());

	// Register the types.
	REGISTER_TYPE(DefinedType);
	REGISTER_TYPE(FuncType);
	REGISTER_TYPE(TupleType);
	REGISTER_TYPE(UnionType);

	// Throw an exception if no code could be generated.
	throw std::runtime_error(
		"Unable to generate type code for node " + node->getId().str() +
		" (a " + node->getClassName() + "), hash '" + out.hash + "'");
}

void CodeGenerator::generateMappedType(const NodePtr& node, ExprCode& out, Context& ctx)
{
	if (const ast::UnionMappedType::Ptr& type = ast::UnionMappedType::from(node)) {
		generateUnionMappedType(type, out, ctx);
	}
}



void CodeGenerator::postprocess()
{
}


bool CodeGenerator::lookupType(TypeCode& out)
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
bool CodeGenerator::isRefUnused(const std::string& ref)
{
	sqlite3_throw(bind_text(refUnusedStmt, 1, ref.c_str(), -1, SQLITE_STATIC));
	bool result = !refUnusedStmt.step();
	refUnusedStmt.reset();
	return result;
}


/** Adds a new fragment to the database. */
void CodeGenerator::addFragment(const Fragment& frag)
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
void CodeGenerator::addDependency(const std::string& frag, const std::string& dep, bool after)
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
std::string CodeGenerator::makeFuncName(const ast::FuncDef::Ptr& node)
{
	return makeFriendly(node->getName());
}

/** Returns the unique name for the given type. It is unique within the current
 * database, and multiple calls with the same node will yield the same name. */
std::string CodeGenerator::makeTypeName(const ast::TypeDef::Ptr& node)
{
	return makeFriendly(node->getName());
}

/** Returns a C-friendly version of the given name, potentially replacing
 * disallowed characters. */
std::string CodeGenerator::makeFriendly(const std::string& name)
{
	std::string result;
	if (!name.empty() && name[0] >= '0' && name [0] <= '9')
		result += '_';
	for (std::string::const_iterator i = name.begin(); i != name.end(); i++) {
		if (*i == '.') {
			result += '_';
		} else if (
			(*i >= 'a' && *i <= 'z') ||
			(*i >= 'A' && *i <= 'Z') ||
			(*i >= '0' && *i <= '9') || *i == '_') {
			result += *i;
		} else {
			char buf[8];
			snprintf(buf, 8, "c%02X", *i);
			result += buf;
		}
	}
	return result;
}
