/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem.hpp"
#include "maxwell/repository/SourceInfoInterface.hpp"

namespace maxwell {
namespace repository {

class SourceIndexInterface {
public:
	virtual bool addFile(const File& file) = 0;
	virtual bool removeFile(const File& file) = 0;
};

} // namespace repository
} // namespace maxwell
