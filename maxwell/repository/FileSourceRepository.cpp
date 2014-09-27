/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/repository/FileSourceRepository.hpp"
using maxwell::filesystem::Path;
using maxwell::SourceId;
using namespace maxwell::repository;

bool FileSourceRepository::add(const Path& path, const File& file) {
	if (sourcesByPath.count(path))
		return false;

	// Allocate the next SourceId.
	SourceId sid(sourcesById.empty() ? 1 :
		sourcesById.rbegin()->first.getId() + 1);

	// Create a new file entry.
	std::unique_ptr<FileSource> src(new FileSource);
	src->id = sid;
	src->path = path;

	// Store the file in the indices.
	sourcesByPath[src->path] = src.get();
	sourcesById[src->id] = std::move(src);

	return true;
}

bool FileSourceRepository::remove(SourceId sid) {
	auto it = sourcesById.find(sid);
	if (it == sourcesById.end())
		return false;

	sourcesByPath.erase(it->second->path);
	sourcesById.erase(it);
	return true;
}

bool FileSourceRepository::remove(const Path& path) {
	auto it = sourcesByPath.find(path);
	if (it == sourcesByPath.end())
		return false;

	sourcesById.erase(it->second->id); // it->second is now invalid
	sourcesByPath.erase(it);
	return true;
}

SourceId FileSourceRepository::getSourceId(const Path& path) const {
	auto it = sourcesByPath.find(path);
	return it != sourcesByPath.end() ? it->second->id : SourceId();
}

Path FileSourceRepository::getPath(SourceId sid) const {
	auto it = sourcesById.find(sid);
	return it != sourcesById.end() ? it->second->path : Path();
}
