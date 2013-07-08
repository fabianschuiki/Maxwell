/* Copyright © 2013 Fabian Schuiki */

/**
 * @file This program prints the description of a node in the repository.
 */

#include <iostream>
#include <string>
#include <ast/Repository.hpp>
#include <stdexcept>
#include <cstdlib>

using std::string;
using std::cout;
using std::cerr;
using ast::Repository;
using ast::NodeId;
using ast::NodePtr;

int main(int argc, char *argv[])
{
	try {
		Repository repo("mwcrepo");
		for (int i = 1; i < argc; i++) {
			string idstr(argv[i]);
			size_t slashpos = idstr.find_last_of("/");
			int depth = -1;
			if (slashpos != string::npos) {
				depth = atoi(idstr.substr(slashpos+1).c_str());
				idstr = idstr.substr(0, slashpos);
			}
			NodeId id(idstr);
			NodePtr node = repo.getNode(id);
			cout << "Node \033[1m" << id << "\033[0m = " << node->describe(depth) << "\n";
		}

	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		return 1;
	}
	return 0;
}