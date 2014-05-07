/* Copyright © 2013 Fabian Schuiki */
#include "NodeFlagsRepository.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>

using ast::NodeFlagsRepository;
using ast::NodeId;
using std::string;
using std::ifstream;
using std::ofstream;

NodeFlagsRepository::NodeFlagsRepository(const boost::filesystem::path& path) : path(path)
{
	modified = false;
	loaded = false;
}

/// Flushes changes to disk before destruction.
NodeFlagsRepository::~NodeFlagsRepository()
{
	flush();
}

/**
 * @brief Returns a set of flags set for the given node id.
 */
NodeFlagsRepository::Flags NodeFlagsRepository::getFlags(const NodeId& id)
{
	if (!loaded) load();
	FlagsByNode::iterator it = flags.find(id);
	if (it != flags.end()) {
		return it->second;
	}
	return Flags();
}

/**
 * @brief Returns true if the given flag is set for the given node id.
 */
bool NodeFlagsRepository::isFlagSet(const NodeId& id, int flag)
{
	if (!loaded) load();
	FlagsByNode::iterator it = flags.find(id);
	if (it != flags.end()) {
		return it->second.count(flag);
	}
	return false;
}

/**
 * @brief Sets the given flag for the given node id.
 */
void NodeFlagsRepository::addFlag(const NodeId& id, int flag)
{
	if (!loaded) load();
	if (flags[id].insert(flag).second)
		modified = true;
}

/**
 * @brief Removes the given flag for the given node id.
 */
void NodeFlagsRepository::removeFlag(const NodeId& id, int flag)
{
	if (!loaded) load();
	FlagsByNode::iterator it = flags.find(id);
	if (it != flags.end()) {
		if (it->second.erase(flag))
			modified = true;
	}
}

/**
 * @brief Removes the given node id from the repository, thus removing all
 * flags associated with it.
 */
void NodeFlagsRepository::removeFlags(const NodeId& id)
{
	if (!loaded) load();
	if (flags.erase(id))
		modified = true;
}

/**
 * @brief Removes all nodes spawned by the given source from the repository.
 */
void NodeFlagsRepository::removeFlags(int source)
{
	if (!loaded) load();
	for (FlagsByNode::iterator it = flags.begin(); it != flags.end();) {
		FlagsByNode::iterator it_saved = it;
		it++;
		if (it_saved->first.source == source) {
			flags.erase(it_saved);
			modified = true;
		}
	}
}

/**
 * @brief Flushes all changes to the persistent store on disk.
 */
void NodeFlagsRepository::flush()
{
	if (modified) store();
}

/**
 * @brief Loads the flags from disk.
 *
 * Throws an exception if the repository has unflushed changes. In that case
 * you should call flush() first.
 */
void NodeFlagsRepository::load()
{
	if (modified) {
		throw std::runtime_error("Loading flags repository from disk would overwrite modifications.");
	}
	loaded = true;

	ifstream f(path.c_str());
	if (!f.good()) return;
	flags.clear();
	while (!f.eof()) {
		string id_str; f >> id_str;
		if (id_str.empty())
			continue;
		NodeId id(id_str);
		while (!f.eof()) {
			string flag_str; f >> flag_str;
			if (flag_str.empty())
				continue;
			if (flag_str == ";")
				break;
			flags[id].insert(atoi(flag_str.c_str()));
		}
	}
}

/**
 * @brief Stores the flags to disk.
 *
 * Does nothing if the flags have not been loaded through load() function.
 */
void NodeFlagsRepository::store()
{
	if (!loaded) return;
	modified = false;

	ofstream f(path.c_str());
	if (!f.good()) {
		throw std::runtime_error("Unable to open flags repository for writing at " + path.string() + ".");
	}
	for (FlagsByNode::iterator it = flags.begin(); it != flags.end(); it++) {
		f << it->first << " ";
		for (Flags::iterator is = it->second.begin(); is != it->second.end(); is++) {
			f << " " << *is;
		}
		f << " ;\n";
	}
}