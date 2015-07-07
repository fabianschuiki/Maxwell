/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/repository/file/FileSource.hpp"
#include "maxwell/repository/file/FileSourceRepository.hpp"
#include "maxwell/repository/Source.hpp"
#include "maxwell/serialization/VectorEncoder.hpp"
#include "maxwell/serialization/ArrayDecoder.hpp"

using maxwell::sha1;
using maxwell::sha1hash;
using maxwell::filesystem::Path;
using maxwell::filesystem::File;
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


/// Checks whether the given \a path and \a file differ from the given source
/// file \a src. If the file is detected to be modified, the function returns
/// true and sets \a mod to the file's modification date, \a hash to the file's
/// content hash, \a pathHash to the hash of the file's path, and \a data to the
/// contents of the file. \a src may be \c nullptr, in which case the function
/// always returns true.
static bool checkModified(
	FileSource* src,
	const Path& path,
	const File& file,
	time_t& mod,
	sha1hash& hash,
	sha1hash& pathHash,
	std::vector<Byte>& data) {

	// Check whether the modification time differs.
	mod = file.getModificationTime();
	if (src && src->getModificationTime() >= mod) {
		return false;
	}

	// Calculate the hash of the file.
	data.clear();
	file.read(data);

	sha1 base;
	base.update(path.c_str());
	pathHash = sha1(base);
	hash = base.update(&data[0], data.size());

	// If the path is already present in the repository, update the file's hash.
	if (src && src->getHash() == hash) {
		return false;
	}

	return true;
}


/// Creates a new file-based source repository that maintains the given \a dir.
/// Make sure the repository is the sole user of the given directory, as files
/// are added and removed frequently, potentially removing files created by
/// someone else.
FileSourceRepository::FileSourceRepository(const Directory& dir):
	dir(dir),
	needsFlush(false),
	needsPurge(false) {

	// Make sure the directory exists.
	dir.make();

	// Load the index file if it exists.
	File& index = dir.getFile("index");
	if (index.exists()) {
		try {
			std::vector<Byte> indexData;
			index.read(indexData);
			ArrayDecoder indexDecoder(&indexData[0], indexData.size());
			Decoder& dec = indexDecoder;
			uint16_t version;
			dec(version);

			while (dec.remaining()) {
				auto src = make_unique<FileSource>(*this);
				decode(dec, src->id);
				decode(dec, src->path);
				decode(dec, src->hash);
				dec(src->modificationTime);
				src->pathHash = sha1(src->path.c_str());

				sourcesByPath[src->path] = src.get();
				sourcesByPathHash[src->pathHash] = src.get();
				sourcesById[src->id] = std::move(src);
			}
		} catch (std::exception &e) {
			sourcesById.clear();
			sourcesByPath.clear();
			sourcesByPathHash.clear();

			throw std::runtime_error("corrupted source index "
				+ index.getPath().native());
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

	// Find any existing records of the file and check whether it has been
	// modified. mod, data, pathHash and hash are filled in the process and are
	// valid if checkModified() returns true.
	auto it = sourcesByPath.find(path);
	FileSource* src = (it != sourcesByPath.end() ? it->second : nullptr);
	time_t mod;
	std::vector<Byte> data;
	sha1hash pathHash, hash;

	if (!checkModified(src, path, file, mod, hash, pathHash, data))
		return false;

	// If a record already existed, simply update the file's hash and
	// modification time.
	if (src) {
		src->hash = hash;
		src->modificationTime = mod;
	}

	// Otherwise, allocate a new source ID and create a new file entry.
	else {
		// Allocate the next SourceId.
		SourceId sid(sourcesById.empty() ? 1 :
			sourcesById.rbegin()->first.getId() + 1);

		// Create a new file entry.
		auto src = make_unique<FileSource>(*this);
		src->id = sid;
		src->path = path;
		src->pathHash = pathHash;
		src->hash = hash;
		src->modificationTime = mod;

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
	auto copy = sourcesByPath; // make a copy in case fn modifies things
	for (auto& src : copy) {
		fn(*src.second);
	}
}


bool FileSourceRepository::isModified(
	const Path& path,
	const File& file) const {

	auto it = sourcesByPath.find(path);
	if (it == sourcesByPath.end())
		return true;

	time_t mod;
	std::vector<Byte> data;
	sha1hash pathHash, hash;

	return checkModified(it->second, path, file, mod, hash, pathHash, data);
}

bool FileSourceRepository::isModified(
	SourceId sid,
	const File& file) const {

	auto it = sourcesById.find(sid);
	if (it == sourcesById.end())
		return true;

	time_t mod;
	std::vector<Byte> data;
	sha1hash pathHash, hash;

	return checkModified(it->second.get(), it->second->getPath(),
		file, mod, hash, pathHash, data);
}


/// Serializes the file index and stores it to the directory.
void FileSourceRepository::flush() const {

	// Serialize the index.
	std::vector<Byte> index;
	index.reserve(4*1024); // pre-allocate storage for speed
	VectorEncoder indexEncoder(index);
	Encoder& enc = indexEncoder; // enables use of templates in Encoder
	const uint16_t version = 2;
	enc(version);

	for (auto& pair : sourcesById) {
		auto& src = pair.second;
		encode(enc, src->id);
		encode(enc, src->path);
		encode(enc, src->hash);
		enc(src->modificationTime);
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
