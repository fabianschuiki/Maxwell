/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE location
#include "maxwell/location.hpp"
#include <boost/test/unit_test.hpp>
using namespace maxwell;

BOOST_AUTO_TEST_CASE(location_sid) {
	SourceId sida;
	SourceId sidb(1);

	BOOST_CHECK_EQUAL(sida.isInvalid(), true);
	BOOST_CHECK_EQUAL(sida.isValid(), false);
	BOOST_CHECK_EQUAL((bool)sida, false);

	BOOST_CHECK_EQUAL(sidb.isInvalid(), false);
	BOOST_CHECK_EQUAL(sidb.isValid(), true);
	BOOST_CHECK_EQUAL((bool)sidb, true);

	BOOST_CHECK(sida == sida);
	BOOST_CHECK(sida != sidb);
	BOOST_CHECK(sida <= sidb); BOOST_CHECK(sidb <= sidb);
	BOOST_CHECK(sidb >= sida); BOOST_CHECK(sidb >= sidb);
	BOOST_CHECK(sida < sidb);
	BOOST_CHECK(sidb > sida);

	BOOST_CHECK_EQUAL(sida.getId(), 0);
	BOOST_CHECK_EQUAL(sidb.getId(), 1);
}

BOOST_AUTO_TEST_CASE(location_loc) {
	SourceId sid(1);
	SourceLocation loca;
	SourceLocation locb(sid);
	SourceLocation locc(sid, 10);

	BOOST_CHECK_EQUAL(loca.isInvalid(), true);
	BOOST_CHECK_EQUAL(loca.isValid(), false);
	BOOST_CHECK_EQUAL((bool)loca, false);

	BOOST_CHECK_EQUAL(locb.isInvalid(), false);
	BOOST_CHECK_EQUAL(locb.isValid(), true);
	BOOST_CHECK_EQUAL((bool)locb, true);

	BOOST_CHECK_EQUAL((locb+10).getOffset(), 10);
	BOOST_CHECK_EQUAL((locc-10).getOffset(),  0);
	locb += 5;
	locc -= 5;
	BOOST_CHECK(locb == locc);
	BOOST_CHECK(loca != locb);
	BOOST_CHECK(loca <= locb); BOOST_CHECK(loca <= loca);
	BOOST_CHECK(locb >= loca); BOOST_CHECK(loca >= loca);
	BOOST_CHECK(loca < locb);
	BOOST_CHECK(locb > loca);
	BOOST_CHECK_EQUAL(locb.getSourceId(), sid);
}

BOOST_AUTO_TEST_CASE(location_range) {
	SourceId sid(1);
	SourceLocation loca(sid, 10);
	SourceLocation locb(sid, 20);
	SourceRange rnga;
	SourceRange rngb(sid, 5, 10);
	SourceRange rngc(loca, locb);

	BOOST_CHECK_EQUAL(rnga.isInvalid(), true);
	BOOST_CHECK_EQUAL(rnga.isValid(), false);
	BOOST_CHECK_EQUAL((bool)rnga, false);

	BOOST_CHECK_EQUAL(rngb.isInvalid(), false);
	BOOST_CHECK_EQUAL(rngb.isValid(), true);
	BOOST_CHECK_EQUAL((bool)rngb, true);

	BOOST_CHECK_EQUAL(rngb == rnga, false);
	BOOST_CHECK_EQUAL(rngb != rnga, true);

	BOOST_CHECK_EQUAL(rngb.getSourceId(), sid);
	BOOST_CHECK_EQUAL(rngc.getOffset(), 10);
	BOOST_CHECK_EQUAL(rngc.getLength(), 10);
	BOOST_CHECK_EQUAL(rngc.getBegin(), loca);
	BOOST_CHECK_EQUAL(rngc.getEnd(), locb);

	BOOST_CHECK(rngb.contains(loca));
	BOOST_CHECK(!rngb.contains(locb));
	BOOST_CHECK(!rngb.contains(rngc));
	BOOST_CHECK(!rngb.contains(4));
	BOOST_CHECK(rngb.contains(5));
	BOOST_CHECK(!rngb.contains(15));
	BOOST_CHECK(rngb.touches(rngc));
	BOOST_CHECK(rngb.intersects(rngc));
}
