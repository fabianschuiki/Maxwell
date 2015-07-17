/* Copyright (c) 2013-2015 Fabian Schuiki */
#include "maxwell/ast/Repository.hpp"
#include "maxwell/console.hpp"
#include "maxwell/diagnostic/ConsoleDiagnosticPrinter.hpp"
#include "maxwell/diagnostic/diagnostic.hpp"
#include "maxwell/filesystem/disk/DiskDirectory.hpp"
#include "maxwell/filesystem/disk/DiskFile.hpp"
#include "maxwell/repository/file/FileSourceRepository.hpp"
#include "maxwell/stage/StageManager.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/// \file
/// This program operates on the local repository and performs processing
/// stages on the stored nodes individually.

using std::string;
using std::cout;
using std::cerr;
using ast::Repository;
using ast::NodeId;
using ast::NodePtr;
using std::vector;
using stage::StageManager;
using stage::Stage;
using namespace maxwell;
using namespace maxwell::filesystem;

int main(int argc, char *argv[]) {
	console::init();

	try {
		Repository repo("mwcrepo");
		StageManager mgr(repo);
		boost::filesystem::create_directory("mwcrepo/mwc");
		DiskDirectory repoDir("mwcrepo/mwc/sources");
		repository::FileSourceRepository sourceRepo(repoDir);
		DiagnosticContext diagCtx;

		for (auto& s : mgr.stages)
			s->setDiagnosticContext(&diagCtx);
		// mgr.stagesByName["CalcActualTypes"]->verbosity = 99;

		// Read the ids from the input.
		vector<NodeId> ids;
		for (int i = 1; i < argc; i++) {
			ids.push_back(NodeId(string(argv[i])));
		}

		// int prevStage = -1;
		// int prevId = -1;
		bool failed = false;
		unsigned sentinel = 0;
		while (!failed && !diagCtx.isError()) {
			if (sentinel++ > 50 * ids.size()) // abort if >50 stage iterations were performed PER NODE
				throw std::runtime_error("Excessive amount of stage iterations. Aborting.");

			// Find the next stage to be processed.
			int nextStage = -1;
			int nextId = -1;
			for (unsigned i = 0; i < mgr.stages.size() && nextStage < 0; i++) {
				for (unsigned n = 0; n < ids.size() && nextStage < 0; n++) {
					if (!repo.isFlagSet(ids[n], mgr.stages[i]->getId())) {
						nextStage = i;
						nextId = n;
					}
				}
			}

			// Execute the stage.
			if (nextStage >= 0 && nextId >= 0) {
				Stage& st = *mgr.stages[nextStage];
				const NodeId& id = ids[nextId];
				try {
					// Indicate stage backtracking.
					// if (prevStage > nextStage || (prevStage == nextStage && prevId > nextId)) {
					// 	cout << "Backtracking to \033[35;1m" << st.getName() << "\033[0m on " << id << "\n";
					// }
					// cout << "Performing \033[36;1m" << st.getName() << "\033[0m on " << id << "\n";

					// auto d = make_unique<Diagnostic>();
					// auto msg = make_unique<DiagnosticMessage>(kInfo,
					// 	"Compiling this thing " + id.str());
					// msg->setMainRange(repo.getNode(id)->getReferenceRange());
					// d->add(std::move(msg));
					// diagCtx.add(std::move(d));

					// Perform operation and mark the stage as processed for this node.
					st.run(id);
					repo.addFlag(id, st.getId()); // flag this stage as processed

				} catch (std::exception &e) {
					auto d = make_unique<Diagnostic>();
					auto msg = make_unique<DiagnosticMessage>(kFatal,
						"Exeption occurred in compilation stage " + st.getName()
						+ "; " + e.what());
					msg->setMainRange(repo.getNode(id)->getReferenceRange());
					d->add(std::move(msg));
					// msg = make_unique<DiagnosticMessage>(kInfo, e.what());
					// d->add(std::move(msg));
					diagCtx.add(std::move(d));
					// failed = true;
				}
			} else {
				break;
			}

			// prevStage = nextStage;
			// prevId = nextId;
		}

		ConsoleDiagnosticPrinter fmt(sourceRepo);
		for (auto const& d : diagCtx.getDiagnostics()) {
			fmt.consume(d);
		}

		if (diagCtx.isError())
			return 1;

		// return failed ? 1 : 0;

	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		return 1;
	}

	return 0;
}
