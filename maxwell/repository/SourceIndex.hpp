/* Coypright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem.hpp"
// #include "maxwell/repository/SourceIndexInterface.hpp"

namespace maxwell {
namespace repository {

/// An index that assigns IDs to source files. Also keeps track of their paths.
class SourceIndex {
	const File& file;

public:
	SourceIndex(const File& file): file(file) {}
	~SourceIndex() {}

	bool add(const Path& path);
	bool remove(const Path& path);
};

} // namespace repository
} // namespace maxwell
