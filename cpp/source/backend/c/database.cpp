/* Copyright (c) 2014 Fabian Schuiki */
#include "database.hpp"
#include <sqlite3.hpp>
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
		"fragid integer not null, "
		"depid integer not null, "
		"after boolean default 0 not null, "
		"FOREIGN KEY (fragid) REFERENCES fragments(id) ON DELETE CASCADE, "
		"FOREIGN KEY (depid) REFERENCES fragments(id))", db);
	runStmt("CREATE UNIQUE INDEX IF NOT EXISTS fragments_name ON fragments (name)", db);
	runStmt("CREATE INDEX IF NOT EXISTS dependencies_fragid ON dependencies (fragid)", db);
	runStmt("COMMIT TRANSACTION", db);
}
