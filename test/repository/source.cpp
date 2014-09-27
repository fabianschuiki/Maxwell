/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE repository_source_module
#include "maxwell/filesystem/MockDirectory.hpp"
#include "maxwell/filesystem/MockFile.hpp"
#include "maxwell/filesystem/Path.hpp"
#include "maxwell/repository/FileSourceRepository.hpp"
#include <boost/test/unit_test.hpp>
#include <fstream>

using maxwell::filesystem::MockDirectory;
using maxwell::filesystem::MockFile;
using maxwell::filesystem::Path;
using maxwell::repository::FileSourceRepository;
using maxwell::repository::SourceRepository;
using maxwell::SourceId;

BOOST_AUTO_TEST_CASE(repository_source) {
	MockDirectory dir(".mwc/source");
	SourceId sida, sidb;

	// Simulate a first program execution.
	{
		FileSourceRepository concrete(dir);
		SourceRepository &repo = concrete;

		// Add mock files to the repository.
		MockFile srca("src/main.mw");
		MockFile srcb("src/funcs.mw");
		BOOST_CHECK(repo.add("main.mw", srca));
		BOOST_CHECK(repo.add("funcs.mw", srcb));
		BOOST_CHECK(!repo.add("main.mw", srca));
		BOOST_CHECK(!repo.add("funcs.mw", srcb));

		// Get the source IDs.
		sida = repo.getSourceId("main.mw");
		sidb = repo.getSourceId("funcs.mw");
		BOOST_CHECK(sida.isValid());
		BOOST_CHECK(sidb.isValid());
		BOOST_CHECK(repo.getSourceId("inexistent.mw").isInvalid());
		BOOST_CHECK_EQUAL(repo.getPath(sida), Path("main.mw"));
		BOOST_CHECK_EQUAL(repo.getPath(sidb), Path("funcs.mw"));
		BOOST_CHECK_EQUAL(repo.getPath(SourceId()), Path());
	}

	std::cout << dir.getPath() << " contains:\n";
	for (auto& pair : dir.files) {
		std::cout << "  " << pair.first << " (" << pair.second.content.size() << " bytes)\n";
	}

	// std::ofstream fout("testindex");
	// const auto& index = dir.files.find("index")->second.content;
	// fout.write((const char*)&index[0], index.size());
	// fout.close();

	// Simulate a second program execution.
	{
		FileSourceRepository concrete(dir);
		SourceRepository &repo = concrete;

		// Make sure the files were loaded again.
		BOOST_CHECK(repo.getSourceId("main.mw"));
		BOOST_CHECK(repo.getSourceId("funcs.mw"));

		// Update one of the files with new mock content.
		MockFile srcc("src/main.mw"); srcc.content.push_back(3);
		BOOST_CHECK(repo.add("main.mw", srcc));
		BOOST_CHECK(!repo.add("main.mw", srcc));

		// Remove the mock files from the repository again.
		BOOST_CHECK(repo.remove("main.mw"));
		BOOST_CHECK(!repo.remove("main.mw"));
		BOOST_CHECK(repo.remove(sidb));
		BOOST_CHECK(!repo.remove(sidb));
	}

	std::cout << dir.getPath() << " contains:\n";
	for (auto& pair : dir.files) {
		std::cout << "  " << pair.first << " (" << pair.second.content.size() << " bytes)\n";
	}

	// MockFile file(".mwc/source/index", Buffer<const Byte>((const Byte*)"buggy stuff"));

	// // Putting the following into a separate block causes the flush-on-destroy
	// // of SourceIndex to trigger.
	// {
	// 	SourceIndex idx(file);
	// 	BOOST_CHECK(idx.add("main.mw") == true);
	// 	BOOST_CHECK(idx.add("main.mw") == false);
	// 	BOOST_CHECK(idx.add("base64/encode.mw") == true);
	// 	idx.flush();

	// 	BOOST_CHECK(idx.remove("main.mw") == true);
	// 	BOOST_CHECK(idx.remove("main.mw") == false);
	// 	// idx.flush() called in destructor
	// }

	// const auto& index = dir.files.find("index")->second.content;
	// std::cout << "file contains: " << std::string(index.begin(), index.end()) << '\n';
}
