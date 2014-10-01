/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Node.hpp"
#include "maxwell/filesystem/Path.hpp"
#include <vector>

namespace maxwell {
namespace filesystem {

/// An abstract interface shared between files and directories.
class Node {
public:
	/// Returns the name of the file or directory.
	virtual std::string getName() const {
		return getPath().filename().string();
	}

	/// Returns the path to the file or directory.
	virtual const Path& getPath() const = 0;

	/// Returns whether the file or directory exists or not. Directories may
	/// return files that do not exist, but are created as soon as write() is
	/// called on them.
	virtual bool exists() const = 0;

	/// Remove the file or directory.
	virtual void unlink() const = 0;
};

} // namespace filesystem
} // namespace maxwell
