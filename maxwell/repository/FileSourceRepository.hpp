/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Directory.hpp"
#include "maxwell/repository/SourceRepository.hpp"
#include "maxwell/sha1.hpp"
#include <map>
#include <memory>

namespace maxwell {
namespace repository {

class FileSourceRepository;

class FileSource {
public:
	typedef maxwell::filesystem::Path Path;

	SourceId getId() const { return id; }
	const Path& getPath() const { return path; }

private:
	friend class FileSourceRepository;

	SourceId id;
	Path path;
	sha1hash hash;
	sha1hash pathHash;
};

/// A file-based implementation of the SourceRepository interface.
class FileSourceRepository : public SourceRepository {
public:
	typedef maxwell::filesystem::Directory Directory;

	FileSourceRepository(const Directory& dir);
	~FileSourceRepository();

	bool add(const Path& path, const File& file);
	bool remove(SourceId sid);
	bool remove(const Path& path);

	SourceId getSourceId(const Path& path) const;
	Path getPath(SourceId sid) const;

	void flush() const;

private:
	const Directory& dir;

	mutable bool needsFlush;
	std::map<SourceId, std::unique_ptr<FileSource>> sourcesById;
	std::map<Path, FileSource*> sourcesByPath;
};

} // namespace repository
} // namespace maxwell
