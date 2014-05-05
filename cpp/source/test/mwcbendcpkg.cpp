/* Copyright (c) 2014 Fabian Schuiki */

/** @file This program invokes the packager of the C backend on a backend data-
 * base and set of nodes. */

#include <sqlite3.h>
#include <backend/c/database.hpp>
#include <backend/c/Packager.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace backendc;


int main(int argc, char *argv[])
{
	sqlite3* db = NULL;
	try {
		int rc;

		// Lookup the name of the main fragment from the arguments the user
		// passed to the program.
		if (argc < 2) {
			std::cerr << "usage: " << argv[0] << " FRAGMENT-NAME\n";
			return 2;
		}
		std::string name = argv[1];

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
		pkg.run(name);

		// Close the database.
		sqlite3_close(db);

		// Dump the generated files.
		for (std::map<std::string,std::string>::iterator i = pkg.files.begin(); i != pkg.files.end(); i++) {
			std::ofstream f(i->first.c_str());
			f << i->second;
		}

	} catch (std::exception &e) {
		std::cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		if (db) sqlite3_close(db);
		return 1;
	}
	return 0;
}