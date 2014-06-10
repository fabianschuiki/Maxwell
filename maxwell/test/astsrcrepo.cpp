/* Copyright (c) 2013 Fabian Schuiki */

/**
 * @file This program serves as a testing facility for the ast::Repository
 * classes.
 */

#include <iostream>
#include "maxwell/ast/SourceRepository.hpp"

using std::cout;

int main(int argc, char *argv[])
{
	ast::SourceRepository repo("./srcrepo");

	// List the files already in there.
	const ast::SourceRepository::SourcesById& sources = repo.getSourcesById();
	cout << "Repository contains " << sources.size() << " sources:\n";
	for (ast::SourceRepository::SourcesById::const_iterator it = sources.begin(); it != sources.end(); it++) {
		cout << "  #" << it->first << "  " << it->second << "\n";
	}

	// Add a resource.
	for (int i = 1; i < argc; i++) {
		cout << "Adding source " << argv[i] << "... ";
		int id = repo.registerSource(argv[i]);
		cout << id << "\n";
	}

	return 0;
}
