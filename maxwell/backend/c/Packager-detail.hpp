/* Copyright (c) 2014-2015 Fabian Schuiki */
#pragma once
#include "maxwell/sqlite3.hpp"
#include <set>
#include <string>
#include <vector>

namespace backendc {

struct Deendency;
struct Fragment;
struct Group;

struct Dependency {
	std::string name;
	bool after;
	Fragment* frag;
};

struct Fragment {
	int order;
	int id;
	std::string name;
	std::string code;
	std::string ref;
	std::string group;
	std::vector<Dependency> deps;
	std::vector<std::string> incs;
	bool after; // %after flags of all %deps or'd together
};

struct Group {
	std::string name;
	std::vector<Fragment*> frags;
	std::vector<Group*> deps;
	std::set<std::string> incs;
};

} // namespace backendc
