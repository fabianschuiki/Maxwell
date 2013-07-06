/* Copyright © 2013 Fabian Schuiki */
#include "SourceRepository.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

using ast::SourceRepository;
using std::string;
using std::ofstream;
using std::ifstream;

SourceRepository::SourceRepository(const boost::filesystem::path& path) : path(path)
{
	modified = false;
	loaded = false;
}

/**
 * @brief Flushes changes to the disk before destruction.
 */
SourceRepository::~SourceRepository()
{
	flush();
}

const SourceRepository::SourcesByName& SourceRepository::getSourcesByName()
{
	if (!loaded) load();
	return byName;
}

const SourceRepository::SourcesById& SourceRepository::getSourcesById()
{
	if (!loaded) load();
	return byId;
}

/**
 * @brief Flushes all changes to the persistent store on disk.
 */
void SourceRepository::flush()
{
	if (modified) store();
}

/**
 * @brief Adds the given source file to the register and returns its id.
 *
 * Simply returns the file's id if it is already registered.
 */
int SourceRepository::registerSource(const string& s)
{
	if (!loaded) load();
	SourcesByName::iterator it = byName.find(s);
	if (it != byName.end()) {
		return it->second;
	}
	int i;
	for (i = 1; byId.count(i) > 0; i++);
	byName[s] = i;
	byId[i] = s;
	modified = true;
	return i;
}

/**
 * @brief Removes the given file from the repository.
 *
 * Returns the id of the source file that was removed.
 */
int SourceRepository::unregisterSource(const string& s)
{
	if (!loaded) load();
	SourcesByName::iterator i = byName.find(s);
	if (i != byName.end()) {
		int id = i->second;
		byId.erase(id);
		byName.erase(i);
		modified = true;
		return id;
	}
	return 0;
}

/**
 * @brief Removes the file with the given id from the repository.
 */
void SourceRepository::unregisterSource(int i)
{
	if (!loaded) load();
	SourcesById::iterator it = byId.find(i);
	if (it != byId.end()) {
		byName.erase(it->second);
		byId.erase(i);
		modified = true;
	}
}

/**
 * @brief Loads the source file table from disk.
 *
 * Throws an exception if the repository has unflushed changes. In that case
 * you should call flush() first.
 */
void SourceRepository::load()
{
	if (modified) {
		throw std::runtime_error("Loading sources from disk would overwrite modified sources in memory.");
	}
	loaded = true;

	ifstream f(path.c_str());
	if (!f.good()) return;
	byId.clear();
	byName.clear();
	while (!f.eof()) {
		int i;
		string s;
		f >> i;
		while (!f.eof() && (f.peek() == ' ' || f.peek() == '\t'))
			f.get();
		if (f.eof()) break;
		std::getline(f, s);
		byId[i] = s;
		byName[s] = i;
	}
}

/**
 * @brief Stores the source file table to disk.
 *
 * Does nothing if the file table has never been loaded through the load()
 * function.
 */
void SourceRepository::store()
{
	if (!loaded) return;
	modified = false;

	ofstream f(path.c_str());
	if (!f.good()) {
		throw std::runtime_error("Unable to open source repository for writing at " + path.string() + ".");
	}
	for (SourcesById::iterator i = byId.begin(); i != byId.end(); i++) {
		f << i->first << "  " << i->second << "\n";
	}
}