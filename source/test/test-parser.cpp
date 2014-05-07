/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE parser
#include <driver/Driver.hpp>
#include <ast/Repository.hpp>
#include <boost/test/unit_test.hpp>

using ast::Repository;
using driver::Driver;

BOOST_AUTO_TEST_CASE(tuples)
{
	Repository repo("test-parser.repo");
	Driver driver;

	try {
		std::string input = "func main { (1,2,3); }";
		std::stringstream s(input);
		if (driver.parseStream(s)) {
			BOOST_REQUIRE(driver.nodes.size() == 1);
			const ast::NodePtr& node = driver.nodes.front();
			
			BOOST_CHECK_EQUAL(node->getClassName(), "FuncDef");
		} else {
			BOOST_ERROR("Failed to parse '" + input + "'");
		}
	} catch (std::exception& e) {
		BOOST_ERROR(e.what());
	}
}
