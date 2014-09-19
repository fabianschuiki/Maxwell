/* Copyright (c) 2014 Fabian Schuiki */
#pragma once

namespace maxwell {
namespace mwc {

/// Base class for all command line tools. Parses the arguments and prepares
/// some default setup before calling the subclass' main code. Use the TOOL_MAIN
/// macro to generate the appropriate main function.
class Tool {
	int const argc;
	char** const argv;

protected:
	virtual void run() = 0;

public:
	Tool(int argc, char** argv): argc(argc), argv(argv) {}

	void main() {

	}
};

} // namespace mwc
} // namespace maxwell

#define MWC_TOOL_MAIN(classname) int main(int argc, char** argv) {\
	return classname(argc, argv).main();\
}
