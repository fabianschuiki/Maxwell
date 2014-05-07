/* Copyright © 2013-2014 Fabian Schuiki */
/** @file This program invokes the C backend on a list of nodes in the
 * repository. */
#include <ast/Repository.hpp>
#include <backend/c/CodeGen2.hpp>
#include <backend/c/database.hpp>
#include <sqlite3.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

using ast::NodeId;
using namespace backendc;

int main(int argc, char *argv[])
{
	sqlite3* db = NULL;
	try {
		ast::Repository repo("mwcrepo");

		// Open the database.
		int rc = sqlite3_open("mwcrepo/bendc.db", &db);
		if (rc) {
			std::stringstream s;
			s << "Can't open database: %s" << sqlite3_errmsg(db);
			throw std::runtime_error(s.str());
		}
		sqlite3_exec(db, "PRAGMA foreign_keys = ON", NULL, NULL, NULL);

		// Make sure the database has the right schema.
		database(db).prepareFragmentsSchema();

		// Read the node IDs from the input.
		std::vector<NodeId> ids;
		for (int i = 1; i < argc; i++) {
			ids.push_back(NodeId(std::string(argv[i])));
		}

		// Run the code generator for the given node IDs. Then output the list
		// files that were generated.
		CodeGen2 cg2(repo, db);
		cg2.run(ids.begin(), ids.end());

		for (std::map<NodeId,std::string>::const_iterator i = cg2.names.begin(); i != cg2.names.end(); i++)
			std::cout << i->second << '\n';

		// Close the database.
		sqlite3_close(db);

	} catch (std::exception &e) {
		std::cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		if (db) sqlite3_close(db);
		return 1;
	}
	return 0;
}