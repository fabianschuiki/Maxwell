/* Copyright (c) 2014 Fabian Schuiki */
#pragma once

/** @file Includes sqlite3.h and adds an exception class that helps dealing
 * with sqlite3 errors in C++ code. */

extern "C" {
	#include "thirdparty/sqlite3.h"
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

struct sqlite3_statement
{
	sqlite3_stmt* stmt;

	sqlite3_statement(): stmt(NULL) {}
	~sqlite3_statement() { if (stmt) sqlite3_finalize(stmt); stmt = NULL; }

	void prepare(sqlite3* db, const char* zSql, int nByte = -1, const char** pzTail = NULL) {
		int rc = sqlite3_prepare_v2(db, zSql, nByte, &stmt, pzTail);
		if (rc != SQLITE_OK) {
			std::stringstream s;
			s << "Unable to prepare statement '" << zSql << "'";
			throw sqlite3_exception(rc, s.str());
		}
	}

	bool step() {
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_DONE)
			return false;
		if (rc == SQLITE_ROW)
			return true;
		throw sqlite3_exception(rc, "Unable to step statement");
	}

	void reset() {
		int rc = sqlite3_reset(stmt);
		if (rc != SQLITE_OK)
			throw sqlite3_exception(rc, "Unable to reset statement");
	}

	operator sqlite3_stmt*() const { return stmt; }
};

/** Convenience define that calls sqlite3_<expr> and checks whether the result
 * is SQLITE_OK, throwing an sqlite3_exception if it is not. */
#define sqlite3_throw(expr) { int rc = sqlite3_##expr; if (rc != SQLITE_OK) throw sqlite3_exception(rc, "Unable to " #expr); }
