/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem.hpp"

namespace maxwell {

class MockFile : public File {
public:
	MockFile() {}
	~MockFile() {}

	std::istream getInputStream() {}
	std::ostream getOutputStream() {}
};

} // namespace maxwell
