/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <map>
#include <queue>
#include <string>

struct sqlite3;

namespace backendc {

struct Fragment;
struct Group;

struct Packager
{
	Packager(sqlite3* db);
	~Packager();

	/** Packages the fragment with the given name, together with all its
	 * dependencies. */
	void run(const std::string& name) {
		collect(name);
		sort();
		group();
		compile();
	}

	/** Packages the fragments first..last, together with all their
	 * dependencies */
	template<class Iterator> void run(Iterator first, Iterator last) {
		collect(first, last);
		sort();
		group();
		compile();
	}

	/** Collects all dependencies for the fragment with the given name. This
	 * prepares the Packager for subsequent calls to sort(), group(), and
	 * compile(). */
	void collect(const std::string& name) {
		std::queue<std::string> names;
		names.push(name);
		collect(names);
	}

	/** Collects all dependencies for the fragments first..last. This prepares
	 * the Packager for subsequent calls to sort(), group(), and compile(). */
	template<class Iterator> void collect(Iterator first, Iterator last) {
		std::queue<std::string> names;
		for (Iterator i = first; i != last; i++)
			names.push(*i);
		collect(names);
	}

	void sort();
	void group();
	void compile();

	std::map<std::string, std::string> files;

private:
	sqlite3* const db;
	std::map<std::string, Fragment*> fragments;
	std::map<std::string, Group*> groups;

	void collect(std::queue<std::string>& names);
};

} // namespace backendc
