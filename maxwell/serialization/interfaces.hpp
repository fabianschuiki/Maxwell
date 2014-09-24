/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/serialization/conversions.hpp"
#include "maxwell/types.hpp"
#include <string>
#include <vector>

/// \file
/// Encoder and decoder class interfaces. Objects that require serialization
/// should accept these two interfaces. Code that requires an object to be
/// serialized shall instantiate a concrete subclass of Encoder or Decoder and
/// pass that to the object to be serialized.

namespace maxwell {
namespace serialization {

/// Base class for an encoder, i.e. an object that may be used to serialize
/// other structures.
class Encoder {
public:
	/// Encodes \a length bytes from \a data to the encoder.
	virtual Encoder& operator() (const Byte* data, size_t length) = 0;

	/// Encodes the object \a data to the encoder.
	template <typename T>
	Encoder& operator() (const T& data) {
		T v = encodeConversion(data);
		(*this)((const Byte*)&v, sizeof(v));
		return *this;
	}

	/// Encodes the given string.
	Encoder& operator() (const std::string& data) {
		uint32_t l = data.size();
		(*this)(l);
		(*this)((const Byte*)data.c_str(), l);
		return *this;
	}
};

/// Base class for a decoder, i.e. an object that may be used to unserialize
/// other structures.
class Decoder {
public:
	/// Reads the next \a length bytes from the decoder into \a data. Throws an
	/// std::underflow_error if the decoder runs out of data.
	virtual Decoder& operator() (Byte* data, size_t length) = 0;
	/// Returns the remaining number of bytes in the decoder.
	virtual size_t remaining() const = 0;

	/// Decodes the next object of type \a T from the stream.
	template <typename T>
	Decoder& operator() (T& data) {
		T v;
		(*this)((Byte*)&v, sizeof(T));
		data = decodeConversion(v);
		return *this;
	}

	/// Decodes the next string from the stream.
	Decoder& operator() (std::string& data) {
		uint32_t l;
		(*this)(l);
		data.assign(l, 0);
		(*this)((Byte*)&data[0], l);
		return *this;
	}
};

} // namespace serialization
} // namespace maxwell
