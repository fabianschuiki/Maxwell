/* Copyright © 2013 Fabian Schuiki */

/**
 * @file This program serves as a testing facility for the ast::NodeRepository
 * classes.
 */

#include <iostream>
#include <ast/nodes/ast.hpp>
#include <ast/NodeRepository.hpp>
#include <boost/smart_ptr.hpp>
#include <vector>
#include <string>

using std::cout;
using std::cerr;
using boost::shared_ptr;
using namespace ast;
using std::vector;
using std::string;

int main(int argc, char *argv[])
{
	try {
		NodeRepository repo("./noderepo");

		bool clearSource = false;
		vector<string> readNodes;
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "--clear") == 0) {
				clearSource = true;
			} else {
				readNodes.push_back(argv[i]);
			}
		}

		if (clearSource) {
			// Remove the source #1.
			cout << "Removing nodes from source #1\n";
			repo.removeNode(1);
		} else if (!readNodes.empty()) {
			// Read the requested nodes.
			for (int i = 0; i < readNodes.size(); i++) {
				cout << "Reading node \033[1m" << readNodes[i] << "\033[0m... ";
				shared_ptr<Node> node = repo.getNode(NodeId(readNodes[i]));
				cout << node->describe() << "\n";
			}

			// Dump the loaded nodes.
			cout << "Loaded nodes: ";
			bool first = true;
			const NodeRepository::Nodes& loaded = repo.getLoadedNodes();
			for (NodeRepository::Nodes::const_iterator it = loaded.begin(); it != loaded.end(); it++) {
				if (!first) cout << ", "; else first = false;
				cout << it->first;
			}
			cout << "\n";
		} else {
			// Add a node.
			shared_ptr<FuncDef> fdef(new FuncDef);
			fdef->setName("main");
			cout << "Adding node " << fdef->describe() << " to source #1... ";
			NodeId id = repo.addNode(1, fdef);
			cout << "id = \033[33m" << id << "\033[0m\n";

			// Flush the changes.
			std::cout << "Flushing changes\n";
			repo.flush();
		}

		return 0;
	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
	}
	return 1;
}