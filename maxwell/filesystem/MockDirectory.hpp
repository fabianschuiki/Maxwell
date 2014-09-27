/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Directory.hpp"

namespace maxwell {
namespace filesystem {

/// A virtual directory useful during testing.
class MockDirectory : public Directory {
	Path path;

public:
	MockDirectory(const Path& path): path(path) {}

	const Path& getPath() const { return path; }
};

} // namespace filesystem
} // namespace maxwell
