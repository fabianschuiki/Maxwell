/* Copyright © 2013-2014 Fabian Schuiki */
/** @file This program invokes the C backend on a node in the repository. */
#include <iostream>
#include <string>
#include <ast/Repository.hpp>
#include <backend/c/Repository.hpp>
#include <backend/c/CodeGenerator.hpp>
#include <backend/c/CodeGen2.hpp>
#include <backend/c/database.hpp>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <sqlite3.hpp>

using std::string;
using std::cout;
using std::cerr;
using ast::Repository;
using ast::NodeId;
using ast::NodePtr;
using std::vector;
using std::set;
using std::map;

int main(int argc, char *argv[])
{
	sqlite3* db = NULL;
	try {
		Repository repo("mwcrepo");
		backendc::Repository bendrepo("mwcrepo");

		// Open the database.
		int rc = sqlite3_open("mwcrepo/bendc.db", &db);
		if (rc) {
			std::stringstream s;
			s << "Can't open database: %s" << sqlite3_errmsg(db);
			throw std::runtime_error(s.str());
		}
		sqlite3_exec(db, "PRAGMA foreign_keys = ON", NULL, NULL, NULL);

		// Make sure the database has the right schema.
		backendc::database(db).prepareFragmentsSchema();

		// Read the node IDs from the input.
		vector<NodeId> ids;
		for (int i = 1; i < argc; i++) {
			ids.push_back(NodeId(string(argv[i])));
		}

		// Run stuff through the fancy new CodeGen2.
		cout << "Running CodeGen2\n";
		backendc::CodeGen2 cg2(repo, db);
		cg2.run(ids.begin(), ids.end());

		for (std::map<NodeId,std::string>::const_iterator i = cg2.names.begin(); i != cg2.names.end(); i++)
			std::cout << i->second << '\n';

		// Process each of the nodes.
		map<NodeId, backendc::CodeGenerator::RootContext> contexts;
		backendc::CodeGenerator cg(repo, bendrepo, db);
		for (int i = 0; i < ids.size(); i++) {
			cout << "Generating code for \033[1m" << ids[i] << "\033[0m\n";
			cg.run(ids[i], contexts[ids[i]]);
		}

		// Gather the generated code per source file.
		set<int> sourceIds;
		for (int i = 0; i < ids.size(); i++) {
			sourceIds.insert(ids[i].source);
		}
		for (set<int>::iterator it = sourceIds.begin(); it != sourceIds.end(); it++) {
			string name = repo.getSourceName(*it);
			cout << "Packaging \033[1m" << *it << "\033[0m (" << name << ")\n";

			backendc::CodeGenerator::RootContext context;
			for (map<NodeId, backendc::CodeGenerator::RootContext>::iterator iu = contexts.begin(); iu != contexts.end(); iu++) {
				context.decls.insert(iu->second.decls.begin(), iu->second.decls.end());
				context.defs.insert(iu->second.defs.begin(), iu->second.defs.end());
			}

			size_t colonpos = name.find_last_of('.');
			if (colonpos != string::npos)
				name = name.substr(0, colonpos);
			string name_h = name + ".h";
			string name_c = name + ".c";
			backendc::CodeGenerator::RootContext::Stmts::const_iterator iu;
			std::ofstream h(name_h.c_str());
			std::ofstream c(name_c.c_str());
			h << "#pragma once\n\n";
			for (iu = context.decls.begin(); iu != context.decls.end(); iu++) {
				h << (*iu).code << '\n';
			}
			c << "#include \"" << name_h << "\"\n";
			for (iu = context.defs.begin(); iu != context.defs.end(); iu++) {
				c << '\n' << (*iu).code << '\n';
			}
		}

		// Close the database.
		sqlite3_close(db);

	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		if (db) sqlite3_close(db);
		return 1;
	}
	return 0;
}