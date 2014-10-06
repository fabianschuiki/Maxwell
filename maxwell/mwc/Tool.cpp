/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/mwc/Tool.hpp"
#include <iostream>
#include <stdexcept>

using namespace maxwell::mwc;

Tool::Tool(const Path& pwd):
	in(std::cin),
	out(std::cout),
	err(std::cerr),
	currentPath(pwd) {}

Tool::Tool(
	std::istream& in,
	std::ostream& out,
	std::ostream& err,
	const Path& pwd):
	in(in),
	out(out),
	err(err),
	currentPath(pwd) {}

int Tool::main(int argc, char** argv) {
	try {
		this->argc = argc-1;
		this->argv = argv+1;

		// Print the tool help if requested.
		if (this->argc > 0 && (
			strcmp(*this->argv, "-h") == 0 ||
			strcmp(*this->argv, "--help") == 0)) {
			printHelp();
			return 0;
		}

		// Print the tool version if requested.
		if (this->argc > 0 && strcmp(*this->argv, "--version") == 0) {
			printVersion();
			return 0;
		}

		return run() ? 0 : 1;
	} catch (std::exception& e) {
		err << e.what() << '\n';
		return -1;
	}
}

void Tool::printHelp() {
	printUsage();
}
