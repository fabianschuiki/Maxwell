/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/File.hpp"
#include "maxwell/filesystem/Path.hpp"
#include "maxwell/location.hpp"

namespace maxwell {
namespace repository {

/// An object that maintains a set of source files and detects changes in them.
/// For each source file added, the repository must track
///
/// - a unique id (the source id),
/// - the file's path,
/// - contents,
/// - hash of the contents, and
/// - modification timestamp.
///
/// Adding a file to the repository and updating an existing file's entry is the
/// same operation. To do this, the repository requires a data structure that
/// represents a file and gives access to the file's path, modification
/// timestamp and contents.
///
/// Removing a file from the repository requires knowledge of that file's path
/// or unique id.
///
/// A file can be requested from the repository given its path or unique id. The
/// list of files may be accessed directly as an opaque, iterable field; or by
/// obtaining a begin and end iterator as is common in C++.

class SourceRepository {
public:
	typedef maxwell::filesystem::File File;
	typedef maxwell::filesystem::Path Path;

	/// Adds the given \a file to the repository under the given \a path. If the
	/// repository already contains an entry for the \a path, that entry is
	/// updated.
	///
	/// \note Note that the separate \a path argument allows for the paths in
	/// the repository to be relative to some common location, e.g. the root of
	/// the source base. By contrast, the \a file is likely to have a path
	/// relative to the current working directory.
	///
	/// \return Returns false if the file was already present in the repository
	/// with the same contents as the \a file provided. Otherwise returns true
	/// if an entry in the repository was updated or changed.
	virtual bool add(const Path& path, const File& file) = 0;

	/// Removes the source file with the given \a sid.
	/// \return Returns whether the file was present in the repository and had
	/// to be removed.
	virtual bool remove(SourceId sid) = 0;

	/// Removes the source file with the given \a path. Note that this is the
	/// path that was passed to the add() function as \a path argument.
	/// \return Returns whether the file was present in the repository and had
	/// to be removed.
	virtual bool remove(const Path& path) = 0;

	virtual SourceId getSourceId(const Path& path) const = 0;
	virtual Path getPath(SourceId sid) const = 0;

	/// \todo Add accessor to individual files.
	/// \todo Add iterator over all files.
};

} // namespace repository
} // namespace maxwell
