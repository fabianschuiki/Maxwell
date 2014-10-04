/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/sha1.hpp"
#include <cassert>
#include <iostream>
using namespace maxwell;

const static char* lhex_table = "0123456789abcdef";
const static char* uhex_table = "0123456789ABCDEF";


static void hex(char *dst, const Byte* digest, const char* table) {
	for (const Byte* d = digest; d != digest + SHA1_DIGEST_SIZE; d++) {
		*dst++ = table[(*d >> 4) & 0xf];
		*dst++ = table[(*d >> 0) & 0xf];
	}
}

/// Returns a string representation of the SHA1 hash in hexadecimal notation
/// using upper case letters.
std::string sha1hash::uhex() const {
	char buffer[SHA1_DIGEST_SIZE*2];
	hex(buffer, *this, uhex_table);
	return std::string(buffer, buffer+sizeof(buffer));
}

/// Returns a string representation of the SHA1 hash in hexadecimal notation
/// using lower case letters.
std::string sha1hash::lhex() const {
	char buffer[SHA1_DIGEST_SIZE*2];
	hex(buffer, *this, lhex_table);
	return std::string(buffer, buffer+sizeof(buffer));
}

/// Returns a SHA1 hash from the given hexadecimal notation, which may use
/// either upper or lower case letters.
bool sha1hash::fromhex(const std::string& hex, sha1hash& out) {
	if (hex.length() != SHA1_DIGEST_SIZE*2)
		return false;

	auto hexval = [](char c) {
		if (c >= '0' && c <= '9') {
			return c - '0';
		} else if (c >= 'a' && c <= 'f') {
			return c - 'a' + 10;
		} else if (c >= 'A' && c <= 'F') {
			return c - 'A' + 10;
		} else {
			return -1;
		}
	};

	for (unsigned i = 0; i < SHA1_DIGEST_SIZE; i++) {
		auto vh = hexval(hex[i*2+0]);
		auto vl = hexval(hex[i*2+1]);
		if (vh == -1 || vl == -1)
			return false;
		out.digest[i] = vh << 4 | vl << 0;
	}
	return true;
}


/// Resets the hash engine as if no data has been processed yet.
sha1& sha1::reset() {
	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;
	state[4] = 0xc3d2e1f0;
	count = 0;
	return *this;
}

/// Processes the \a length bytes of \a data.
sha1& sha1::update(const Byte* data, size_t length) {

	Byte* bufptr = buffer + (count & 0x3f);
	Byte* const bufend = buffer + 64;
	const Byte* dataptr = data;
	const Byte* const dataend = data+length;

	// Handle the case where adding the given amount of data causes a buffer
	// overflow-
	if (bufptr + length >= bufend) {

		// Fill up the remaining bytes of the buffer and transform the state.
		auto p = dataptr;
		dataptr += (bufend-bufptr);
		std::copy(p, dataptr, bufptr);
		transform(buffer);
		bufptr = buffer;

		// Apply all remaining 64 byte chunks of the input data to the state.
		// This leaves less than 64 bytes from the data to be processed.
		while (dataend-dataptr >= 64) {
			transform(dataptr);
			dataptr += 64;
		}
	}

	// Append the data to the buffer. The previous stage needs to make sure that
	// this does not cause the buffer to be filled entirely.
	assert(bufptr+(dataend-dataptr) < bufend);
	if (dataptr < dataend)
		std::copy(dataptr, dataend, bufptr);

	count += length;
	return *this;
}

template<unsigned n> uint32_t rol(uint32_t v) {
	return (v << n) | (v >> (32-n));
}

/// Used internally to process a 64 byte block of data.
void sha1::transform(const Byte* data) {

	// Copy the current state into some handy work variables.
	uint32_t a = state[0];
	uint32_t b = state[1];
	uint32_t c = state[2];
	uint32_t d = state[3];
	uint32_t e = state[4];

	// Specify a lambda expression that merges one loop's result into the above
	// variables.
	auto apply = [&](uint32_t w, uint32_t f) {
		uint32_t tmp = rol<5>(a) + f + e + w;
		e = d;
		d = c;
		c = rol<30>(b);
		b = a;
		a = tmp;
	};

	// Specify the functions f and constants k used in the main loop.
	auto f0 = [&](){ return ((b & c) | (~b & d)) + 0x5a827999; };
	auto f1 = [&](){ return (b ^ c ^ d) + 0x6ed9eba1; };
	auto f2 = [&](){ return ((b & c) | (b & d) | (c & d)) + 0x8f1bbcdc; };
	auto f3 = [&](){ return (b ^ c ^ d) + 0xca62c1d6; };

	// The first 16 loop iterations operate on the unmodified input data.
	uint32_t chunk[16];
	for (unsigned i = 0; i < 16; i++) {
		chunk[i] = (data[i*4+0] << 24) | (data[i*4+1] << 16)
		         | (data[i*4+2] <<  8) | (data[i*4+3] <<  0);
		apply(chunk[i], f0());
	}

	// Specify a lambda expression that modifies the chunks on the fly in order
	// to obtain the "extended eighty 32 bit words".
	auto extend = [&](unsigned i) {
		uint32_t v = rol<1>(chunk[(i+13)%16] ^ chunk[(i+8)%16] ^ chunk[(i+2)%16]
			^ chunk[i%16]);
		chunk[i%16] = v;
		return v;
	};

	// Perform the remaining loop iterations.
	for (unsigned i = 16; i < 20; i++) apply(extend(i), f0());
	for (unsigned i = 20; i < 40; i++) apply(extend(i), f1());
	for (unsigned i = 40; i < 60; i++) apply(extend(i), f2());
	for (unsigned i = 60; i < 80; i++) apply(extend(i), f3());

	// Copy the result back into the state.
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
}

/// Wraps up and returns the final hash. Note that calling update() after
/// finalize() yields a corrupted hash.
sha1hash sha1::finalize() {

	// Convert the count into a 64 bit big endian integer.
	size_t bits = count*8;
	const Byte cnt[8] = {
		(Byte)(bits >> 56),
		(Byte)(bits >> 48),
		(Byte)(bits >> 40),
		(Byte)(bits >> 32),
		(Byte)(bits >> 24),
		(Byte)(bits >> 16),
		(Byte)(bits >>  8),
		(Byte)(bits >>  0)
	};

	// Append the bit '1'.
	update((const Byte[]){0x80}, 1); // append bit '1'

	// Pad the buffer such that there are 8 bytes left at the end.
	if ((count & 0x3f) > 56) {
		update((const Byte[]){0,0,0,0,0,0,0,0}, 64-(count & 0x3f));
	}

	if ((count & 0x3f) < 56) {
		Byte *begin = buffer + (count & 0x3f);
		Byte *end = buffer + 56;
		std::fill(begin, end, 0);
		count += end-begin;
	}
	assert((count & 0x3f) == 56);

	// Append the big endian count in bits, which should cause the message to
	// be padded to 512 bits, or 64 bytes.
	update(cnt, 8);
	assert((count & 0x3f) == 0);

	// Calculate the digest.
	sha1hash h;
	for (unsigned i = 0; i < SHA1_DIGEST_SIZE; i += 4) {
		h.digest[i+0] = (state[i/4] >> 24);
		h.digest[i+1] = (state[i/4] >> 16);
		h.digest[i+2] = (state[i/4] >> 8);
		h.digest[i+3] = (state[i/4] >> 0);
	}
	return h;
}
