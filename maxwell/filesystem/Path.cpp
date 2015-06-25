/* Copyright (c) 2014-2015 Fabian Schuiki */
#include "maxwell/filesystem/Path.hpp"

namespace maxwell {
namespace filesystem {


/// Returns the given \a path relative to \a base. Both paths must be absolute.
Path relativePath(const Path& path, const Path& base) {
	assert(path.is_absolute());
	assert(base.is_absolute());
	Path result;
	auto pb = path.begin(), pe = path.end();
	auto bb = base.begin(), be = base.end();
	while (pb != pe && bb != be && *pb == *bb) {
		++pb;
		++bb;
	}
	while (bb != be) {
		result /= "../";
		++bb;
	}
	while (pb != pe) {
		result /= *pb;
		++pb;
	}
	return result;
}


/// Returns a normalized version of the given \a path. Normalization entails the
/// following modifications:
///
/// - links to the current directory (`./`) are removed
/// - links to the parent directory (`../`) are resolved
/// - empty segments (`//`) are removed
/// - trailing slashes (`src/`) are removed
///
/// \return Returns the path without `./`, double slashes and trailing slashes,
/// and `../` only at the beginning of the path if it cannot be avoided.
Path normalizePath(const Path& path) {
	Path result;
	for (auto p : path) {
		if (p == ".")
			continue;
		if (p == ".." && !result.empty() && result.filename() != p) {
			if (result.filename() == "/")
				result = "../";
			else
				result = result.parent_path();
		} else {
			result /= p;
		}
	}
	return result;
}


/// Prepends \a base to \a path if the latter is relative. Does nothing if
/// \a path is already absolute.
Path absolutePath(const Path& path, const Path& base) {
	return path.is_absolute() ? path : base/path;
}


} // namespace filesystem
} // namespace maxwell
