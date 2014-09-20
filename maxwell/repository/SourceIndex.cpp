/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/repository/SourceIndex.hpp"
#include "maxwell/repository/SourceInfo.hpp"
#include "maxwell/serialization/VectorEncoder.hpp"
using namespace maxwell::repository;
using maxwell::serialization::Encoder;
using maxwell::serialization::VectorEncoder;


SourceIndex::SourceIndex(File& file): file(file) {
	modified = false;
	std::vector<Byte> data;
	file.read(data);
	read(data);
}

SourceIndex::~SourceIndex() {
	if (modified)
		flush();
}

/// Adds the \a path to the source index.
/// \return Returns true if the path was added, false if it was already present.
bool SourceIndex::add(const Path& path) {

	auto existing = byPath.find(path);
	if (existing != byPath.end())
		return false;

	uint32_t id = 1;
	if (!byId.empty()) {
		id = byId.rbegin()->first + 1;
	}

	auto info = std::unique_ptr<SourceInfo>(new SourceInfo(
		id, path, "<nohash>"));
	byPath[path] = info.get();
	byId[id] = std::move(info);

	modified = true;
	return true;
}

/// Removes the \a path from the source index.
/// \return Returns true if the path was found and removed, false if it was not
/// part of the index to begin with.
bool SourceIndex::remove(const Path& path) {

	auto existing = byPath.find(path);
	if (existing == byPath.end())
		return false;

	SourceInfo *info = existing->second;
	byPath.erase(existing);
	byId.erase(info->getId());

	modified = true;
	return true;
}

/// Writes the index to disk. You should rarely have to call this function
/// directly, since the destructor of SourceIndex makes sure that it is flushed
/// to disk eventually.
void SourceIndex::flush() {
	std::vector<Byte> data;
	write(data);
	file.write(data);
	modified = false;
}

/// Reads the source index from the given \a input, which is expected to be a
/// binary serialized version.
void SourceIndex::read(const std::vector<Byte>& input) {

}

/// Writes the source index to the given \a output.
void SourceIndex::write(std::vector<Byte>& output) {
	VectorEncoder venc(output);
	Encoder& enc = venc;

	for (auto i = byId.begin(); i != byId.end(); i++) {
		const auto& v = i->second;
		enc(v->getId());
		enc(v->getPath().native());
		enc(v->getHash());
	}
}
