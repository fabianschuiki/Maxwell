/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "maxwell/filesystem/Path.hpp"
#include <istream>
#include <ostream>

namespace maxwell {
namespace mwc {

/// Base class for all command line tools. Parses the arguments and prepares
/// some default setup before calling the subclass' main code. Use the TOOL_MAIN
/// macro to generate the appropriate main function.
class Tool {
public:
	typedef maxwell::filesystem::Path Path;

protected:
	std::istream& in;
	std::ostream& out;
	std::ostream& err;
	const Path currentPath;

	int argc;
	char** argv;

	/// Concrete tools implement their functionality in this function. Called
	/// from the main() function of the Tool.
	virtual bool run() = 0;

	virtual void printUsage() = 0;
	virtual void printHelp();
	virtual void printVersion() = 0;

public:
	Tool(const Path& pwd = boost::filesystem::current_path());
	Tool(std::istream& in, std::ostream& out, std::ostream& err,
		const Path& pwd = boost::filesystem::current_path());

	int main(int argc, char** argv);
};

} // namespace mwc
} // namespace maxwell
