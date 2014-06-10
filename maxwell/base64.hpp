/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include <string>

/**
 * @brief A wrapper class around William Sherif's base64.h
 */
struct base64
{
	static std::string encode(const std::string& s) {
		return encode(s.c_str(), s.size());
	}

	static std::string decode(const std::string& s) {
		return decode(s.c_str(), s.size());
	}

	static std::string encode(const void* data, size_t length);
	static std::string decode(const char* data, size_t length);
};
