/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/serialization/interfaces.hpp"
#include <stdexcept>

namespace maxwell {
namespace serialization {

/// Straightforward implementation of a decoder that extracts data from an
/// existing memory location.
class ArrayDecoder : public Decoder {
	const Byte* buffer;
	size_t left;

public:
	/// Creates a new decoder processing the given \a buffer of the given \a
	/// length.
	ArrayDecoder(const Byte* buffer, size_t length):
		buffer(buffer),
		left(length) {}

	/// Creates a new decoder processing the memory between \a begin and \e end,
	/// excluding \a end.
	ArrayDecoder(const Byte* begin, const Byte* end):
		buffer(begin),
		left(end-begin) {}

	virtual Decoder& operator() (Byte* data, size_t length) {
		if (left < length) throw std::underflow_error("decoder underflow");
		left -= length;
		while (length > 0) {
			*data = *buffer;
			data++;
			buffer++;
			length--;
		}
		return *this;
	}

	virtual size_t remaining() const { return left; }
};

} // namespace serialization
} // namespace maxwell
