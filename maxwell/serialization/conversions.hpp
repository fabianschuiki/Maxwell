/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/serialization/endian.hpp"

/// \file
/// Conversion functions that allow automatic endianness conversion when
/// encoding and decoding.

namespace maxwell {
namespace serialization {

// Automatic endianness conversion for unsigned integers.
uint16_t encodeConversion(const uint16_t& v) { return *(uint16_t*)bu16(v).v; }
uint32_t encodeConversion(const uint32_t& v) { return *(uint32_t*)bu32(v).v; }
uint64_t encodeConversion(const uint64_t& v) { return *(uint64_t*)bu64(v).v; }

uint16_t decodeConversion(const uint16_t& v) { return *(bu16*)&v; }
uint32_t decodeConversion(const uint32_t& v) { return *(bu32*)&v; }
uint64_t decodeConversion(const uint64_t& v) { return *(bu64*)&v; }

// Automatic endianness conversion for signed integers.
int16_t encodeConversion(const int16_t& v) { return *(int16_t*)bi16(v).v; }
int32_t encodeConversion(const int32_t& v) { return *(int32_t*)bi32(v).v; }
int64_t encodeConversion(const int64_t& v) { return *(int64_t*)bi64(v).v; }

int16_t decodeConversion(const int16_t& v) { return *(bi16*)&v; }
int32_t decodeConversion(const int32_t& v) { return *(bi32*)&v; }
int64_t decodeConversion(const int64_t& v) { return *(bi64*)&v; }

/// Fallback identity conversion.
template<typename T>
T encodeConversion(const T& v) {
	return v;
}

/// Fallback identity conversion.
template<typename T>
T decodeConversion(const T& v) {
	return v;
}

} // namespace serialization
} // namespace maxwell
