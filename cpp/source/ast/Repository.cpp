/* Copyright © 2013 Fabian Schuiki */
#include "Repository.hpp"
#include "nodes/interfaces.hpp"
#include <iostream>
#include <boost/bind.hpp>

using ast::Repository;
using ast::SourceRepository;
using ast::NodeRepository;
using ast::NodePtr;
using ast::NodeId;
using ast::NamedInterface;
using boost::scoped_ptr;

Repository::Repository(const boost::filesystem::path& path) : path(path), builtinRepository(*this)
{
	boost::filesystem::path psrc = path; psrc /= "sources";
	boost::filesystem::path psym = path; psym /= "symbols";
	boost::filesystem::path pdep = path; pdep /= "dependencies";
	sourceRepo.reset(new SourceRepository(psrc));
	nodeRepo.reset(new NodeRepository(path));
	symbolRepo.reset(new SymbolRepository(psym));
	dependencyRepo.reset(new DependencyRepository(pdep));

	// Configure the required callbacks.
	nodeRepo->onNodeLoaded = boost::bind(&Repository::nodeLoaded, this, _1, _2);

	// Create the map of builtin nodes.
	const BuiltinRepository::NodeNames& names = builtinRepository.getNodeNames();
	for (BuiltinRepository::NodeNames::const_iterator it = names.begin(); it != names.end(); it++) {
		NodeId id(0, it->first);
		builtinNodes[id] = it->second;
	}
}

/**
 * @brief Flushes all pending changes to the repository to disk.
 */
void Repository::flush()
{
	sourceRepo->flush();
	nodeRepo->flush();
	symbolRepo->flush();
	dependencyRepo->flush();
}

/**
 * @brief Adds the node to the NodeRepository for the given source file.
 *
 * Returns the id that was assigned to the node.
 */
NodeId Repository::addNode(int source, const NodePtr& node)
{
	NodeId id = nodeRepo->addNode(source, node);
	if (NamedInterface *intf = node->asNamed()) {
		symbolRepo->addExportedSymbol(id, intf->getName());
	}
	return id;
}

/**
 * @brief Adds the node to the NodeRepository and registers the source file if
 * not yet done so.
 *
 * Returns the id that was assigned to the node.
 */
NodeId Repository::addNode(const string& source, const NodePtr& node)
{
	return addNode(sourceRepo->registerSource(source), node);
}

/**
 * @brief Returns the node with the given id.
 *
 * Throws an exception if the node does not exist.
 */
NodePtr Repository::getNode(const NodeId& id)
{
	if (id.source == 0) {
		const NodePtr& n = builtinRepository.getNode(id.root);
		if (!id.id.empty()) {
			return n->resolvePath(id.id);
		} else {
			return n;
		}
	}
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
		symbolRepo->removeExportedSymbol(id);
		dependencyRepo->removeNode(id);
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
	symbolRepo->removeExportedSymbol(i);
	dependencyRepo->removeNode(i);
}

/**
 * @brief Called by the NodeRepository to indicate a node was added to the
 * repository's set of loaded nodes.
 *
 * This callback will then properly setup the node dependencies and hierarchy.
 */
void Repository::nodeLoaded(const NodeId& id, const NodePtr& node)
{
	node->updateHierarchy(id, this);
}

/**
 * @brief Marks the given node as modified.
 */
void Repository::markModified(const NodeId& id)
{
	nodeRepo->markModified(id);
}

/**
 * @brief Called by individual nodes upon modification of an attribute.
 *
 * Causes the repository to invalidate all nodes that depend on the node %id.
 */
void Repository::notifyNodeChanged(const NodeId& id)
{
	// Fetch a list of dependencies for this id.
	const DependencyRepository::IdsByStage& deps = dependencyRepo->getDependantIds(id);

	// Show stuff.
	for (DependencyRepository::IdsByStage::const_iterator it = deps.begin(); it != deps.end(); it++) {
		std::cout << "Invalidating " << it->first << " of";
		for (DependencyRepository::Ids::const_iterator is = it->second.begin(); is != it->second.end(); is++) {
			std::cout << " " << *is;
		}
		std::cout << " (due to changed " << id << ")\n";
	}
}

/**
 * @brief Returns a map of external nodes known to the node given by id.
 */
Repository::ExternalNames Repository::getExternalNamesForNodeId(const NodeId& id)
{
	ExternalNames nodes(builtinNodes);
	// TODO: add the known nodes for that node
	const SymbolRepository::Symbols& local = symbolRepo->getExportedSymbols(id.source);
	nodes.insert(local.begin(), local.end());
	return nodes;
}

/**
 * @brief Marks the given stage and node id as dependant on the given %ids.
 */
void Repository::setDependenciesOfStage(const NodeId& id, const string& stage, const set<NodeId>& ids)
{
	dependencyRepo->setDependenciesOfStage(id, stage, ids);
}