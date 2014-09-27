/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Path.hpp"

namespace maxwell {
namespace filesystem {

/// An abstract interface for a directory of resources. Most likely implemented
/// by a disk directory class and a mock directory class.
class Directory {
public:
	/// Returns the path to the directory.
	virtual const Path& getPath() const = 0;

	// \todo Add functions that query the directory contents.
};

} // namespace filesystem
} // namespace maxwell
