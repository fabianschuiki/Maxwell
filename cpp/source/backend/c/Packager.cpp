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

	// Prepare a SQL statement that fetches a fragment from the database.
	sqlite3_stmt *stmt;
	rc = sqlite3_prepare_v2(db, "SELECT code,ref FROM fragments WHERE name = ?", -1, &stmt, NULL);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to prepare fragment fetch statement");

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
		rc = sqlite3_bind_text(stmt, 1, n.c_str(), -1, SQLITE_STATIC);
		if (rc != SQLITE_OK)
			throw sqlite3_exception(rc, "Unable to bind name in fragment fetch statement");

		// Fetch the result from the database. If sqlite3_step() returns DONE,
		// nothing was found in the database and an error should be returned.
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_DONE)
			throw std::runtime_error("No fragment named '" + n + "' found in the database");
		else if (rc != SQLITE_ROW)
			throw sqlite3_exception(rc, "Unable to step fragment fetch statement");

		// Create the fragment from the table row.
		std::string frag_code = (const char*)sqlite3_column_text(stmt, 0);
		std::string frag_ref  = (const char*)sqlite3_column_text(stmt, 1);
		std::cout << "[fragment " << n << "] ref = '" << frag_ref << "', code = " << frag_code << '\n';

		// Reset the statement such that it may be reused in the next loop
		// iteration.
		rc = sqlite3_reset(stmt);
		if (rc != SQLITE_OK)
			throw sqlite3_exception(rc, "Unable to reset fragment fetch statement");

		std::cout << "gathering " << n << '\n';
	}

	// Dispose of the statement.
	rc = sqlite3_finalize(stmt);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to finalize fragment fetch statement");
}
