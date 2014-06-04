/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <string>

/**
 * @brief A wrapper class around William Sherif's base64.h
 */
struct base64
{
	static std::string encode(const std::string s);
	static std::string encode(const void* data, int length);
	static std::string decode(const std::string s);
};
