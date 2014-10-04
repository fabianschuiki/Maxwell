/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/repository/file/FileSource.hpp"
#include "maxwell/repository/file/FileSourceRepository.hpp"
#include "maxwell/repository/Source.hpp"
#include "maxwell/serialization/VectorEncoder.hpp"
#include "maxwell/serialization/ArrayDecoder.hpp"

using maxwell::sha1;
using maxwell::sha1hash;
using maxwell::filesystem::Path;
using maxwell::serialization::VectorEncoder;
using maxwell::serialization::ArrayDecoder;
using maxwell::serialization::Encoder;
using maxwell::serialization::Decoder;
using maxwell::SourceId;
using namespace maxwell::repository;


// Convenience functions to encode certain structures.
static void encode(Encoder& enc, SourceId sid) {
	enc(sid.getId());
}

static void encode(Encoder& enc, const Path& path) {
	enc(path.native());
}

static void encode(Encoder& enc, const sha1hash& hash) {
	enc(hash, maxwell::SHA1_DIGEST_SIZE);
}

// Convenience functions to decode certain structures.
static void decode(Decoder& dec, SourceId& sid) {
	uint32_t id;
	dec(id);
	sid = SourceId(id);
}

static void decode(Decoder& dec, Path& path) {
	std::string str;
	dec(str);
	path = str;
}

static void decode(Decoder& dec, sha1hash& hash) {
	Byte digest[maxwell::SHA1_DIGEST_SIZE];
	dec(digest, sizeof(digest));
	hash = sha1hash(digest);
}


/// Creates a new file-based source repository that maintains the given \a dir.
/// Make sure the repository is the sole user of the given directory, as files
/// are added and removed frequently, potentially removing files created by
/// someone else.
FileSourceRepository::FileSourceRepository(const Directory& dir):
	dir(dir),
	needsFlush(false),
	needsPurge(false) {

	// Load the index file if it exists.
	File& index = dir.getFile("index");
	if (index.exists()) {
		std::vector<Byte> indexData;
		index.read(indexData);
		ArrayDecoder indexDecoder(&indexData[0], indexData.size());
		Decoder& dec = indexDecoder;

		while (dec.remaining()) {
			std::unique_ptr<FileSource> src(new FileSource);
			decode(dec, src->id);
			decode(dec, src->path);
			decode(dec, src->hash);
			src->pathHash = sha1(src->path.c_str());

			sourcesByPath[src->path] = src.get();
			sourcesByPathHash[src->pathHash] = src.get();
			sourcesById[src->id] = std::move(src);
		}
	}
}

/// Destructs the repository. If the needsFlush flag is set, flush() is called.
/// If the needsPurge flag is set, purge() is called.
FileSourceRepository::~FileSourceRepository() {
	if (needsFlush)
		flush();
	if (needsPurge)
		purge();
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

	// If the path is already present in the repository, update the file's hash.
	auto it = sourcesByPath.find(path);
	if (it != sourcesByPath.end()) {
		if (it->second->hash == hash)
			return false;
		it->second->hash = hash;
	}

	// Otherwise, allocate a new source ID and create a new file entry.
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
		sourcesByPathHash[src->pathHash] = src.get();
		sourcesById[src->id] = std::move(src);
	}

	// In any case, if we've made it this far, the file needs to be copied into
	// the repository's directory.
	File& dst = dir.getFile(pathHash.lhex());
	dst.write(data);

	needsFlush = true;
	return true;
}

bool FileSourceRepository::remove(SourceId sid) {
	auto it = sourcesById.find(sid);
	if (it == sourcesById.end())
		return false;

	sourcesByPath.erase(it->second->path);
	sourcesByPathHash.erase(it->second->pathHash);
	sourcesById.erase(it);
	needsFlush = true;
	needsPurge = true;
	return true;
}

bool FileSourceRepository::remove(const Path& path) {
	auto it = sourcesByPath.find(path);
	if (it == sourcesByPath.end())
		return false;

	sourcesByPathHash.erase(it->second->pathHash);
	sourcesById.erase(it->second->id); // it->second is now invalid
	sourcesByPath.erase(it);
	needsFlush = true;
	needsPurge = true;
	return true;
}

void FileSourceRepository::removeAll() {
	sourcesById.clear();
	sourcesByPath.clear();
	sourcesByPathHash.clear();
	needsFlush = true;
	needsPurge = true;
}


SourceId FileSourceRepository::getSourceId(const Path& path) const {
	auto it = sourcesByPath.find(path);
	return it != sourcesByPath.end() ? it->second->id : SourceId();
}

Path FileSourceRepository::getPath(SourceId sid) const {
	auto it = sourcesById.find(sid);
	return it != sourcesById.end() ? it->second->path : Path();
}


Source* FileSourceRepository::getSource(SourceId sid) const {
	auto it = sourcesById.find(sid);
	return it != sourcesById.end() ? it->second.get() : nullptr;
}

Source* FileSourceRepository::getSource(const Path& path) const {
	auto it = sourcesByPath.find(path);
	return it != sourcesByPath.end() ? it->second : nullptr;
}


void FileSourceRepository::eachSource(
	std::function<void(const Source&)> fn) const {
	for (auto& src : sourcesById) {
		fn(*src.second);
	}
}


/// Serializes the file index and stores it to the directory.
void FileSourceRepository::flush() const {

	// Serialize the index.
	std::vector<Byte> index;
	index.reserve(4*1024); // pre-allocate storage for speed
	VectorEncoder indexEncoder(index);
	Encoder& enc = indexEncoder; // enables use of templates in Encoder

	for (auto& pair : sourcesById) {
		auto& src = pair.second;
		encode(enc, src->getId());
		encode(enc, src->getPath());
		encode(enc, src->getHash());
	}

	// Store the serialized data to disk.
	needsFlush = false;
	File& indexFile = dir.getFile("index");
	indexFile.write(index);
}

/// Removes all obsolete files from the directory. A file is obsolete if it is
/// not the index file, and its name is not listed in the index as the path hash
/// of one of the source files. Does not touch invisible files.
void FileSourceRepository::purge() const {
	needsPurge = false;
	dir.eachFile([&](File& f){
		auto name = f.getName();
		if (name == "index" || name[0] == '.')
			return;

		sha1hash hash;
		if (!sha1hash::fromhex(name, hash) || !sourcesByPathHash.count(hash)) {
			f.unlink();
		}
	});
}
