/* Copyright (c) 2014 Fabian Schuiki */
#include "Packager.hpp"
#include <sqlite3.hpp>
#include <iostream>
#include <queue>
using namespace backendc;


Packager::Packager(sqlite3* db): db(db)
{
}

Packager::~Packager()
{
}

void Packager::run(const std::string& name)
{
	int rc;

	// Prepare a SQL statement that fetches a fragment from the database, and
	// one that fetches all dependencies.
	sqlite3_stmt *fragStmt, *depsStmt;

	rc = sqlite3_prepare_v2(db, "SELECT rowid,code,ref FROM fragments WHERE name = ?", -1, &fragStmt, NULL);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to prepare fragment fetch statement");

	rc = sqlite3_prepare_v2(db, "SELECT name FROM dependencies JOIN fragments ON fragments.rowid = depid WHERE fragid = ?", -1, &depsStmt, NULL);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to prepare dependency fetch statement");

	// Create the queue that holds the fragment names that need to be gathered
	// from the database.
	std::queue<std::string> names;
	names.push(name);
	std::cout << "packaging " << name << '\n';

	// Fetch all fragments in the queue from the database, adding dependencies
	// to the queue again to have them fetched as well.
	while (!names.empty()) {
		std::string n = names.front();
		names.pop();

		// Bind the first parameter to the name of the fragment.
		rc = sqlite3_bind_text(fragStmt, 1, n.c_str(), -1, SQLITE_STATIC);
		if (rc != SQLITE_OK)
			throw sqlite3_exception(rc, "Unable to bind name in fragment fetch statement");

		// Fetch the result from the database. If sqlite3_step() returns DONE,
		// nothing was found in the database and an error should be returned.
		rc = sqlite3_step(fragStmt);
		if (rc == SQLITE_DONE)
			throw std::runtime_error("No fragment named '" + n + "' found in the database");
		else if (rc != SQLITE_ROW)
			throw sqlite3_exception(rc, "Unable to step fragment fetch statement");

		// Create the fragment from the table row.
		sqlite3_int64 fragRowId = sqlite3_column_int64(fragStmt, 0);
		std::string   fragCode  = (const char*)sqlite3_column_text(fragStmt, 1);
		std::string   fragRef   = (const char*)sqlite3_column_text(fragStmt, 2);
		std::cout << "[fragment #" << fragRowId << " " << n << "] ref = '" << fragRef << "', code = " << fragCode << '\n';

		

		// Bind the fragment rowid to the first argument of the dependency
		// statement.
		rc = sqlite3_bind_int64(depsStmt, 1, fragRowId);
		if (rc != SQLITE_OK)
			throw sqlite3_exception(rc, "Unable to bind fragment rowid in dependency fetch statement");

		// Reset the statements such that it may be reused in the next loop
		// iteration.
		rc = sqlite3_reset(fragStmt);
		if (rc != SQLITE_OK)
			throw sqlite3_exception(rc, "Unable to reset fragment fetch statement");

		rc = sqlite3_reset(depsStmt);
		if (rc != SQLITE_OK)
			throw sqlite3_exception(rc, "Unable to reset dependency fetch statement");

		std::cout << "gathering " << n << '\n';
	}

	// Dispose of the statements.
	rc = sqlite3_finalize(fragStmt);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to finalize fragment fetch statement");

	rc = sqlite3_finalize(depsStmt);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to finalize dependency fetch statement");
}
