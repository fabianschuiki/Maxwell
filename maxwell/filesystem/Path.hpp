/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <boost/filesystem.hpp>

namespace maxwell {
namespace filesystem {

typedef boost::filesystem::path Path;

Path relativePath(const Path& path, const Path& base);
Path normalizePath(const Path& path);

} // namespace filesystem
} // namespace maxwell
