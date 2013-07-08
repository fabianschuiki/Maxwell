/* Copyright © 2013 Fabian Schuiki */

/**
 * @file This program parses a set of source files and loads them into the
 * testing repository.
 */

#include <iostream>
#include <string>
#include <driver/Driver.hpp>
#include <ast/Repository.hpp>
#include <stdexcept>

using std::string;
using std::cout;
using std::cerr;
using driver::Driver;
using ast::Repository;

int main(int argc, char *argv[])
{
	try {
		Driver driver;
		Repository repo("mwcrepo");

		for (int i = 1; i < argc; i++) {
			string arg(argv[i]);
			cout << "Parsing " << arg << "... ";
			if (driver.parseFile(arg)) {
				cout << "\033[32mdone\033[0m (" << driver.nodes.size() << " nodes)\n";
				repo.unregisterSource(arg);
				int source = repo.registerSource(arg);
				for (ast::NodeVector::iterator it = driver.nodes.begin(); it != driver.nodes.end(); it++) {
					repo.addNode(source, *it);
				}
				driver.nodes.clear();
			} else {
				cout << "\033[31;1mfailed\033[0m\n";
			}
		}
	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		return 1;
	}
	return 0;
}