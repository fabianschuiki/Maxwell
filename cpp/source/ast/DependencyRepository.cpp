/* Copyright © 2013 Fabian Schuiki */
#include "DependencyRepository.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>

using ast::DependencyRepository;
using ast::NodeId;
using std::string;
using std::ifstream;
using std::ofstream;

DependencyRepository::DependencyRepository(const boost::filesystem::path& path) : path(path)
{
	modified = false;
	loaded = false;
}

/// Flushes changes to disk before destroying the repository.
DependencyRepository::~DependencyRepository()
{
	flush();
}

/**
 * @brief Flushes all changes to the persistent store on disk.
 */
void DependencyRepository::flush()
{
	if (modified) store();
}

/**
 * @brief Returns a map of stages and ids that depend on the given node.
 *
 * Throws an exception if the node is not part of the dependency repository.
 */
const DependencyRepository::IdsByStage& DependencyRepository::getDependantIds(const NodeId& id)
{
	if (!loaded) load();
	StagesById::iterator it = dependencies.find(id);
	if (it == dependencies.end()) {
		throw std::runtime_error("Looking for ids depending on " + id.str() + " which is not part of the dependency repository.");
	}
	return it->second;
}

/**
 * @brief Marks the given node id and stage as depending on the given set of
 * ids.
 *
 * The dependencies are internally stored as a list of nodes which each has a
 * separate list of node ids and stages that depend on that node. This function
 * takes parameters describing the other perspective: A list of node ids a
 * given stage and node depend on.
 */
void DependencyRepository::setDependenciesOfStage(const NodeId& id, const string& stage, const Ids& dependingIds)
{
	if (!loaded) load();

	// Add the (stage,node) tuple to the list of dependant tuples of each of the ids.
	for (Ids::const_iterator it = dependingIds.begin(); it != dependingIds.end(); it++) {
		if (dependencies[*it][stage].insert(id).second)
			modified = true;
	}

	// Remove the (stage,node) tuple as dependant node from all other ids.
	for (StagesById::iterator it = dependencies.begin(); it != dependencies.end(); it++) {
		if (!dependingIds.count(it->first)) {
			IdsByStage::iterator is = it->second.find(stage);
			if (is != it->second.end()) {
				if (is->second.erase(id))
					modified = true;
			}
		}
	}
}

/**
 * @brief Removes all references to the given node id from the repository.
 */
void DependencyRepository::removeNode(const NodeId& id)
{
	if (!loaded) load();

	// Remove the dependency record for the node itself.
	if (dependencies.erase(id))
		modified = true;

	// Remove all references to the node.
	for (StagesById::iterator it = dependencies.begin(); it != dependencies.end(); it++) {
		for (IdsByStage::iterator is = it->second.begin(); is != it->second.end();) {
			IdsByStage::iterator is_saved = is;
			is++; // required since we might remove this stage from the repository.
			if (is_saved->second.erase(id)) {
				modified = true;
				if (it->second.empty())
					it->second.erase(is_saved); // remove the stage entirely if it became empty
			}
		}
	}
}

/**
 * @brief Removes all references to nodes spawned by the given source.
 */
void DependencyRepository::removeNode(int source)
{
	if (!loaded) load();

	// Remove all references to the node.
	for (StagesById::iterator it = dependencies.begin(); it != dependencies.end();) {
		StagesById::iterator it_saved = it;
		const NodeId& id = it->first;
		IdsByStage& stages = it->second;
		it++;

		// If this id is part of the given source, remove the entire record.
		if (id.source == source) {
			dependencies.erase(it_saved);
		} else {
			// Iterate through all dependencies and remove the ones referring this source.
			for (IdsByStage::iterator is = stages.begin(); is != stages.end();) {
				IdsByStage::iterator is_saved = is;
				Ids& ids = is->second;
				is++; // required since we might remove this stage from the repository.

				// Find ids with this source and remove them.
				for (Ids::iterator iq = ids.begin(); iq != ids.end();) {
					Ids::iterator iq_saved = iq;
					iq++;
					if ((*iq_saved).source == source) {
						ids.erase(iq_saved);
						modified = true;
					}
				}

				// Remove the stage entirely if there's no more ids left.
				if (ids.empty())
					stages.erase(is_saved);
			}
		}
	}
}

/**
 * @brief Loads the dependency repository from disk.
 *
 * Throws an exception if the repository has unflushed changes. In that case
 * you should call flush() first.
 */
void DependencyRepository::load()
{
	if (modified) {
		throw std::runtime_error("Loading dependency repository from disk would overwrite modifications.");
	}
	loaded = true;

	ifstream f(path.c_str());
	if (!f.good()) return;
	dependencies.clear();
	while (!f.eof()) {
		string id_str; f >> id_str;
		if (id_str.empty()) continue;
		NodeId id(id_str);
		while (!f.eof()) {
			string stage; f >> stage;
			if (stage.empty()) continue;
			if (stage == ";")
				break;
			while (!f.eof()) {
				string depid_str; f >> depid_str;
				if (depid_str.empty()) continue;
				if (depid_str == ";")
					break;
				dependencies[id][stage].insert(NodeId(depid_str));
			}
		}
	}
}

/**
 * @brief Stores the dependencies to disk.
 *
 * Does nothing if the repository has not been loaded through the load()
 * function.
 */
void DependencyRepository::store()
{
	if (!loaded) return;
	modified = false;

	ofstream f(path.c_str());
	if (!f.good()) {
		throw std::runtime_error("Unable to open dependency repository for writing at " + path.string() + ".");
	}
	for (StagesById::iterator it = dependencies.begin(); it != dependencies.end(); it++) {
		f << it->first;
		for (IdsByStage::iterator is = it->second.begin(); is != it->second.end(); is++) {
			f << "\n\t" << is->first;
			for (Ids::iterator iq = is->second.begin(); iq != is->second.end(); iq++) {
				f << " " << *iq;
			}
			f << " ;";
		}
		f << " ;\n";
	}
}