/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE sha1_module
#include "maxwell/sha1.hpp"
#include <boost/test/unit_test.hpp>
using maxwell::sha1;
using maxwell::sha1hash;

BOOST_AUTO_TEST_CASE(sha1_case) {
	// FIPS 180-2 C.1 and RFC3174 7.3 TEST1
	auto t1 = sha1().update("abc").finalize();
	BOOST_CHECK_EQUAL(t1.lhex(), "a9993e364706816aba3e25717850c26c9cd0d89d");
	BOOST_CHECK_EQUAL(t1.uhex(), "A9993E364706816ABA3E25717850C26C9CD0D89D");

	sha1hash t1b, t1c;
	BOOST_CHECK(!sha1hash::fromhex("axxxxe364706816aba3e25717850c26c9cd0d89d", t1b));
	BOOST_CHECK(!sha1hash::fromhex("whadup", t1b));
	BOOST_CHECK(sha1hash::fromhex("a9993e364706816aba3e25717850c26c9cd0d89d", t1b));
	BOOST_CHECK(sha1hash::fromhex("A9993E364706816ABA3E25717850C26C9CD0D89D", t1c));
	BOOST_CHECK_EQUAL(t1b, t1c);
	BOOST_CHECK_EQUAL(t1, t1b);
	BOOST_CHECK_EQUAL(t1, t1c);

	// FIPS 180-2 C.2 and RFC3174 7.3 TEST2
	auto t2 = sha1().update("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq").finalize();
	BOOST_CHECK_EQUAL(t2.lhex(), "84983e441c3bd26ebaae4aa1f95129e5e54670f1");
	BOOST_CHECK_EQUAL(t2.uhex(), "84983E441C3BD26EBAAE4AA1F95129E5E54670F1");

	// RFC3174 7.3 TEST4
	sha1 a4;
	for (unsigned i = 0; i < 80; i++)
		a4.update("01234567");
	auto t4 = a4.finalize();
	BOOST_CHECK_EQUAL(t4.lhex(), "dea356a2cddd90c7a7ecedc5ebb563934f460452");
	BOOST_CHECK_EQUAL(t4.uhex(), "DEA356A2CDDD90C7A7ECEDC5EBB563934F460452");

	// Long update.
	const char* c5 =
		"abcefghijklmnopqrstuvwxyzABCEFGHIJKLMNOPQRSTUVWXYZ"
		"abcefghijklmnopqrstuvwxyzABCEFGHIJKLMNOPQRSTUVWXYZ"
		"abcefghijklmnopqrstuvwxyzABCEFGHIJKLMNOPQRSTUVWXYZ"
		"abcefghijklmnopqrstuvwxyzABCEFGHIJKLMNOPQRSTUVWXYZ";
	auto t5 = sha1().update(c5).finalize();
	BOOST_CHECK_EQUAL(t5.lhex(), "6da7df1af35624ade5dfd2b63a2307d5f283bee4");
	BOOST_CHECK_EQUAL(t5.uhex(), "6DA7DF1AF35624ADE5DFD2B63A2307D5F283BEE4");
}
