/* Copyright (c) 2014 Fabian Schuiki */
#include "Packager.hpp"
#include "Packager-detail.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
using namespace backendc;


/** Loads the fragment with the given name and all its dependencies recursively
 * from the database into the %fragments member. */
void Packager::collect(const std::string& name)
{
	int rc;

	// Prepare a SQL statement that fetches a fragment from the database, and
	// one that fetches all dependencies.
	sqlite3_stmt *fragStmt, *depsStmt;

	rc = sqlite3_prepare_v2(db, "SELECT id,code,ref,grp FROM fragments WHERE name = ?", -1, &fragStmt, NULL);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to prepare fragment fetch statement");

	rc = sqlite3_prepare_v2(db, "SELECT name,after FROM dependencies JOIN fragments ON fragments.id = depid WHERE fragid = ?", -1, &depsStmt, NULL);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to prepare dependency fetch statement");

	// Create the queue that holds the fragment names that need to be gathered
	// from the database.
	std::queue<std::string> names;
	names.push(name);

	// Fetch all fragments in the queue from the database, adding dependencies
	// to the queue again to have them fetched as well.
	while (!names.empty()) {
		const std::string& n = names.front();

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
		Fragment *frag = new Fragment;
		frag->name  = n;
		frag->id    = sqlite3_column_int(fragStmt, 0);
		frag->code  = (const char*)sqlite3_column_text(fragStmt, 1);
		frag->ref   = (const char*)sqlite3_column_text(fragStmt, 2);
		frag->group = (const char*)sqlite3_column_text(fragStmt, 3);
		fragments[frag->name] = frag;

		// Bind the fragment id to the first argument of the dependency
		// statement.
		rc = sqlite3_bind_int(depsStmt, 1, frag->id);
		if (rc != SQLITE_OK)
			throw sqlite3_exception(rc, "Unable to bind fragment id in dependency fetch statement");

		// Fetch the dependencies from the database. This query may return an
		// arbitrary number of names.
		while ((rc = sqlite3_step(depsStmt)) == SQLITE_ROW) {
			Dependency dep;
			dep.name  = (const char*)sqlite3_column_text(depsStmt, 0);
			dep.after = sqlite3_column_int(depsStmt, 1);
			if (!fragments.count(dep.name))
				names.push(dep.name);
			frag->deps.push_back(dep);
		}
		if (rc != SQLITE_DONE)
			throw sqlite3_exception(rc, "Unable to step dependency fetch statement");

		// Reset the statements such that it may be reused in the next loop
		// iteration.
		rc = sqlite3_reset(fragStmt);
		if (rc != SQLITE_OK)
			throw sqlite3_exception(rc, "Unable to reset fragment fetch statement");

		rc = sqlite3_reset(depsStmt);
		if (rc != SQLITE_OK)
			throw sqlite3_exception(rc, "Unable to reset dependency fetch statement");

		names.pop();
	}

	// Dispose of the statements.
	rc = sqlite3_finalize(fragStmt);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to finalize fragment fetch statement");

	rc = sqlite3_finalize(depsStmt);
	if (rc != SQLITE_OK)
		throw sqlite3_exception(rc, "Unable to finalize dependency fetch statement");

	// Resolve the frag pointer in each Dependency entry. This allows faster
	// operation of the subsequent algorithms. Also replace all placeholders in
	// the fragment's code.
	std::map<std::string,Fragment*>::iterator i, l;
	for (i = fragments.begin(); i != fragments.end(); i++) {
		i->second->after = false;
		for (std::vector<Dependency>::iterator k = i->second->deps.begin(); k != i->second->deps.end(); k++) {
			l = fragments.find(k->name);
			if (l == fragments.end())
				throw std::runtime_error("Unable to resolve dependency '" + k->name + "' of fragment '" + i->first + "'");
			k->frag = l->second;
			i->second->after = i->second->after || k->after;
		}

		// Replace placeholders.
		const std::string bL("%{"), bR("}");
		const std::string& before = i->second->code;
		std::string after;
		std::string::const_iterator current = before.begin(), end = before.end();
		std::string::const_iterator next = std::search(current, end, bL.begin(), bL.end());
		while (next != end) {
			after.append(current, next);
			std::string::const_iterator a,b;
			a = next + bL.size();
			next = std::search(next, end, bR.begin(), bR.end());
			b = next;
			current = next + bR.size();
			next = std::search(current, end, bL.begin(), bL.end());

			// Lookup the referenced fragment and insert its %ref member.
			std::string fn(a,b);
			l = fragments.find(fn);
			if (l == fragments.end())
				throw std::runtime_error("Fragment '" + i->first + "' has a placeholder referring to fragment %{" + fn + "} which does not exist");
			after.append(l->second->ref);
		}
		after.append(current, next);
		i->second->code = after;
	}
}
