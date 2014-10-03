/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/mwc/Tool.hpp"
#include <iostream>
#include <stdexcept>

using namespace maxwell::mwc;

Tool::Tool():
	in(std::cin),
	out(std::cout),
	err(std::cerr) {}

Tool::Tool(std::istream& in, std::ostream& out, std::ostream& err):
	in(in),
	out(out),
	err(err) {}

int Tool::main(int argc, char** argv) {
	try {
		this->argc = argc-1;
		this->argv = argv+1;
		return run() ? 0 : 1;
	} catch (std::exception& e) {
		err << e.what() << '\n';
		return -1;
	}
}
