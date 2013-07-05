/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <boost/smart_ptr.hpp>
#include <boost/filesystem.hpp>

namespace ast {

using std::shared_ptr;

/**
 * The Repository represents a persistent store on disk that holds AST nodes.
 */
class Repository
{
public:
	const boost::filesystem::path path;
	Repository(const boost::filesystem::path& path);
};

}