/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <boost/filesystem.hpp>

namespace maxwell {

namespace filesystem = boost::filesystem;
typedef boost::filesystem::path Path;


/// An abstract interface for a file resource. Most likely implemented by a disk
/// file class and a mock file class.
class File {
public:
	virtual std::istream getInputStream() = 0;
	virtual std::ostream getOutputStream() = 0;
};


/// An abstract interface for a directory of resources. Most likely implemented
/// by a disk directory class and a mock directory class.
class Directory {
public:
	// \todo Add functions that query the directory contents.
};

} // namespace maxwell
