/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include "maxwell/types.hpp"

/// \file
/// Wrappers for big and little endian values that allows for automatic
/// conversion from and to the host endianness.

namespace maxwell {
namespace serialization {

template <typename U, int size>
struct big_endian_value {
	uint8_t v[size];

	big_endian_value() {}
	big_endian_value(U u) { *this = u; }

	inline big_endian_value& operator= (U x) {
		for (int i = 0; i < size; i++)
			v[i] = x >> ((size-i-1)*8);
		return *this;
	}

	inline operator U() const {
		U x = 0;
		for (int i = 0; i < size; i++)
			x |= ((U)v[i]) << ((size-i-1)*8);
		return x;
	}
};

namespace convenience {
	typedef big_endian_value<uint8_t,  1> bu8;
	typedef big_endian_value<uint16_t, 2> bu16;
	typedef big_endian_value<uint32_t, 4> bu32;
	typedef big_endian_value<uint64_t, 8> bu64;

	typedef big_endian_value<int8_t,  1> bi8;
	typedef big_endian_value<int16_t, 2> bi16;
	typedef big_endian_value<int32_t, 4> bi32;
	typedef big_endian_value<int64_t, 8> bi64;
}


template <typename U, int size>
struct little_endian_value {
	uint8_t v[size];

	little_endian_value() {}
	little_endian_value(U u) { *this = u; }

	inline little_endian_value& operator= (U x) {
		for (int i = 0; i < size; i++)
			v[i] = x >> (i*8);
		return *this;
	}

	inline operator U() {
		U x = 0;
		for (int i = 0; i < size; i++)
			x |= ((U)v[i]) << (i*8);
		return x;
	}
};

namespace convenience {
	typedef little_endian_value<uint8_t,  1> lu8;
	typedef little_endian_value<uint16_t, 2> lu16;
	typedef little_endian_value<uint32_t, 4> lu32;
	typedef little_endian_value<uint64_t, 8> lu64;

	typedef little_endian_value<int8_t,  1> li8;
	typedef little_endian_value<int16_t, 2> li16;
	typedef little_endian_value<int32_t, 4> li32;
	typedef little_endian_value<int64_t, 8> li64;
}

// Make sure the endian convenience types are available under the serialization
// namespace.
using namespace convenience;

} // namespace serialization
} // namespace maxwell
