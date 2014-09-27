/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/types.hpp"
#include <string>

namespace maxwell {

static const unsigned SHA1_DIGEST_SIZE = 20; // bytes

class sha1;
class sha1hash;

// A SHA1 hash computed using the sha1 class.
class sha1hash {
	friend class sha1;

	union {
		Byte digest[20];
		uint32_t chunk[5];
	};

public:
	operator const Byte*() const { return digest; }

	bool operator==(const sha1hash& v) const {
		return std::equal(chunk, chunk+5, v.chunk);
	}
	bool operator!=(const sha1hash& v) const { return !operator==(v); }

	const Byte* bytes() const { return *this; }
	std::string uhex() const;
	std::string lhex() const;
};

/// An implementation of the SHA1 hashing algorithm.
class sha1 {
	uint32_t state[5];
	Byte buffer[64];
	size_t count;

	void transform(const Byte* data);

public:
	sha1() { reset(); }
	sha1(const sha1& v) { *this = v; }
	sha1(const Byte* data, size_t length) { reset(); update(data, length); }

	sha1& reset();
	sha1& update(const Byte* data, size_t length);
	sha1hash finalize();

	sha1& update(const char* str) {
		const char* end = str;
		while (*end != 0) end++;
		return update((const Byte*)str, end-str);
	}

	operator sha1hash() { return finalize(); }
};

} // namespace maxwell
