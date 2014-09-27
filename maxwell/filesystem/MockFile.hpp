/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/File.hpp"

namespace maxwell {
namespace filesystem {

/// A virtual file useful during testing.
class MockFile : public File {
	Path path;

public:
	std::vector<Byte> content;
	bool fexists;

	MockFile(const Path& path): path(path), fexists(false) {}
	~MockFile() {}

	const Path& getPath() const { return path; }

	void read(std::vector<Byte>& dst) const {
		dst = content;
	}

	void write(const Buffer<const Byte>& src) {
		content.assign(src.getStart(), src.getEnd());
		fexists = true;
	}

	bool exists() const { return fexists; }
};

} // namespace filesystem
} // namespace maxwell
