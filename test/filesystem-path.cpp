/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE filesystem_path_module
#include "maxwell/filesystem/Path.hpp"
#include <boost/test/unit_test.hpp>
using namespace maxwell::filesystem;

BOOST_AUTO_TEST_CASE(relative_path) {
	BOOST_CHECK_EQUAL(relativePath("/home/src/one", "/home/src"), "one");
	BOOST_CHECK_EQUAL(relativePath("/home/src/one", "/home/two"), "../src/one");
	BOOST_CHECK_EQUAL(relativePath("/home/src", "/work/dst"), "../../home/src");
	BOOST_CHECK_EQUAL(relativePath("/home/src", "/"), "home/src");
	BOOST_CHECK_EQUAL(relativePath("/", "/home/src"), "../../");
}

BOOST_AUTO_TEST_CASE(normalize_path) {
	BOOST_CHECK_EQUAL(normalizePath("/home/src/./one"), "/home/src/one");
	BOOST_CHECK_EQUAL(normalizePath("/home/src/./one/"), "/home/src/one");
	BOOST_CHECK_EQUAL(normalizePath("/home/src//one/"), "/home/src/one");
	BOOST_CHECK_EQUAL(normalizePath("/home/../work/one"), "/work/one");
	BOOST_CHECK_EQUAL(normalizePath("/home/../work/one/"), "/work/one");
	BOOST_CHECK_EQUAL(normalizePath("/home/../../work/one"), "../work/one");
	BOOST_CHECK_EQUAL(normalizePath("/home/../../work/one/"), "../work/one");
	BOOST_CHECK_EQUAL(normalizePath("/home/../work/../../test"), "../test");
	BOOST_CHECK_EQUAL(normalizePath("/home/../work/../../test/"), "../test");
	BOOST_CHECK_EQUAL(normalizePath("../home/../../work"), "../../work");
	BOOST_CHECK_EQUAL(normalizePath("../home/../../work/"), "../../work");
	BOOST_CHECK_EQUAL(normalizePath("../home/..//../work/"), "../../work");
}
