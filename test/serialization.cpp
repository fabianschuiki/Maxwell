/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE serialization
#include "maxwell/serialization/ArrayDecoder.hpp"
#include "maxwell/serialization/interfaces.hpp"
#include "maxwell/serialization/VectorEncoder.hpp"
#include <boost/test/unit_test.hpp>
using namespace maxwell::serialization;

BOOST_AUTO_TEST_CASE(endianness_unsigned) {
	std::vector<Byte> data;
	data.reserve(128);

	// Encode a few integers.
	VectorEncoder venc(data);
	Encoder& enc = venc;

	uint8_t a = 0xab;
	uint16_t b = 0xabcd;
	uint32_t c = 0xabcdef01;
	uint64_t d = 0xabcdef0123456789;
	enc(a)(b)(c)(d);

	BOOST_CHECK_EQUAL(data.size(), 15);

	// Make sure the result is big endian (wire format).
	BOOST_CHECK_EQUAL(data[0],  0xab);

	BOOST_CHECK_EQUAL(data[1],  0xab);
	BOOST_CHECK_EQUAL(data[2],  0xcd);

	BOOST_CHECK_EQUAL(data[3],  0xab);
	BOOST_CHECK_EQUAL(data[4],  0xcd);
	BOOST_CHECK_EQUAL(data[5],  0xef);
	BOOST_CHECK_EQUAL(data[6],  0x01);

	BOOST_CHECK_EQUAL(data[7],  0xab);
	BOOST_CHECK_EQUAL(data[8],  0xcd);
	BOOST_CHECK_EQUAL(data[9],  0xef);
	BOOST_CHECK_EQUAL(data[10], 0x01);
	BOOST_CHECK_EQUAL(data[11], 0x23);
	BOOST_CHECK_EQUAL(data[12], 0x45);
	BOOST_CHECK_EQUAL(data[13], 0x67);
	BOOST_CHECK_EQUAL(data[14], 0x89);

	// Decode the integers back.
	ArrayDecoder adec(&data[0], data.size());
	Decoder& dec = adec;

	dec(a)(b)(c)(d);

	// Make sure the result is native host byte order.
	BOOST_CHECK_EQUAL(a, (uint8_t)0xab);
	BOOST_CHECK_EQUAL(b, (uint16_t)0xabcd);
	BOOST_CHECK_EQUAL(c, (uint32_t)0xabcdef01);
	BOOST_CHECK_EQUAL(d, (uint64_t)0xabcdef0123456789);
}

BOOST_AUTO_TEST_CASE(endianness_signed) {
	std::vector<Byte> data;
	data.reserve(128);

	// Encode a few integers.
	VectorEncoder venc(data);
	Encoder& enc = venc;

	int8_t a = 0xab;
	int16_t b = 0xabcd;
	int32_t c = 0xabcdef01;
	int64_t d = 0xabcdef0123456789;
	enc(a)(b)(c)(d);

	BOOST_CHECK_EQUAL(data.size(), 15);

	// Make sure the result is big endian (wire format).
	BOOST_CHECK_EQUAL(data[0],  0xab);

	BOOST_CHECK_EQUAL(data[1],  0xab);
	BOOST_CHECK_EQUAL(data[2],  0xcd);

	BOOST_CHECK_EQUAL(data[3],  0xab);
	BOOST_CHECK_EQUAL(data[4],  0xcd);
	BOOST_CHECK_EQUAL(data[5],  0xef);
	BOOST_CHECK_EQUAL(data[6],  0x01);

	BOOST_CHECK_EQUAL(data[7],  0xab);
	BOOST_CHECK_EQUAL(data[8],  0xcd);
	BOOST_CHECK_EQUAL(data[9],  0xef);
	BOOST_CHECK_EQUAL(data[10], 0x01);
	BOOST_CHECK_EQUAL(data[11], 0x23);
	BOOST_CHECK_EQUAL(data[12], 0x45);
	BOOST_CHECK_EQUAL(data[13], 0x67);
	BOOST_CHECK_EQUAL(data[14], 0x89);

	// Decode the integers back.
	ArrayDecoder adec(&data[0], data.size());
	Decoder& dec = adec;

	dec(a)(b)(c)(d);

	// Make sure the result is native host byte order.
	BOOST_CHECK_EQUAL(a, (int8_t)0xab);
	BOOST_CHECK_EQUAL(b, (int16_t)0xabcd);
	BOOST_CHECK_EQUAL(c, (int32_t)0xabcdef01);
	BOOST_CHECK_EQUAL(d, (int64_t)0xabcdef0123456789);
}

BOOST_AUTO_TEST_CASE(strings) {
	std::vector<Byte> data;
	data.reserve(128);

	// Encode a string.
	VectorEncoder venc(data);
	Encoder& enc = venc;

	std::string original = "Hello World";
	enc(original);

	BOOST_CHECK_EQUAL(data.size(), 11+4);

	// Decode the string back.
	ArrayDecoder adec(&data[0], data.size());
	Decoder& dec = adec;

	std::string reversed;
	dec(reversed);

	BOOST_CHECK_EQUAL(original, reversed);
}
