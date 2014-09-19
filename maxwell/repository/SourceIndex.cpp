/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/repository/SourceIndex.hpp"
#include "maxwell/repository/SourceInfo.hpp"
using namespace maxwell::repository;


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

bool SourceIndex::add(const Path& path) {

	auto existing = byPath.find(path);
	if (existing != byPath.end())
		return false;

	unsigned id = 1;
	if (!byId.empty()) {
		id = byId.rbegin()->first + 1;
	}

	const auto& info = byId.emplace(id, std::unique_ptr<SourceInfo>(
		new SourceInfo(id, path, "<nohash>")));
	byPath.emplace(path, info.first->second.get());

	modified = true;
	return true;
}

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

void SourceIndex::flush() {
	std::vector<Byte> data;
	write(data);
	file.write(data);
	modified = false;
}


void SourceIndex::read(const std::vector<Byte>& input) {

}

void SourceIndex::write(std::vector<Byte>& output) {
	const char* crappy = "Hello World";
	output.insert(output.end(), crappy, crappy + strlen(crappy));
}
