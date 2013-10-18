/* Copyright © 2013 Fabian Schuiki */

/**
 * @file This program invokes the C backend on a node in the repository.
 */

#include <iostream>
#include <string>
#include <ast/Repository.hpp>
#include <backend/c/Repository.hpp>
#include <backend/c/CodeGenerator.hpp>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <set>

using std::string;
using std::cout;
using std::cerr;
using ast::Repository;
using ast::NodeId;
using ast::NodePtr;
using std::vector;
using std::set;

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
		backendc::CodeGenerator cg(repo, bendrepo);
		for (int i = 0; i < ids.size(); i++) {
			cout << "Generating code for \033[1m" << ids[i] << "\033[0m\n";
			cg.run(ids[i]);
		}
		
		// Gather the generated code per source file.
		set<int> sourceIds;
		for (int i = 0; i < ids.size(); i++) {
			sourceIds.insert(ids[i].source);
		}
		for (set<int>::iterator it = sourceIds.begin(); it != sourceIds.end(); it++) {
			cout << "Packaging \033[1m" << *it << "\033[0m\n";
		}

	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		return 1;
	}
	return 0;
}