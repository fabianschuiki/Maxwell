/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "Node.hpp"
#include <map>
#include <set>
#include <string>
#include <boost/filesystem.hpp>

namespace ast {

using std::map;
using std::set;
using std::string;

/**
 * A NodeRepository maintains a persistent store of Node instances on disk. It
 * provides automated lazy loading and storing of nodes.
 */
class NodeRepository
{
public:
	const boost::filesystem::path path;
	NodeRepository(const boost::filesystem::path& path);
	~NodeRepository();

	typedef map<NodeId, shared_ptr<Node> > Nodes;
	const Nodes& getLoadedNodes();

	void flush();
	void markModified(const NodeId& id);

	NodeId addNode(int source, const shared_ptr<Node>& node);
	shared_ptr<Node> getNode(const NodeId& id);
	bool hasNode(const NodeId& id);
	void removeNode(const NodeId& id);
	void removeNode(int source);

private:
	Nodes nodes;
	typedef set<NodeId> NodeIds;
	NodeIds modified;

	void load(const NodeId& id);
	void store(const NodeId& id);

	boost::filesystem::path getPathForSource(int source);
	boost::filesystem::path getPathForNodeId(const NodeId& id);
};

} // namespace ast