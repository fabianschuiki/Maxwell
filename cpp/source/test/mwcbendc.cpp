/* Copyright © 2013-2014 Fabian Schuiki */
/** @file This program invokes the C backend on a node in the repository. */
#include <iostream>
#include <string>
#include <ast/Repository.hpp>
#include <backend/c/Repository.hpp>
#include <backend/c/CodeGenerator.hpp>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <fstream>

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
	try {
		Repository repo("mwcrepo");
		backendc::Repository bendrepo("mwcrepo");

		// Read the node IDs from the input.
		vector<NodeId> ids;
		for (int i = 1; i < argc; i++) {
			ids.push_back(NodeId(string(argv[i])));
		}

		// Process each of the nodes.
		map<NodeId, backendc::CodeGenerator::RootContext> contexts;
		backendc::CodeGenerator cg(repo, bendrepo);
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

	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		return 1;
	}
	return 0;
}