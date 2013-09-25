/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <boost/filesystem.hpp>

namespace backend {
namespace c {

/**
 * The main umbrella repository containing all the files associated with the
 * C backend of the Maxwell compiler.
 */
class Repository
{
public:
	const boost::filesystem::path path;
	Repository(const boost::filesystem::path& path);

protected:
};

} // namespace c
} // namespace backend