/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Path.hpp"

namespace maxwell {
namespace filesystem {

class File;

/// An abstract interface for a directory of resources. Most likely implemented
/// by a disk directory class and a mock directory class.
class Directory {
public:
	/// Returns the path to the directory.
	virtual const Path& getPath() const = 0;

	/// Returns a copy of the directory. The caller is responsible for freeing
	/// the copy, e.g. by assigning it to a std::unique_ptr.
	virtual Directory* copy() const = 0;

	virtual File& getFile(const std::string& name) const = 0;
	virtual Directory& getDirectory(const std::string& name) const = 0;
};

} // namespace filesystem
} // namespace maxwell
