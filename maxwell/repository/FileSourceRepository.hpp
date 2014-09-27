/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/repository/SourceRepository.hpp"
#include "maxwell/filesystem/Directory.hpp"
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
};

/// A file-based implementation of the SourceRepository interface.
class FileSourceRepository : public SourceRepository {
public:
	typedef maxwell::filesystem::Directory Directory;

	FileSourceRepository(const Directory& dir): dir(dir) {}
	~FileSourceRepository() {}

	bool add(const Path& path, const File& file);
	bool remove(SourceId sid);
	bool remove(const Path& path);

	SourceId getSourceId(const Path& path) const;
	Path getPath(SourceId sid) const;

private:
	const Directory& dir;

	std::map<SourceId, std::unique_ptr<FileSource>> sourcesById;
	std::map<Path, FileSource*> sourcesByPath;
};

} // namespace repository
} // namespace maxwell
