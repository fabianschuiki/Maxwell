/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/repository/FileSourceRepository.hpp"
#include "maxwell/serialization/VectorEncoder.hpp"

using maxwell::filesystem::Path;
using maxwell::serialization::VectorEncoder;
using maxwell::serialization::Encoder;
using maxwell::SourceId;
using namespace maxwell::repository;


FileSourceRepository::FileSourceRepository(const Directory& dir):
	dir(dir),
	needsFlush(false) {

	// Load stuff.
}

FileSourceRepository::~FileSourceRepository() {
	if (needsFlush)
		flush();
}

bool FileSourceRepository::add(const Path& path, const File& file) {

	// Calculate the hash of the file.
	std::vector<Byte> data;
	data.reserve(4*1024); // pre-allocate storage for speed
	file.read(data);

	sha1 base;
	base.update(path.c_str());
	sha1hash pathHash = sha1(base);
	sha1hash hash = base.update(&data[0], data.size());

	auto it = sourcesByPath.find(path);
	if (it != sourcesByPath.end()) {
		if (it->second->hash == hash)
			return false;
		it->second->hash = hash;
	}

	else {
		// Allocate the next SourceId.
		SourceId sid(sourcesById.empty() ? 1 :
			sourcesById.rbegin()->first.getId() + 1);

		// Create a new file entry.
		std::unique_ptr<FileSource> src(new FileSource);
		src->id = sid;
		src->path = path;
		src->pathHash = pathHash;
		src->hash = hash;

		// Store the file in the indices.
		sourcesByPath[src->path] = src.get();
		sourcesById[src->id] = std::move(src);
	}

	needsFlush = true;
	return true;
}

bool FileSourceRepository::remove(SourceId sid) {
	auto it = sourcesById.find(sid);
	if (it == sourcesById.end())
		return false;

	sourcesByPath.erase(it->second->path);
	sourcesById.erase(it);
	needsFlush = true;
	return true;
}

bool FileSourceRepository::remove(const Path& path) {
	auto it = sourcesByPath.find(path);
	if (it == sourcesByPath.end())
		return false;

	sourcesById.erase(it->second->id); // it->second is now invalid
	sourcesByPath.erase(it);
	needsFlush = true;
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

void FileSourceRepository::flush() const {

	// Serialize the index.
	std::vector<Byte> index;
	index.reserve(4*1024); // pre-allocate storage for speed
	VectorEncoder indexEncoder(index);
	Encoder& enc = indexEncoder; // enables use of templates in Encoder

	for (auto& pair : sourcesById) {
		auto& src = pair.second;
		enc(src->getId().getId());
		enc(src->getPath().native());
	}

	// Store the serialized data to disk.
	needsFlush = false;
	File& indexFile = dir.getFile("index");
	indexFile.write(index);
	std::cout << "flushed " << index.size() << "B to " << indexFile.getPath()
		<< '\n';
}
