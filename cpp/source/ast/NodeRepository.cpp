/* Copyright © 2013 Fabian Schuiki */
#include "NodeRepository.hpp"
#include "Serializer.hpp"
#include <cassert>
#include <fstream>

using ast::NodeRepository;
using ast::NodeId;
using ast::Node;
using std::map;
using std::string;
using boost::shared_ptr;

NodeRepository::NodeRepository(const boost::filesystem::path& path) : path(path)
{
	// Create the directory if required.
	if (!boost::filesystem::exists(path)) {
		boost::filesystem::create_directory(path);
	}
}

NodeRepository::~NodeRepository()
{
	flush();
}

/**
 * @brief Returns the map of loaded nodes.
 *
 * Since the nodes are loaded lazily, there is no way of retrieving a complete
 * list of nodes in the repository.
 */
const NodeRepository::Nodes& NodeRepository::getLoadedNodes()
{
	return nodes;
}

/**
 * @brief Flushes all changes to the persistent store on disk.
 */
void NodeRepository::flush()
{
	for (NodeIds::iterator it = modified.begin(); it != modified.end();) {
		NodeId id = *it;
		it++; // required here already since store() will erase the id from the set we're iterating
		store(id);
	}
}

/**
 * @brief Marks the given node as modified which causes it to be persisted upon
 * the next flush.
 */
void NodeRepository::markModified(const NodeId& id)
{
	if (!nodes.count(id)) {
		throw std::runtime_error("Marking node modified which is not part of the repository.");
	}
	modified.insert(id);
}

/**
 * @brief Adds the given node to the repository, considering it spawned by the
 * given source id.
 *
 * This function will allocate a new root id within the source to the node. The
 * node is automatically marked as modified such that it is persisted to disk
 * upon the next call to flush().
 *
 * Note that the node's id is not update automatically. If you wish the node to
 * represent the new id, the calling function must assign the result of this
 * function as the node's id.
 */
NodeId NodeRepository::addNode(int source, const shared_ptr<Node>& node)
{
	assert(source > 0 && "source == 0 is reserved for builtin types");

	// Make sure the node is not part of another repository.
	if (!node->getId().empty()) {
		throw std::runtime_error("Adding node which is already part of another repository, i.e. whose id is not empty().");
	}

	// Find a suitable id for the node.
	NodeId id(source, 1);
	boost::filesystem::path basePath = getPathForSource(source);
	char buf[32];
	for (;; id.root++) {
		snprintf(buf, 31, "%i", id.root);
		boost::filesystem::path p = basePath;
		p /= buf;
		if (!boost::filesystem::exists(p)) break; // abort if this root does not exist
	}

	// Insert the node.
	nodes[id] = node;
	modified.insert(id);
	if (onNodeLoaded) onNodeLoaded(id, node);
	return id;
}

/**
 * @brief Returns the node with the given id, possibly loading it from disk.
 *
 * Throws an exception if the given node does not exist. To prevent this, you
 * may query a node's existence within the repository through the hasNode()
 * function.
 */
shared_ptr<Node> NodeRepository::getNode(const NodeId& id)
{
	NodeId rootId = id.getRoot();
	if (!nodes.count(rootId)) {
		load(rootId); // will throw an exception if the node cannot be loaded
	}
	const shared_ptr<Node>& node = nodes[rootId]; // guaranteed to exist by the call to load()
	if (id.isRoot())
		return node;
	else
		return node->resolvePath(id.id);
}

/**
 * @brief Returns true if the node exists in the repository.
 *
 * This function checks the entire repository, not only the loaded ones. This
 * means that this function may be used to check whether it is safe to ask for
 * a specific node id.
 *
 * Make sure that the %id is a root id, i.e. isRoot() returns true. Otherwise
 * the repository will try to locate nodes in '<source>/<root>.<id>', which
 * most likely fail due to the <id> component.
 */
bool NodeRepository::hasNode(const NodeId& id)
{
	if (!id.isRoot()) {
		throw std::runtime_error("Only root node ids may be queried for existence using hasNode().");
	}
	if (nodes.count(id))
		return true;
	boost::filesystem::path p = getPathForNodeId(id);
	return boost::filesystem::exists(p);
}

/**
 * @brief Removes the node with the given id from the repository.
 *
 * This function removes the node regardless of whether it is marked as
 * modified.
 */
void NodeRepository::removeNode(const NodeId& id)
{
	if (!id.isRoot()) {
		throw std::runtime_error("Only root node ids may be removed from the repository.");
	}
	nodes.erase(id);
	modified.erase(id);
	boost::filesystem::path p = getPathForNodeId(id);
	if (boost::filesystem::exists(p)) {
		std::cout << "Would remove node file " << p.string() << "\n";
	}
}

/**
 * @brief Removes all nodes in the given source from the repository.
 */
void NodeRepository::removeNode(int source)
{
	for (Nodes::iterator it = nodes.begin(); it != nodes.end();) {
		const NodeId& id = it->first;
		it++; // required since we modify the map
		modified.erase(id);
		nodes.erase(id);
	}
	boost::filesystem::path p = getPathForSource(source);
	if (boost::filesystem::exists(p)) {
		boost::filesystem::remove_all(p);
		//std::cout << "Would remove source directory " << p.string() << "\n";
	}
}

/**
 * @brief Loads the node with the given id from disk.
 *
 * Throws an error if the node does not exist.
 */
void NodeRepository::load(const NodeId& id)
{
	boost::filesystem::path p = getPathForNodeId(id);
	if (!boost::filesystem::exists(p)) {
		throw std::runtime_error("Loading node '" + id.str() + "' that does not exist in the repository.");
	}

	// Load the node through the ast::Serializer.
	std::ifstream f(p.c_str());
	Serializer ser;
	NodePtr node = ser.decode(f);
	nodes[id] = node;
	if (onNodeLoaded) onNodeLoaded(id, node);
}

/**
 * @brief Stores the node with the given id to disk.
 *
 * Throws an exception if the node does not exist.
 */
void NodeRepository::store(const NodeId& id)
{
	modified.erase(id);
	Nodes::iterator it = nodes.find(id);
	if (it == nodes.end()) {
		throw std::runtime_error("Storing node that is not loaded.");
	}
	const shared_ptr<Node>& node = it->second;

	// Create the source directory if required.
	boost::filesystem::path sp = getPathForSource(id.source);
	if (!boost::filesystem::exists(sp)) {
		boost::filesystem::create_directory(sp);
	}
	boost::filesystem::path p = getPathForNodeId(id);

	// Store the node through the ast::Serializer.
	std::ofstream f(p.c_str());
	Serializer ser;
	ser.encode(f, node);
}

/**
 * @brief Returns the path where this source file's nodes are persisted.
 */
boost::filesystem::path NodeRepository::getPathForSource(int source)
{
	char buf[32];
	snprintf(buf, 31, "%i", source);
	boost::filesystem::path p = path;
	p /= buf;
	return p;
}

/**
 * @brief Returns the path where this node is supposed to be persisted.
 *
 * Throws an exception if the id is empty or builtin.
 */
boost::filesystem::path NodeRepository::getPathForNodeId(const NodeId& id)
{
	if (id.empty()) {
		throw std::runtime_error("Asking for path to node with empty id.");
	}
	if (id.isBuiltin()) {
		throw std::runtime_error("Asking for path to builtin node.");
	}

	char buf[32];
	snprintf(buf, 31, "%i", id.root);

	boost::filesystem::path p = getPathForSource(id.source);
	p /= buf;
	if (!id.id.empty()) p /= id.id;
	return p;
}