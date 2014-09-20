/* Coypright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem.hpp"
#include <map>
#include <memory>
// #include "maxwell/repository/SourceIndexInterface.hpp"

namespace maxwell {
namespace repository {

class SourceInfo;

/// An index that assigns IDs to source files. Also keeps track of their paths.
class SourceIndex {
	File& file;

	std::map<uint32_t, std::unique_ptr<SourceInfo>> byId;
	std::map<Path, SourceInfo*> byPath;
	bool modified;

	void read(const std::vector<Byte>& input);
	void write(std::vector<Byte>& output);

public:
	SourceIndex(File& file);
	~SourceIndex();

	bool add(const Path& path);
	bool remove(const Path& path);

	void flush();
};

} // namespace repository
} // namespace maxwell
