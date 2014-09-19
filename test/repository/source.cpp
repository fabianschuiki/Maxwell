/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE repository_source
#include "maxwell/filesystem/mock.hpp"
#include "maxwell/repository/SourceIndex.hpp"
#include <boost/test/unit_test.hpp>
using namespace maxwell;
using maxwell::repository::SourceIndex;

BOOST_AUTO_TEST_CASE(repository_source_index) {
	MockFile file(".mwc/source/index", Buffer<const Byte>((const Byte*)"buggy stuff"));

	// Putting the following into a separate block causes the flush-on-destroy
	// of SourceIndex to trigger.
	{
		SourceIndex idx(file);
		BOOST_CHECK(idx.add("main.mw") == true);
		BOOST_CHECK(idx.add("main.mw") == false);
		BOOST_CHECK(idx.add("base64/encode.mw") == true);
		idx.flush();

		BOOST_CHECK(idx.remove("main.mw") == true);
		BOOST_CHECK(idx.remove("main.mw") == false);
		// idx.flush() called in destructor
	}

	auto stuff = file.getContent();
	std::cout << "file contains: " << std::string(stuff.getStart(), stuff.getEnd()) << '\n';
}
