/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/repository/SourceRepositoryInterface.hpp"

namespace maxwell {
namespace repository {

/// Manages a repository of source files.
class SourceRepository : public SourceRepositoryInterface {
	const Path path;

public:
	SourceRepository(const Path& path): path(path) {}
	~SourceRepository() {}

	/// Returns the path managed by this repository.
	const Path& getPath() const { return path; }

	bool addFile(const Path& path);
	bool removeFile(const Path& path);
};

} // namespace repository
} // namespace maxwell
