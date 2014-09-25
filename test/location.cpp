/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE location
#include "maxwell/location.hpp"
#include <boost/test/unit_test.hpp>
using namespace maxwell;

BOOST_AUTO_TEST_CASE(location_basic) {
	SourceId sida;
	SourceId sidb(1);

	BOOST_CHECK_EQUAL(sida.isInvalid(), true);
	BOOST_CHECK_EQUAL(sida.isValid(), false);
	BOOST_CHECK_EQUAL((bool)sida, false);

	BOOST_CHECK_EQUAL(sidb.isInvalid(), false);
	BOOST_CHECK_EQUAL(sidb.isValid(), true);
	BOOST_CHECK_EQUAL((bool)sidb, true);
}
