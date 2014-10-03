/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/mwc/SourceTool.hpp"
using namespace maxwell::mwc;

static bool stroneof(const char* a, const char* b0, const char* b1) {
	return strcmp(a,b0) == 0 || strcmp(a,b1) == 0;
}

bool SourceTool::run() {

	if (argc > 0 && stroneof(*argv, "-r", "--repo")) {
		--argc; ++argv;
		if (argc > 0) {
			out << "setting repo to " << *argv;
			--argc; ++argv;
		} else {
			err << "expected repository path after -r/--repo\n";
			return false;
		}
	}

	if (argc > 0) {
		if (strcmp(*argv, "add") == 0) {

		} else if (strcmp(*argv, "remove") == 0) {

		} else if (strcmp(*argv, "list") == 0) {

		} else {
			err << "unknown command '" << *argv << "'\n";
			printUsage();
			return false;
		}
	} else {
		printUsage();
		return false;
	}

	return true;
}

void SourceTool::printUsage() {
	err << "usage: mwc-src [-r|--repo <repo>] add <path>...\n";
	err << "   or: mwc-src [-r|--repo <repo>] remove <path>...\n";
	err << "   or: mwc-src [-r|--repo <repo>] list\n";
}
