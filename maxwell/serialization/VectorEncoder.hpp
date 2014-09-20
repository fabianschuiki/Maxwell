/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/serialization/interfaces.hpp"

namespace maxwell {
namespace serialization {

/// Straightforward implementation of an encoder that serializes data to an
/// std::vector specified by the caller.
class VectorEncoder : public Encoder {
	std::vector<Byte>& buffer;

public:
	/// Creates a new encoder that stores its encoded data in the given \a
	/// buffer.
	VectorEncoder(std::vector<Byte>& buffer): buffer(buffer) {}

	virtual Encoder& operator() (const Byte* data, size_t length) {
		buffer.insert(buffer.end(), data, data + length);
		return *this;
	}
};

} // namespace serialization
} // namespace maxwell
