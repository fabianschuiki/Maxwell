/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <map>
#include <string>

struct sqlite3;

namespace backendc {

struct Fragment;
struct Group;

struct Packager
{
	Packager(sqlite3* db);
	~Packager();

	void run(const std::string& name);
	void collect(const std::string& name);
	void sort();
	void group();
	void compile();

	std::map<std::string, std::string> files;

private:
	sqlite3* const db;
	std::map<std::string, Fragment*> fragments;
	std::map<std::string, Group*> groups;
};

} // namespace backendc
