/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem.hpp"

namespace maxwell {
namespace repository {

class SourceRepositoryInterface {
public:
	virtual const Path& getPath() const = 0;

	virtual bool addFile(const Path& path) = 0;
	virtual bool removeFile(const Path& path) = 0;
};

} // namespace repository
} // namespace maxwell
