/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Directory.hpp"
#include "maxwell/filesystem/disk/DiskFile.hpp"
#include <map>

namespace maxwell {
namespace filesystem {

/// A directory on disk.
class DiskDirectory : public Directory {
	const Path path;

	mutable std::map<std::string, DiskFile> fileCache;
	mutable std::map<std::string, DiskDirectory> directoryCache;

public:
	DiskDirectory(const Path& path): path(path) {}
	Directory* copy() const { return new DiskDirectory(path); }

	const Path& getPath() const { return path; }
	bool exists() const;
	void unlink() const;
	bool make() const;

	File& getFile(const std::string& name) const;
	Directory& getDirectory(const std::string& name) const;

	void eachFile(std::function<void(File&)> fn) const;
	void eachDirectory(std::function<void(Directory&)> fn) const;
};

} // namespace filesystem
} // namespace maxwell
