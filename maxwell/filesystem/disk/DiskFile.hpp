/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/File.hpp"

namespace maxwell {
namespace filesystem {

/// A file on disk.
class DiskFile : public File {
	const Path path;

public:
	DiskFile(const Path& path): path(path) {}

	const Path& getPath() const { return path; }
	bool exists() const;
	void unlink() const;

	void read(std::vector<Byte>& dst) const;
	void write(const Buffer<const Byte>& src);
	time_t getModificationTime() const;
};

} // namespace filesystem
} // namespace maxwell
