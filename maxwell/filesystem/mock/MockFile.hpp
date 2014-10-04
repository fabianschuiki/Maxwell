/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/File.hpp"

namespace maxwell {
namespace filesystem {

/// A virtual file useful during testing.
class MockFile : public File {
	Path path;

public:
	mutable std::vector<Byte> content;
	mutable bool fexists;
	mutable time_t modified;

	MockFile(const Path& path): path(path), fexists(false), modified(0) {}
	~MockFile() {}

	const Path& getPath() const { return path; }
	void unlink() const { fexists = false; }

	void read(std::vector<Byte>& dst) const {
		dst = content;
	}

	void write(const Buffer<const Byte>& src) {
		content.assign(src.getStart(), src.getEnd());
		fexists = true;
		modified = time(NULL);
	}

	bool exists() const { return fexists; }
	time_t getModificationTime() const { return modified; }
};

} // namespace filesystem
} // namespace maxwell
