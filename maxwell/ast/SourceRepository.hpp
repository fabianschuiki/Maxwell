/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include <map>
#include <string>
#include <boost/filesystem.hpp>

namespace ast {

using std::map;
using std::string;

/**
 * Manages a map of source files and a unique ID assigned to them that resides
 * on disk.
 */
class SourceRepository
{
public:
	const boost::filesystem::path path;
	SourceRepository(const boost::filesystem::path& path);
	~SourceRepository();

	typedef map<string, int> SourcesByName;
	typedef map<int, string> SourcesById;
	const SourcesByName& getSourcesByName();
	const SourcesById& getSourcesById();
	const string& getSourceName(int id);

	void flush();

	int registerSource(const string& s);
	int unregisterSource(const string& s);
	void unregisterSource(int i);

private:
	SourcesByName byName;
	SourcesById byId;
	bool modified;
	bool loaded;

	void load();
	void store();
};

} // namespace ast
