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

	bool addFile(const Path& path);
	bool removeFile(const Path& path);
};

} // namespace repository
} // namespace maxwell
