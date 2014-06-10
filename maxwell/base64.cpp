/* Copyright (c) 2013 Fabian Schuiki */
#include "maxwell/base64.hpp"
#include <stdexcept>
#include <cstdlib>

// Include the base64.h file in a separate namespace to avoid conflicts.
extern "C" {
	#define base64 NibbleAndAHalf_base64
	#define unbase64 NibbleAndAHalf_unbase64
	#include "thirdparty/base64.h"
	#undef base64
	#undef unbase64
}

/** Encodes the given data as base64 and returns the encoded string. */
std::string base64::encode(const void* data, size_t length)
{
	int out_len = 0;
	char* out = NibbleAndAHalf_base64(data, length, &out_len);
	if (out == NULL) {
		throw std::runtime_error("base64() returned a NULL string. This is most likely due to malloc() not being able to allocate enough memory.");
	}
	std::string out_str(out, out_len);
	free(out); // since we're in C ;)
	return out_str;
}

/** Decodes the given base64 string and returns the decoded string. */
std::string base64::decode(const char* data, size_t length)
{
	/* Don't attempt to decode strings that are shorter than 2 characters,
	 * as this would fail anyway in unbase64(). Catching it here leaves
	 * only memory issues to be returned by unbase64(). */
	if (length < 2) {
		throw std::runtime_error("Base64-decoding a string with only one character makes no sense.");
	}

	int out_len = 0;
	char* out = (char*)NibbleAndAHalf_unbase64(data, length, &out_len);
	if (out == NULL) {
		throw std::runtime_error("unbase64() returned a NULL string. This is most likely due to malloc() not being able to allocate enough memory.");
	}
	std::string out_str(out, out_len);
	free(out); // since we're in C, again!
	return out_str;
}
