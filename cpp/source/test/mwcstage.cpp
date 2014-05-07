/* Copyright © 2013 Fabian Schuiki */

/**
 * @file This program operates on the local repository and performs processing
 * stages on the stored nodes individually.
 */

#include <iostream>
#include <string>
#include <vector>
#include <ast/Repository.hpp>
#include <stage/StageManager.hpp>
#include <stdexcept>

using std::string;
using std::cout;
using std::cerr;
using ast::Repository;
using ast::NodeId;
using ast::NodePtr;
using std::vector;
using stage::StageManager;
using stage::Stage;

int main(int argc, char *argv[])
{
	try {
		Repository repo("mwcrepo");
		StageManager mgr(repo);
		// mgr.stagesByName["CalcActualTypes"]->verbosity = 99;

		// Read the ids from the input.
		vector<NodeId> ids;
		for (int i = 1; i < argc; i++) {
			ids.push_back(NodeId(string(argv[i])));
		}

		int prevStage = -1;
		int prevId = -1;
		bool failed = false;
		int sentinel = 0;
		while (!failed) {
			if (sentinel++ > 50 * ids.size()) // abort if >50 stage iterations were performed PER NODE
				throw std::runtime_error("Excessive amount of stage iterations. Aborting.");

			// Find the next stage to be processed.
			int nextStage = -1;
			int nextId = -1;
			for (int i = 0; i < mgr.stages.size() && nextStage < 0; i++) {
				for (int n = 0; n < ids.size() && nextStage < 0; n++) {
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

					// Perform operation and mark the stage as processed for this node.
					st.run(id);
					repo.addFlag(id, st.getId()); // flag this stage as processed

				} catch (std::exception &e) {
					cerr << "*** \033[31;1munclassified error:\033[0m " << st.getName() << " " << id << ": " << e.what() << "\n";
					failed = true;
				}
			} else {
				break;
			}

			prevStage = nextStage;
			prevId = nextId;
		}

		return failed ? 1 : 0;

	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		return 1;
	}
}