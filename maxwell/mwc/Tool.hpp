/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <iostream>

namespace maxwell {
namespace mwc {

/// Base class for all command line tools. Parses the arguments and prepares
/// some default setup before calling the subclass' main code. Use the TOOL_MAIN
/// macro to generate the appropriate main function.
class Tool {
protected:
	virtual void run() = 0;

public:
	int main(int argc, char** argv) {
		run();
		return 0;
	}
};

} // namespace mwc
} // namespace maxwell

#define MWC_TOOL_MAIN(classname) int main(int argc, char** argv) {\
	return classname(argc, argv).main();\
}
