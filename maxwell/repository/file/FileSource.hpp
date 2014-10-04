/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/repository/Source.hpp"

namespace maxwell {
namespace repository {

class FileSourceRepository;

/// A file-based Implementation of the Source interface used in the
/// FileSourceRepository.
class FileSource : public Source {
	friend class FileSourceRepository;

	SourceId id;
	Path path;
	sha1hash hash;
	sha1hash pathHash;
	time_t modificationTime;

public:
	SourceId getId() const { return id; }
	const Path& getPath() const { return path; }
	const sha1hash& getHash() const { return hash; }
	time_t getModificationTime() const { return modificationTime; }
};

} // namespace repository
} // namespace maxwell
