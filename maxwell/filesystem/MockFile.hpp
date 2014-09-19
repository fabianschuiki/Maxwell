/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/Buffer.hpp"
#include "maxwell/filesystem.hpp"
#include <sstream>

namespace maxwell {

/// A virtual file useful during testing.
class MockFile : public File {
	Path path;
	std::vector<Byte> content;

public:
	MockFile(const Path& path): path(path) {}
	MockFile(const Path& path, const Buffer<const Byte>& content): path(path) {
		this->content.resize(content.getLength());
		std::copy(content.getStart(), content.getEnd(), this->content.begin());
	}
	~MockFile() {}

	const Path& getPath() const { return path; }
	Buffer<const Byte> getContent() const {
		return Buffer<const Byte>(&content[0], &content[0] + content.size());
	}

	void read(std::vector<Byte>& dst) {
		dst = content;
	}

	void write(const Buffer<const Byte>& src) {
		content.assign(src.getStart(), src.getEnd());
	}
};

} // namespace maxwell
