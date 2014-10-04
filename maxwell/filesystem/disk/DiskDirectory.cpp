/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/filesystem/disk/DiskDirectory.hpp"
using namespace maxwell::filesystem;


bool DiskDirectory::exists() const {
	return boost::filesystem::exists(path);
}

void DiskDirectory::unlink() const {
	boost::filesystem::remove_all(path);
}


File& DiskDirectory::getFile(const std::string& name) const {
	auto it = fileCache.find(name);
	if (it != fileCache.end())
		return it->second;
	auto r = fileCache.insert(std::make_pair(name, DiskFile(path/name)));
	return r.first->second;
}

Directory& DiskDirectory::getDirectory(const std::string& name) const {
	auto it = directoryCache.find(name);
	if (it != directoryCache.end())
		return it->second;
	auto r = directoryCache.insert(
		std::make_pair(name, DiskDirectory(path/name)));
	return r.first->second;
}


void DiskDirectory::eachFile(std::function<void(File&)> fn) const {
	boost::filesystem::directory_iterator it(path), end;
	for (; it != end; ++it) {
		if (boost::filesystem::is_regular_file(*it)) {
			DiskFile f(*it);
			fn(f);
		}
	}
}

void DiskDirectory::eachDirectory(std::function<void(Directory&)> fn) const {
	boost::filesystem::directory_iterator it(path), end;
	for (; it != end; ++it) {
		if (boost::filesystem::is_directory(*it)) {
			DiskDirectory d(*it);
			fn(d);
		}
	}
}
