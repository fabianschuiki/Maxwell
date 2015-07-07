/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Directory.hpp"
#include "maxwell/repository/Source.hpp"
#include "maxwell/repository/SourceRepository.hpp"
#include "maxwell/sha1.hpp"
#include "maxwell/memory.hpp"
#include <map>

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
	void removeAll();

	SourceId getSourceId(const Path& path) const;
	Path getPath(SourceId sid) const;

	Source* getSource(SourceId sid) const;
	Source* getSource(const Path& path) const;

	void eachSource(std::function<void(const Source&)> fn) const;

	bool isModified(const Path& path, const File& file) const;
	bool isModified(SourceId sid, const File& file) const;

	void flush() const;
	void purge() const;

private:
	/// Directory maintained by this repository.
	const Directory& dir;

	/// Flag set if the index was modified and needs to be written to disk.
	mutable bool needsFlush;
	/// Flag set if the cached source files in the directory need to be cleaned.
	mutable bool needsPurge;

	/// Organizes the sources by their unique ID. Owns the source information
	/// objects.
	std::map<SourceId, std::unique_ptr<FileSource>> sourcesById;
	/// Organizes the sources by their path.
	std::map<Path, FileSource*> sourcesByPath;
	/// Organizes the sources by their path hash.
	std::map<sha1hash, FileSource*> sourcesByPathHash;
};

} // namespace repository
} // namespace maxwell
