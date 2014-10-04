/* Copyright (c) 2014 Fabian Schuiki */
#include "maxwell/filesystem/disk/DiskDirectory.hpp"
#include "maxwell/filesystem/disk/DiskFile.hpp"
#include "maxwell/filesystem/Path.hpp"
#include "maxwell/mwc/SourceTool.hpp"
#include "maxwell/repository/file/FileSourceRepository.hpp"
#include <cstring>
#include <iostream>
using maxwell::filesystem::DiskDirectory;
using maxwell::filesystem::DiskFile;
using maxwell::filesystem::normalizePath;
using maxwell::filesystem::Path;
using maxwell::filesystem::relativePath;
using maxwell::repository::FileSourceRepository;
using maxwell::repository::Source;
using namespace maxwell::mwc;

static bool stroneof(const char* a, const char* b0, const char* b1) {
	return strcmp(a,b0) == 0 || strcmp(a,b1) == 0;
}

bool SourceTool::run() {

	bool supportColor = true;
	const char* COLOR_CLEAR = supportColor ? "\033[0m" : "";
	const char* COLOR_RED   = supportColor ? "\033[31m" : "";
	const char* COLOR_GREEN = supportColor ? "\033[32m" : "";

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
	auto repoDir = repo.parent_path();

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

			// Check the verbosity flag.
			bool verbose = false;
			if (argc > 0 && stroneof(*argv, "-v", "--verbose")) {
				--argc; ++argv;
				verbose = true;
			}

			// Show a note if the user did not provide any arguments.
			if (argc == 0) {
				err << "Nothing specified, nothing added.\n";
				err << "Maybe you wanted to say 'mwc-src add .'?\n";
				return false;
			}

			// Process the arguments.
			for (; argc > 0; argc--, argv++) {
				Path path = normalizePath(currentPath/(*argv));

				// Add entire directories.
				if (boost::filesystem::is_directory(path)) {
					boost::filesystem::recursive_directory_iterator
						it(path), end;
					for (; it != end; ++it) {
						Path p = *it;
						if (p.extension() != ".mw")
							continue;
						bool added = sourceRepo.add(
							relativePath(p, repoDir),
							DiskFile(p));
						if (verbose && added) {
							out << "added "
								<< relativePath(p, currentPath).native()
								<< '\n';
						}
					}
				}

				// Add individual files.
				else if (boost::filesystem::is_regular_file(path)) {
					Path relative = relativePath(path, repoDir);
					bool added = sourceRepo.add(relative, DiskFile(path));
					if (verbose && added) {
						out << "added "
							<< relativePath(path, currentPath).native()
							<< '\n';
					}
				}

				// Complain about inexistent stuff.
				else {
					err << "skipped " << *argv << " (not found)\n";
					continue;
				}
			}
		}

		else if (strcmp(cmd, "remove") == 0) {
			if (argc == 0) {
				err << "Nothing specified, nothing removed.\n";
				return false;
			}
			if (argc > 0 && strcmp(*argv, "--all") == 0) {
				--argc; ++argv;
				sourceRepo.removeAll();
			} else {
				for (; argc > 0; argc--, argv++) {
					Path path = normalizePath(currentPath/(*argv));
					Path relative = relativePath(path, repoDir);
					if (!sourceRepo.remove(relative))
						err << "skipped " << *argv << " (not in repository)\n";
				}
			}
		}

		else if (strcmp(cmd, "list") == 0) {
			sourceRepo.eachSource([&](const Source& src){
				auto p = normalizePath(repoDir/src.getPath());
				out << relativePath(p, currentPath).native() << '\n';
			});
		}

		else if (strcmp(cmd, "status") == 0) {
			sourceRepo.eachSource([&](const Source& src){
				auto p = normalizePath(repoDir/src.getPath());
				if (boost::filesystem::is_regular_file(p)) {
					if (sourceRepo.isModified(src.getPath(), DiskFile(p))) {
						out << "modified: "
							<< relativePath(p, currentPath).native()
							<< '\n';
					}
				} else {
					out << "deleted:  "
						<< relativePath(p, currentPath).native() << '\n';
				}
			});
		}

		else if (strcmp(cmd, "update") == 0) {
			bool verbose = false;
			if (argc > 0 && stroneof(*argv, "-v", "--verbose")) {
				--argc; ++argv;
				verbose = true;
			}
			sourceRepo.eachSource([&](const Source& src){
				auto p = normalizePath(repoDir/src.getPath());
				if (boost::filesystem::is_regular_file(p)) {
					bool added = sourceRepo.add(src.getPath(), DiskFile(p));
					if (verbose && added) {
						out << "updated "
							<< relativePath(p,currentPath).native() << '\n';
					}
				} else {
					bool removed = sourceRepo.remove(src.getPath());
					if (verbose && removed) {
						out << "removed "
							<< relativePath(p,currentPath).native() << '\n';
					}
				}
			});
		}

		else {
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
	err << "usage: mwc-src [-r|--repo <repo>] add [-v|--verbose] <path>...\n";
	err << "   or: mwc-src [-r|--repo <repo>] remove [--all] <path>...\n";
	err << "   or: mwc-src [-r|--repo <repo>] list\n";
	err << "   or: mwc-src [-r|--repo <repo>] status\n";
	err << "   or: mwc-src [-r|--repo <repo>] update [-v|--verbose]\n";
}
