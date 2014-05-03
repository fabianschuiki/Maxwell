/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <string>

struct sqlite3;

namespace backendc {

struct Packager
{
	Packager(sqlite3* db);
	~Packager();

	void run(const std::string& name);

private:
	sqlite3* const db;
};

} // namespace backendc
