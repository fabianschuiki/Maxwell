/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/types.hpp"
#include <algorithm>
#include <functional>
#include <string>

namespace maxwell {

static const unsigned SHA1_DIGEST_SIZE = 20; // bytes

class sha1;
class sha1hash;

/// A SHA1 hash computed using the sha1 class.
class sha1hash {
	friend class sha1;

	union {
		Byte digest[20];
		uint32_t chunk[5];
	};

public:
	/// Creates an invalid SHA1 hash.
	sha1hash() {}
	/// Creates a SHA1 hash with the given 20 bytes of \a digest.
	sha1hash(const Byte* digest) {
		std::copy((uint32_t*)digest, (uint32_t*)(digest+20), chunk);
	}

	/// Returns a pointer to the 20 digest bytes of this hash.
	operator const Byte*() const { return digest; }

	bool operator==(const sha1hash& v) const {
		return std::equal(chunk, chunk+5, v.chunk);
	}
	bool operator!=(const sha1hash& v) const {
		return !operator==(v);
	}
	bool operator<=(const sha1hash& v) const {
		return std::equal(chunk, chunk+5, v.chunk, std::less_equal<Byte>());
	}
	bool operator<(const sha1hash& v) const {
		return std::equal(chunk, chunk+5, v.chunk, std::less<Byte>());
	}
	bool operator>=(const sha1hash& v) const {
		return std::equal(chunk, chunk+5, v.chunk, std::greater_equal<Byte>());
	}
	bool operator>(const sha1hash& v) const {
		return std::equal(chunk, chunk+5, v.chunk, std::greater<Byte>());
	}

	/// Returns a pointer to the 20 digest bytes of this hash.
	const Byte* bytes() const { return digest; }

	std::string uhex() const;
	std::string lhex() const;

	static bool fromhex(const std::string& hex, sha1hash& out);
};

/// An implementation of the SHA1 hashing algorithm. Allows the user to input
/// arbitrary data by keeping a buffer of 64 bytes to generate the 512 bit
/// chunks required for SHA1 hashing.
class sha1 {
	uint32_t state[5];
	Byte buffer[64];
	size_t count;

	void transform(const Byte* data);

public:
	/// Creates a new SHA1 hash engine.
	sha1() { reset(); }
	/// Copies the given hash engine.
	sha1(const sha1& v) { *this = v; }
	/// Copies the given hash engine.
	sha1(sha1& v) { *this = v; } // otherwise templated c'tor is called
	/// Creates a new SHA1 hash engine and calls update() on it with the given
	/// arguments \a args.
	template<typename... Args>
	sha1(Args&&... args) {
		reset();
		update(args...);
	}

	sha1& reset();
	sha1& update(const Byte* data, size_t length);
	sha1hash finalize();

	/// Processes the given input string \a str.
	sha1& update(const char* str) {
		const char* end = str;
		while (*end != 0) end++;
		return update((const Byte*)str, end-str);
	}

	/// Processes the given input string \a str.
	sha1& update(const std::string& str) {
		return update((const Byte*)str.c_str(), str.length());
	}

	/// Synonym for finalize().
	operator sha1hash() { return finalize(); }
};

} // namespace maxwell
