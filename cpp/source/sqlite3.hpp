/* Copyright (c) 2014 Fabian Schuiki */
#pragma once

/** @file Includes sqlite3.h and adds an exception class that helps dealing
 * with sqlite3 errors in C++ code. */

extern "C" {
	#include "sqlite3.h"
}

#include <stdexcept>
#include <sstream>
#include <string>

struct sqlite3_exception : public std::exception
{
	int err;
	std::string comment, errmsg;
	std::string msg;

	sqlite3_exception(int err, const std::string& comment) throw(): err(err), comment(comment) {
		errmsg = sqlite3_errstr(err);
		std::stringstream s;
		s << comment << "; " << errmsg << " (sqlite3 error " << err << ')';
		msg = s.str();
	}
	virtual ~sqlite3_exception() throw() {}
	virtual const char* what() const throw() {
		return msg.c_str();
	}
};
