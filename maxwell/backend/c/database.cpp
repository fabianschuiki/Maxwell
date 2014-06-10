/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/sqlite3.hpp"
#include "maxwell/backend/c/database.hpp"
#include <iostream>
using namespace backendc;

static void runStmt(const std::string& sql, sqlite3* db)
{
	int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to execute statement '" + sql + "'");
}

void database::prepareFragmentsSchema()
{
	runStmt("BEGIN TRANSACTION", db);
	runStmt("CREATE TABLE IF NOT EXISTS fragments ("
		"id integer primary key, "
		"name varchar(128), "
		"code text, "
		"ref text, "
		"grp varchar(128))", db);
	runStmt("CREATE TABLE IF NOT EXISTS dependencies ("
		"id integer primary key, "
		"frag integer not null, "
		"name varchar(128) not null, "
		"after boolean default 0 not null, "
		"FOREIGN KEY (frag) REFERENCES fragments(id) ON DELETE CASCADE)", db);
	runStmt("CREATE UNIQUE INDEX IF NOT EXISTS fragments_name ON fragments (name)", db);
	runStmt("CREATE INDEX IF NOT EXISTS fragments_ref ON fragments (ref)", db);
	runStmt("CREATE INDEX IF NOT EXISTS dependencies_frag ON dependencies (frag)", db);
	runStmt("CREATE UNIQUE INDEX IF NOT EXISTS dependencies_frag_name ON dependencies (frag,name)", db);
	runStmt("COMMIT TRANSACTION", db);
}
