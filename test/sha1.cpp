/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE sha1_module
#include "maxwell/sha1.hpp"
#include <boost/test/unit_test.hpp>
using maxwell::sha1;

BOOST_AUTO_TEST_CASE(sha1_case) {
	// FIPS 180-2 C.1 and RFC3174 7.3 TEST1
	BOOST_CHECK_EQUAL(sha1().update("abc").finalize().lhex(), "a9993e364706816aba3e25717850c26c9cd0d89d");

	// FIPS 180-2 C.2 and RFC3174 7.3 TEST2
	BOOST_CHECK_EQUAL(sha1().update("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq").finalize().lhex(), "84983e441c3bd26ebaae4aa1f95129e5e54670f1");

	// RFC3174 7.3 TEST4
	sha1 t4;
	for (unsigned i = 0; i < 80; i++)
		t4.update("01234567");
	BOOST_CHECK_EQUAL(t4.finalize().lhex(), "dea356a2cddd90c7a7ecedc5ebb563934f460452");
}
