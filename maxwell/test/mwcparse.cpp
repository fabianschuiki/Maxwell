/* Copyright (c) 2013-2015 Fabian Schuiki */
#include "maxwell/ast/Repository.hpp"
#include "maxwell/console.hpp"
#include "maxwell/diagnostic/ConsoleDiagnosticPrinter.hpp"
#include "maxwell/diagnostic/diagnostic.hpp"
#include "maxwell/driver/Driver.hpp"
#include "maxwell/filesystem/disk/DiskDirectory.hpp"
#include "maxwell/filesystem/disk/DiskFile.hpp"
#include "maxwell/iterator.hpp"
#include "maxwell/range.hpp"
#include "maxwell/repository/file/FileSourceRepository.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

/// \file
/// This program parses a set of source files and loads them into the testing
/// repository.

using std::string;
using std::set;
using std::cout;
using std::cerr;
using driver::Driver;
using ast::Repository;
using namespace maxwell;
using namespace maxwell::filesystem;


int main(int argc, char *argv[]) {
	using std::placeholders::_1;

	console::init();

	try {
		Driver driver;
		Repository repo("mwcrepo");
		boost::filesystem::create_directory("mwcrepo/mwc");
		filesystem::DiskDirectory repoDir("mwcrepo/mwc/sources");
		repository::FileSourceRepository sourceRepo(repoDir);
		DiagnosticContext diagCtx;
		driver.setDiagnosticContext(&diagCtx);

		set<string> ids;
		for (int i = 1; i < argc; i++) {
			string arg(argv[i]);
			cerr << "Parsing " << arg << "... ";

			sourceRepo.add("../"+arg, DiskFile(arg));
			SourceId sid = sourceRepo.getSourceId("../"+arg);

			if (driver.parseFile(arg, SourceLocation(sid))) {
				cerr << "\033[32mdone\033[0m (" << driver.nodes.size() << " nodes)\n";
				repo.unregisterSource(arg);
				int source = repo.registerSource(arg);
				for (ast::NodeVector::iterator it = driver.nodes.begin(); it != driver.nodes.end(); it++) {
					repo.addNode(source, *it);
					ids.insert((*it)->getId().str());
				}
				driver.nodes.clear();
			} else {
				cerr << "\033[31;1mfailed\033[0m\n";
			}
		}
		for (set<string>::iterator it = ids.begin(); it != ids.end(); it++) {
			if (it != ids.begin())
				cout << ' ';
			cout << *it;
		}
		cout << '\n';

		ConsoleDiagnosticPrinter fmt(sourceRepo);
		for (auto const& d : diagCtx.getDiagnostics()) {
			fmt.consume(d);
		}

		if (diagCtx.isError())
			return 1;
	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		return 1;
	}

	return 0;
}
