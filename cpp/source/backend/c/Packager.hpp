/* Copyright (c) 2014 Fabian Schuiki */
#pragma once

struct sqlite3;

namespace backendc {

struct Packager
{
	Packager(sqlite3* db);
	~Packager();

private:
	sqlite3* const db;
};

} // namespace backendc
