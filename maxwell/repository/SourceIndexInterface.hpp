/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem.hpp"
#include "maxwell/repository/SourceInfoInterface.hpp"

namespace maxwell {
namespace repository {

class SourceIndexInterface {
public:
	virtual const SourceInfoInterface& addFile(const Path& path) = 0;
	virtual bool removeFile(const Path& path) = 0;
};

} // namespace repository
} // namespace maxwell
