/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Directory.hpp"
#include "maxwell/filesystem/MockFile.hpp"
#include <map>

namespace maxwell {
namespace filesystem {

/// A virtual directory useful during testing.
class MockDirectory : public Directory {
	Path path;

public:
	mutable std::map<std::string, MockFile> files;
	mutable std::map<std::string, MockDirectory> directories;

	MockDirectory(const Path& path): path(path) {}

	const Path& getPath() const { return path; }
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
};

} // namespace filesystem
} // namespace maxwell
