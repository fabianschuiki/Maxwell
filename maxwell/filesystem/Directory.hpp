/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Node.hpp"
#include "maxwell/filesystem/Path.hpp"

namespace maxwell {
namespace filesystem {

class File;

/// An abstract interface for a directory of resources. Most likely implemented
/// by a disk directory class and a mock directory class.
class Directory : public Node {
public:
	/// Returns a copy of the directory. The caller is responsible for freeing
	/// the copy, e.g. by assigning it to a std::unique_ptr.
	virtual Directory* copy() const = 0;

	/// Returns a reference to the given file, even if the file does not exist.
	/// This allows files to be created.
	virtual File& getFile(const std::string& name) const = 0;
	/// Returns a reference to the given directory, even if the directory does
	/// not exist. This allows directories to be created.
	virtual Directory& getDirectory(const std::string& name) const = 0;

	/// Creates the directory. Returns true if the directory had to be created,
	/// or false if it already existed.
	virtual bool make() const = 0;

	/// Calls \a f for each file in the directory.
	virtual void eachFile(std::function<void(File&)> f) const = 0;
	/// Calls \a f for each subdirectory.
	virtual void eachDirectory(std::function<void(Directory&)> f) const = 0;
};

} // namespace filesystem
} // namespace maxwell
