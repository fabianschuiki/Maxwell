/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem.hpp"
#include <sstream>

namespace maxwell {

class MockFile : public File {
	Path path;
	std::stringstream stream;

public:
	MockFile(const Path& path): path(path) {}
	~MockFile() {}

	std::istream& getInputStream() { return stream; }
	std::ostream& getOutputStream() { return stream; }
};

} // namespace maxwell
