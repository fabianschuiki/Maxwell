/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "Node.hpp"
#include <map>
#include <string>
#include <set>
#include <boost/filesystem.hpp>

namespace ast {

using std::map;
using std::string;
using std::set;

/**
 * Manages a list of dependencies per node.
 */
class DependencyRepository
{
public:
	const boost::filesystem::path path;
	DependencyRepository(const boost::filesystem::path& path);
	~DependencyRepository();

	typedef set<NodeId> Ids;
	typedef map<string, Ids> IdsByStage;
	typedef map<NodeId, IdsByStage> StagesById;
	IdsByStage getDependantIds(const NodeId& id);

	void setDependenciesOfStage(const NodeId& id, const string& stage, const Ids& dependingIds);
	void removeNode(const NodeId& id);
	void removeNode(int source);

	void flush();

private:
	StagesById dependencies;
	bool loaded;
	bool modified;

	void load();
	void store();
};

} // namespace ast