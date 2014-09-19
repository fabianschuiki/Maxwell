/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE repository_source
#include "maxwell/filesystem/mock.hpp"
#include "maxwell/repository/SourceIndex.hpp"
#include <boost/test/unit_test.hpp>
using namespace maxwell;
using maxwell::repository::SourceIndex;

BOOST_AUTO_TEST_CASE(repository_source_index) {
	MockFile file(".mwc/source/index");
	SourceIndex idx(file);
	idx.add("main.mw");
	idx.add("base64/encode.mw");
}
