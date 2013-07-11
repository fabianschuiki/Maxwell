/* Copyright © 2013 Fabian Schuiki */
#include "Stage.hpp"

using stage::Stage;

/**
 * @brief Performs this stage's operation for the given node.
 *
 * Sets the node as the stage's currentNode and calls the process() function
 * which is overridden by a concrete subclass.
 */
void Stage::run(const NodePtr& node)
{
	currentNode = node;
	dependencies.clear();
	process(node);
	// TODO: commit dependencies to the repository for this (stage,node) tuple.
	currentNode.reset();
}

/**
 * @brief Performs this stage's operation for the node with the given id.
 *
 * Looks up the given id in the stage's repository and calls run() with the
 * actual node.
 */
void Stage::run(const NodeId& id)
{
	run(repository.getNode(id));
}

/**
 * @brief Flags the currentNode as depending on the given path of the given
 * node id.
 */
void Stage::addDependency(const NodeId& id)
{
	dependencies.insert(id);
}

/**
 * @brief Prints the given message if the configured verbosity level is above
 * the %verbosity passed to the function.
 *
 * An optional %metadata parameter may be specified which is displayed in a
 * separate color in front of the message. The default value is the currentNode
 * id.
 */
void Stage::println(int verbosity, const string& msg, string metadata)
{
	if (this->verbosity > verbosity)
	{
		// Default to the currentNode's id as metadata.
		if (metadata.empty() && currentNode) {
			metadata = currentNode->getId().str();
		}

		// Write the formatted output.
		std::cout << "\033[1m" << getName() << "\033[0m \033[36m" << metadata << "\033[0m: " << msg << std::endl;
	}
}