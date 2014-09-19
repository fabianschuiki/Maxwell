/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/Buffer.hpp"
#include "maxwell/types.hpp"
#include <boost/filesystem.hpp>

namespace maxwell {

typedef boost::filesystem::path Path;


/// An abstract interface for a file resource. Most likely implemented by a disk
/// file class and a mock file class.
class File {
public:
	virtual const Path& getPath() const = 0;

	virtual void read(std::vector<Byte>& dst) = 0;
	virtual void write(const Buffer<const Byte>& src) = 0;
	virtual void write(const std::vector<Byte>& src) {
		write(Buffer<const Byte>(&src[0], &src[0] + src.size()));
	}
};


/// An abstract interface for a directory of resources. Most likely implemented
/// by a disk directory class and a mock directory class.
class Directory {
public:
	// \todo Add functions that query the directory contents.
};

} // namespace maxwell
