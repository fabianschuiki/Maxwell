/* Copyright (c) 2014 Fabian Schuiki */

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

	sqlite3_exception(int err, const std::string& comment) throw(): err(err), comment(comment) {
		errmsg = sqlite3_errstr(err);
	}
	virtual ~sqlite3_exception() throw() {}
	virtual const char* what() const throw() {
		std::stringstream s;
		s << comment << "; " << errmsg << " (sqlite3 error " << err << ')';
		return s.str().c_str();
	}
};
