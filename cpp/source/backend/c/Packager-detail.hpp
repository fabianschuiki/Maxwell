/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <sqlite3.hpp>
#include <set>
#include <string>
#include <vector>

namespace backendc {

struct Dependency
{
	std::string name;
	bool after;
	Fragment* frag;
};

struct Fragment
{
	int order;
	sqlite3_int64 rowid;
	std::string name;
	std::string code;
	std::string ref;
	std::string group;
	std::vector<Dependency> deps;
	bool after; // %after flags of all %deps or'd together
};

struct Group
{
	std::string name;
	std::vector<Fragment*> frags;
	std::vector<Group*> deps;
};

} // namespace backendc
