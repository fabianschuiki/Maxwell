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