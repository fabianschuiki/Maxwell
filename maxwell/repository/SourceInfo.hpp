/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem.hpp"
#include <string>

namespace maxwell {
namespace repository {

/// A snippet of information stored in a SourceIndex.
class SourceInfo {
	const uint32_t id;
	const Path path;
	const std::string hash;

public:
	SourceInfo(uint32_t id, const Path& path, const std::string& hash):
		id(id),
		path(path),
		hash(hash) {}

	uint32_t getId() const { return id; }
	const Path& getPath() const { return path; }
	const std::string& getHash() const { return hash; }
};

} // namespace repository
} // namespace maxwell
