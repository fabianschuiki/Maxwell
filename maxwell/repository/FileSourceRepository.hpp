/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Directory.hpp"
#include "maxwell/repository/Source.hpp"
#include "maxwell/repository/SourceRepository.hpp"
#include "maxwell/sha1.hpp"
#include <map>
#include <memory>

namespace maxwell {
namespace repository {

class FileSource;

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
	void purge() const;

private:
	const Directory& dir;

	mutable bool needsFlush;
	mutable bool needsPurge;
	std::map<SourceId, std::unique_ptr<FileSource>> sourcesById;
	std::map<Path, FileSource*> sourcesByPath;
	std::map<sha1hash, FileSource*> sourcesByPathHash;
};

} // namespace repository
} // namespace maxwell
