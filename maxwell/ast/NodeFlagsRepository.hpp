/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "maxwell/ast/Node.hpp"
#include <boost/filesystem.hpp>
#include <set>
#include <map>

namespace ast {

using std::set;
using std::map;

/**
 * @brief Manages a persistent store for set of flags per node.
 *
 * The NodeFlagsRepository is mainly used to keep track of what stages have
 * been performed on what objects.
 */
class NodeFlagsRepository
{
public:
	const boost::filesystem::path path;
	NodeFlagsRepository(const boost::filesystem::path& path);
	~NodeFlagsRepository();

	typedef set<int> Flags;
	typedef map<NodeId, Flags> FlagsByNode;
	Flags getFlags(const NodeId& id);
	bool isFlagSet(const NodeId& id, int flag);

	void addFlag(const NodeId& id, int flag);
	void removeFlag(const NodeId& id, int flag);
	void removeFlags(const NodeId& id);
	void removeFlags(int source);

	void flush();

private:
	FlagsByNode flags;
	bool modified;
	bool loaded;

	void load();
	void store();
};

} // namespace ast
