/* Copyright © 2013 Fabian Schuiki */
#include "Repository.hpp"
#include <iostream>

using ast::Repository;
using ast::SourceRepository;
using ast::NodeRepository;
using ast::NodeRef;
using ast::NodeId;
using boost::scoped_ptr;

Repository::Repository(const boost::filesystem::path& path) : path(path)
{
	boost::filesystem::path p = path; p /= "sources";
	sourceRepo.reset(new SourceRepository(p));
	nodeRepo.reset(new NodeRepository(p));
}

/**
 * @brief Flushes all pending changes to the repository to disk.
 */
void Repository::flush()
{
	sourceRepo->flush();
	nodeRepo->flush();
}

/**
 * @brief Adds the node to the NodeRepository for the given source file.
 *
 * Returns the id that was assigned to the node.
 */
NodeId Repository::addNode(int source, const NodeRef& node)
{
	return nodeRepo->addNode(source, node);
}

/**
 * @brief Adds the node to the NodeRepository and registers the source file if
 * not yet done so.
 *
 * Returns the id that was assigned to the node.
 */
NodeId Repository::addNode(const string& source, const NodeRef& node)
{
	return addNode(sourceRepo->registerSource(source), node);
}

/**
 * @brief Returns the node with the given id.
 *
 * Throws an exception if the node does not exist.
 */
NodeRef Repository::getNode(const NodeId& id)
{
	return nodeRepo->getNode(id);
}

/**
 * @brief Registers the given source with the repo, possibly assigning it a new
 * unique id.
 *
 * Returns the id of the source file.
 */
int Repository::registerSource(const string& s)
{
	return sourceRepo->registerSource(s);
}

/**
 * @brief Removes the given source file from the repository.
 *
 * Also removes all nodes that were spawned by this source file.
 */
int Repository::unregisterSource(const string& s)
{
	int id = sourceRepo->unregisterSource(s);
	if (id) {
		nodeRepo->removeNode(id);
	}
	return id;
}

/**
 * @brief Removes the given source file from the repository.
 *
 * Also removes all nodes that were spawned by this source file.
 */
void Repository::unregisterSource(int i)
{
	sourceRepo->unregisterSource(i);
	nodeRepo->removeNode(i);
}

/**
 * @brief Called by the NodeRepository to indicate a node was added to the
 * repository's set of loaded nodes.
 *
 * This callback will then properly setup the node dependencies and hierarchy.
 */
void Repository::nodeLoaded(const NodeId& id, const NodeRef& node)
{
	node->updateHierarchy(id, shared_from_this());
}

/**
 * @brief Marks the given node as modified.
 */
void Repository::markModified(const NodeId& id)
{
	nodeRepo->markModified(id);
	std::cout << "Modified node " << id << "\n";
}