/* Copyright (c) 2013-2014 Fabian Schuiki */
/** @file This program parses a set of source files and loads them into the
 * testing repository. */

#include "maxwell/ast/Repository.hpp"
#include "maxwell/driver/Driver.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

using std::string;
using std::set;
using std::cout;
using std::cerr;
using driver::Driver;
using ast::Repository;
using namespace maxwell;

int main(int argc, char *argv[])
{
	try {
		Driver driver;
		Repository repo("mwcrepo");

		set<string> ids;
		for (int i = 1; i < argc; i++) {
			string arg(argv[i]);
			cout << "Parsing " << arg << "... ";
			if (driver.parseFile(arg, SourceLocation())) {
				cout << "\033[32mdone\033[0m (" << driver.nodes.size() << " nodes)\n";
				repo.unregisterSource(arg);
				int source = repo.registerSource(arg);
				for (ast::NodeVector::iterator it = driver.nodes.begin(); it != driver.nodes.end(); it++) {
					repo.addNode(source, *it);
					ids.insert((*it)->getId().str());
				}
				driver.nodes.clear();
			} else {
				cout << "\033[31;1mfailed\033[0m\n";
			}
		}
		for (set<string>::iterator it = ids.begin(); it != ids.end(); it++) {
			if (it != ids.begin())
				cout << ' ';
			cout << *it;
		}
		cout << '\n';
	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		return 1;
	}
	return 0;
}
