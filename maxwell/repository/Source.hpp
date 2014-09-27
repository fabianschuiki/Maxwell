/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Path.hpp"
#include "maxwell/location.hpp"
#include "maxwell/sha1.hpp"

namespace maxwell {
namespace repository {

/// An object that describes a source file maintained by a source repository.
/// This is an abstract interface, and concrete subclasses of SourceRepository
/// are expected to provide their own implementations of Source.
class Source {
public:
	typedef maxwell::filesystem::Path Path;

	/// Returns the unique source ID that was allocated to this source file when
	/// it was added to the repository.
	virtual SourceId getId() const = 0;

	/// Returns the path that was given to the SourceRepository when the file
	/// was added. This usually does not directly correspond to an absolute file
	/// path, but is more of an opaque identifier used to access the file.
	virtual const Path& getPath() const = 0;

	/// Returns the hash of the file's path and contents. The intention of this
	/// hash is to detect changes to the source file.
	virtual const sha1hash& getHash() const = 0;
};

} // namespace repository
} // namespace maxwell
