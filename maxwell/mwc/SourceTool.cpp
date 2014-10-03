/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/filesystem/disk/DiskDirectory.hpp"
#include "maxwell/filesystem/disk/DiskFile.hpp"
#include "maxwell/filesystem/Path.hpp"
#include "maxwell/mwc/SourceTool.hpp"
#include "maxwell/repository/file/FileSourceRepository.hpp"
#include <cstring>
#include <iostream>
using maxwell::filesystem::Path;
using maxwell::filesystem::DiskDirectory;
using maxwell::filesystem::DiskFile;
using maxwell::repository::FileSourceRepository;
using maxwell::repository::Source;
using namespace maxwell::mwc;

static bool stroneof(const char* a, const char* b0, const char* b1) {
	return strcmp(a,b0) == 0 || strcmp(a,b1) == 0;
}

static Path makePathRelative(const Path& path, const Path& base) {
	assert(path.is_absolute());
	assert(base.is_absolute());
	Path result;
	auto pb = path.begin(), pe = path.end();
	auto bb = base.begin(), be = base.end();
	while (pb != pe && bb != be && *pb == *bb) {
		++pb;
		++bb;
	}
	while (bb != be) {
		result /= "../";
		++bb;
	}
	while (pb != pe) {
		result /= *pb;
		++pb;
	}
	return result;
}

bool SourceTool::run() {

	Path repo;
	if (argc > 0 && stroneof(*argv, "-r", "--repo")) {
		--argc; ++argv;
		if (argc > 0) {
			repo = *argv;
			--argc; ++argv;
		} else {
			err << "expected repository path after -r/--repo\n";
			return false;
		}
	}

	// Look for the repo if none was passed as argument.
	if (repo.empty() && currentPath.is_absolute()) {
		auto base = currentPath;
		while (!base.empty()) {
			auto test = base/".mwc";
			if (boost::filesystem::exists(test)) {
				repo = test;
				break;
			} else {
				base = base.parent_path();
			}
		}
	}
	if (repo.empty()) {
		repo = currentPath/".mwc";
	}

	// Setup the source repository.
	Path sourceRepoPath = repo/"sources";
	if (!boost::filesystem::exists(sourceRepoPath)) {
		boost::filesystem::create_directories(sourceRepoPath);
	} else if (!boost::filesystem::is_directory(sourceRepoPath)) {
		err << sourceRepoPath.native() << " exists but is not a directory\n";
		return false;
	}
	DiskDirectory sourceRepoDir(sourceRepoPath);
	FileSourceRepository sourceRepo(sourceRepoDir);

	// Execute the commands.
	if (argc > 0) {
		const char* cmd = *argv;
		argc--; argv++;
		if (strcmp(cmd, "add") == 0) {
			for (; argc > 0; argc--, argv++) {
				Path path = currentPath/(*argv);
				if (!boost::filesystem::is_regular_file(path)) {
					err << "skipping " << *argv << " (not a file)\n";
					continue;
				}
				Path relative = makePathRelative(
					boost::filesystem::canonical(path),
					repo.parent_path());
				sourceRepo.add(relative, DiskFile(path));
			}
		} else if (strcmp(cmd, "remove") == 0) {

		} else if (strcmp(cmd, "list") == 0) {
			sourceRepo.eachSource([&](const Source& src){
				auto p = boost::filesystem::canonical(
					repo.parent_path()/src.getPath());
				out << makePathRelative(p, currentPath).native() << '\n';
			});
		} else {
			err << "unknown command '" << cmd << "'\n";
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
