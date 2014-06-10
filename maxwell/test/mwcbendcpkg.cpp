/* Copyright (c) 2014 Fabian Schuiki */

/** @file This program invokes the packager of the C backend on a backend data-
 * base and set of nodes. */

#include "maxwell/backend/c/database.hpp"
#include "maxwell/backend/c/Packager.hpp"
#include <fstream>
#include <iostream>
#include "maxwell/sqlite3.hpp"
#include <sstream>
#include <stdexcept>
#include <string>

using namespace backendc;


int main(int argc, char *argv[])
{
	sqlite3* db = NULL;
	try {
		int rc;

		// Collect the requested fragment names.
		std::vector<std::string> names;
		names.reserve(argc-1);
		for (int i = 1; i < argc; i++)
			names.push_back(argv[i]);

		// Open the database.
		rc = sqlite3_open("mwcrepo/bendc.db", &db);
		if (rc) {
			std::stringstream s;
			s << "Can't open database: %s" << sqlite3_errmsg(db);
			throw std::runtime_error(s.str());
		}
		sqlite3_exec(db, "PRAGMA foreign_keys = ON", NULL, NULL, NULL);

		// Make sure the database has the right schema.
		database(db).prepareFragmentsSchema();

		// Call the packager on the database.
		Packager pkg(db);
		pkg.run(names.begin(), names.end());

		// Close the database.
		sqlite3_close(db);

		// Dump the generated files.
		for (std::map<std::string,std::string>::iterator i = pkg.files.begin(); i != pkg.files.end(); i++) {
			std::ofstream f(i->first.c_str());
			f << i->second;
			std::cout << i->first << '\n';
		}

	} catch (std::exception &e) {
		std::cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		if (db) sqlite3_close(db);
		return 1;
	}
	return 0;
}
