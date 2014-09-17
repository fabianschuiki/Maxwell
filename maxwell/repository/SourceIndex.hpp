/* Coypright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/repository/SourceIndexInterface.hpp"

namespace maxwell {
namespace repository {

/// An index that assigns IDs to source files. Also keeps track of their paths.
class SourceIndex : public SourceIndexInterface {
	const File& file;

public:
	SourceIndex(const File& file): file(file) {}
	~SourceIndex() {}

	void addFile(const File& file);
	bool removeFile(const File& file);
};

} // namespace repository
} // namespace maxwell
