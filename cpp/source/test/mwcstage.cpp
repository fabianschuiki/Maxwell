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

		// Read the ids from the input.
		vector<NodeId> ids;
		for (int i = 1; i < argc; i++) {
			ids.push_back(NodeId(string(argv[i])));
		}

		// Perform the next stage step.
		bool failed = false;
		for (int i = 0; i < mgr.stages.size(); i++) {
			Stage& st = *mgr.stages[i];
			for (int n = 0; n < ids.size(); n++) {
				const NodeId& id = ids[n];
				try {
					NodePtr node = repo.getNode(id);
					cout << "Performing \033[36;1m" << st.getName() << "\033[0m on " << id << "\n";
					st.process(node);
				} catch (std::exception &e) {
					cerr << "*** \033[31;1munclassified error:\033[0m " << st.getName() << " " << id << ": " << e.what() << "\n";
					failed = true;
				}
			}
		}

		return failed ? 1 : 0;

	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		return 1;
	}
}