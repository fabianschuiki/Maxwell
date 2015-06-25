/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Directory.hpp"
#include "maxwell/filesystem/mock/MockFile.hpp"
#include <map>

namespace maxwell {
namespace filesystem {

/// A virtual directory useful during testing.
class MockDirectory : public Directory {
	Path path;

public:
	mutable std::map<std::string, MockFile> files;
	mutable std::map<std::string, MockDirectory> directories;
	mutable bool dexists;

	MockDirectory(const Path& path): path(path), dexists(false) {}

	const Path& getPath() const { return path; }
	bool exists() const { return dexists; }
	void unlink() const { dexists = false; }
	Directory* copy() const { return new MockDirectory(path); }

	File& getFile(const std::string& name) const {
		auto it = files.find(name);
		if (it == files.end()) {
			auto it = files.insert(std::make_pair(name, MockFile(path/name)));
			return it.first->second;
		}
		return it->second;
	}

	Directory& getDirectory(const std::string& name) const {
		auto it = directories.find(name);
		if (it == directories.end()) {
			auto it = directories.insert(std::make_pair(name,
				MockDirectory(path/name)));
			return it.first->second;
		}
		return it->second;
	}

	bool make() const { return false; }

	void eachFile(std::function<void(File&)> f) const {
		for (auto& v : files) {
			if (v.second.exists())
				f(v.second);
		}
	}

	void eachDirectory(std::function<void(Directory&)> f) const {
		for (auto& v : directories) {
			if (v.second.exists())
				f(v.second);
		}
	}

	/// Removes all files and directories which do not exist. This invalidates
	/// all references to files and directories that might still be around.
	void cleanup() {
		for (auto i = files.begin(); i != files.end();) {
			auto ic = i;
			i++;
			if (!ic->second.exists())
				files.erase(ic);
		}
		for (auto i = directories.begin(); i != directories.end();) {
			auto ic = i;
			i++;
			if (!ic->second.exists())
				directories.erase(ic);
		}
	}

};

} // namespace filesystem
} // namespace maxwell
