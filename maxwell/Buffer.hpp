/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/types.hpp"

namespace maxwell {

/// A chunk of memory containing an arbitrary sequence of elements. The buffer
/// does not own the memory.
template<typename T>
class Buffer {
	T* start;
	T* end;

public:
	/// Creates an empty buffer.
	Buffer(): start(NULL), end(NULL) {}

	/// Creates a buffer ranging from \a ptr to \a ptr + \a length.
	Buffer(T* ptr, size_t length):
		start(ptr),
		end(ptr+length) {}

	/// Creates a buffer ranging from \a start to \a end.
	Buffer(T* start, T* end):
		start(start),
		end(end) {}

	/// Creates a buffer ranging from \a ptr to the terminating 0 value.
	Buffer(T* ptr):
		start(ptr),
		end(find(ptr, 0)) {}

	/// Returns a pointer to the first element in the buffer.
	T* getStart() const { return start; }

	/// Returns a pointer to the position just after the last element in the
	/// buffer.
	T* getEnd() const { return end; }

	/// Returns the number of elements in the buffer.
	size_t getLength() const { return end-start; }

	/// Returns true if the buffer is empty.
	bool isEmpty() const { return start == end; }

private:
	/// Looks for the given value and returns an iterator to it.
	T* find(T* first, const T& value) {
		while (*first != value)
			++first;
		return first;
	}
};

} // namespace maxwell
