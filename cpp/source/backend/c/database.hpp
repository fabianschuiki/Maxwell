/* Copyright (c) 2014 Fabian Schuiki */
#pragma once

struct sqlite3;

namespace backendc {

struct database
{
	sqlite3* db;
	database(sqlite3* db): db(db) {}
	void prepareFragmentsSchema();
};

} // namespace backendc
