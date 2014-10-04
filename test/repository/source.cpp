/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE repository_source_module
#include "maxwell/filesystem/mock/MockDirectory.hpp"
#include "maxwell/filesystem/mock/MockFile.hpp"
#include "maxwell/filesystem/Path.hpp"
#include "maxwell/repository/file/FileSourceRepository.hpp"
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <set>

using maxwell::filesystem::MockDirectory;
using maxwell::filesystem::MockFile;
using maxwell::filesystem::Path;
using maxwell::repository::FileSourceRepository;
using maxwell::repository::Source;
using maxwell::repository::SourceRepository;
using maxwell::sha1;
using maxwell::SourceId;

BOOST_AUTO_TEST_CASE(repository_source) {
	MockDirectory dir(".mwc/source");
	SourceId sida, sidb;

	// Simulate a first program execution.
	{
		FileSourceRepository concrete(dir);
		SourceRepository &repo = concrete;

		// Add mock files to the repository.
		MockFile srca("src/main.mw", 123);
		MockFile srcb("src/funcs.mw", 123);
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

		// Access the sources.
		Source *srcap, *srcbp;
		BOOST_CHECK(srcap = repo.getSource(sida));
		BOOST_CHECK(srcbp = repo.getSource("funcs.mw"));
		BOOST_CHECK(repo.getSource("inexistent.mw") == nullptr);
	}

	// Verify that the directory contains the appropriate files.
	{
		dir.cleanup();
		auto files = dir.files;
		BOOST_CHECK(files.erase("index"));
		BOOST_CHECK(files.erase(sha1("main.mw").finalize().lhex()));
		BOOST_CHECK(files.erase(sha1("funcs.mw").finalize().lhex()));
		BOOST_CHECK(files.empty());
	}

	// Simulate a second program execution.
	{
		FileSourceRepository concrete(dir);
		SourceRepository &repo = concrete;

		// Make sure the files were loaded again.
		BOOST_CHECK(repo.getSourceId("main.mw"));
		BOOST_CHECK(repo.getSourceId("funcs.mw"));

		// Iterate over the sources using a lambda function.
		std::set<Path> paths;
		repo.eachSource([&](const Source& src){
			paths.insert(src.getPath());
		});
		BOOST_CHECK(paths.erase("main.mw"));
		BOOST_CHECK(paths.erase("funcs.mw"));
		BOOST_CHECK(paths.empty());

		// Change one of the file's timestamps.
		MockFile srcc("src/main.mw", 345);
		BOOST_CHECK(!repo.add("main.mw", srcc));
		BOOST_CHECK(!repo.isModified("main.mw", srcc));

		// Change one of the file's contents.
		srcc.content.push_back(3);
		BOOST_CHECK(repo.isModified(repo.getSourceId("main.mw"), srcc));
		BOOST_CHECK(repo.add("main.mw", srcc));
		BOOST_CHECK(!repo.add("main.mw", srcc));

		// Remove the mock files from the repository again.
		BOOST_CHECK(repo.remove("main.mw"));
		BOOST_CHECK(!repo.remove("main.mw"));
		BOOST_CHECK(repo.remove(sidb));
		BOOST_CHECK(!repo.remove(sidb));
	}

	// Verify that all source files were removed, and only the index is left.
	{
		dir.cleanup();
		auto files = dir.files;
		BOOST_CHECK(files.erase("index"));
		BOOST_CHECK(files.empty());
	}

	// Simulate a third program execution.
	{
		FileSourceRepository concrete(dir);
		SourceRepository &repo = concrete;

		// Add mock files to the repository.
		MockFile srca("src/main.mw", 123);
		MockFile srcb("src/funcs.mw", 123);
		BOOST_CHECK(repo.add("main.mw", srca));
		BOOST_CHECK(repo.add("funcs.mw", srcb));

		// Remove all sources.
		repo.removeAll();

		// Verify that inexistent files always show up as modified.
		BOOST_CHECK(repo.isModified(SourceId(123), srca));
		BOOST_CHECK(repo.isModified("dummy", srcb));
	}

	// Verify that all source files were removed, and only the index is left.
	{
		dir.cleanup();
		auto files = dir.files;
		BOOST_CHECK(files.erase("index"));
		BOOST_CHECK(files.empty());
	}
}
