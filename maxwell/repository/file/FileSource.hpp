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

	FileSourceRepository& repo;
	SourceId id;
	Path path;
	sha1hash hash;
	sha1hash pathHash;
	time_t modificationTime;

	mutable std::vector<Byte> content;
	mutable bool contentLoaded = false;

public:
	FileSource(FileSourceRepository& repo): repo(repo) {}

	SourceId getId() const { return id; }
	const Path& getPath() const { return path; }
	const sha1hash& getHash() const { return hash; }
	time_t getModificationTime() const { return modificationTime; }
	range<Byte*> getContent() const;
};

} // namespace repository
} // namespace maxwell
