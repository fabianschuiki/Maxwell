/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <istream>
#include <ostream>

namespace maxwell {
namespace mwc {

/// Base class for all command line tools. Parses the arguments and prepares
/// some default setup before calling the subclass' main code. Use the TOOL_MAIN
/// macro to generate the appropriate main function.
class Tool {
protected:
	std::istream& in;
	std::ostream& out;
	std::ostream& err;

	int argc;
	char** argv;

	/// Concrete tools implement their functionality in this function. Called
	/// from the main() function of the Tool.
	virtual bool run() = 0;

public:
	Tool();
	Tool(std::istream& in, std::ostream& out, std::ostream& err);

	int main(int argc, char** argv);
};

} // namespace mwc
} // namespace maxwell
