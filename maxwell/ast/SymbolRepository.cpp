/* Copyright (c) 2013 Fabian Schuiki */
#include "maxwell/ast/SymbolRepository.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>

using ast::SymbolRepository;
using ast::NodeId;
using std::string;
using std::map;
using std::ifstream;
using std::ofstream;

SymbolRepository::SymbolRepository(const boost::filesystem::path& path) : path(path)
{
	modified = false;
	loaded = false;
}

/// Flushes changes to disk before destruction.
SymbolRepository::~SymbolRepository()
{
	flush();
}

/// Returns all exported symbols in the repository.
const SymbolRepository::ExportedSymbols& SymbolRepository::getExportedSymbols()
{
	if (!loaded) load();
	return exportedSymbols;
}

/**
 * @brief Returns a map of symbols the given source exports.
 */
const SymbolRepository::Symbols& SymbolRepository::getExportedSymbols(int source)
{
	if (!loaded) load();
	ExportedSymbols::iterator it = exportedSymbols.find(source);
	if (it == exportedSymbols.end()) {
		throw std::runtime_error("Requesting exported symbols of source which is not part of the symbol repository.");
	}
	return it->second;
}

/**
 * @brief Adds the given node as an exported symbol to its source's table.
 */
void SymbolRepository::addExportedSymbol(const NodeId& id, const string& name)
{
	if (!loaded) load();
	if (!exportedSymbols.count(id.source) || !exportedSymbols[id.source].count(id) || exportedSymbols[id.source][id] != name) {
		modified = true;
		exportedSymbols[id.source][id] = name;
	}
}

/**
 * @brief Removes the given node id from the symbol table for the id's source.
 */
void SymbolRepository::removeExportedSymbol(const NodeId& id)
{
	if (!loaded) load();
	ExportedSymbols::iterator it = exportedSymbols.find(id.source);
	if (it == exportedSymbols.end()) {
		throw std::runtime_error("Removing node " + id.str() + " from symbol table which does not contain the node's source.");
	}
	if (it->second.erase(id) > 0) {
		modified = true;
	}
}

/**
 * @brief Removes all exported symbols of the given source from the symbol table.
 */
void SymbolRepository::removeExportedSymbol(int source)
{
	if (!loaded) load();
	if (exportedSymbols.erase(source) > 0) {
		modified = true;
	}
}

/**
 * @brief Flushes all changes to the persistent store on disk.
 */
void SymbolRepository::flush()
{
	if (modified) store();
}

/**
 * @brief Loads the symbol tables from disk.
 *
 * Throws an exception if the repository has unflushed changes. In that case
 * you should call flush() first.
 */
void SymbolRepository::load()
{
	if (modified) {
		throw std::runtime_error("Loading symbol tables from disk would overwrite modifications.");
	}
	loaded = true;

	ifstream f(path.c_str());
	if (!f.good()) return;
	exportedSymbols.clear();
	while (!f.eof()) {
		string i, n;
		f >> i;
		while (!f.eof() && (f.peek() == ' ' || f.peek() == '\t'))
			f.get();
		if (f.eof()) break;
		std::getline(f, n);

		NodeId id(i);
		exportedSymbols[id.source][id] = n;
	}
}

/**
 * @brief Stores the symbol tables to disk.
 *
 * Does nothing if the symbols have not been loaded through load() function.
 */
void SymbolRepository::store()
{
	if (!loaded) return;
	modified = false;

	ofstream f(path.c_str());
	if (!f.good()) {
		throw std::runtime_error("Unable to open symbol repository for writing at " + path.string() + ".");
	}
	for (ExportedSymbols::iterator it = exportedSymbols.begin(); it != exportedSymbols.end(); it++) {
		for (Symbols::iterator is = it->second.begin(); is != it->second.end(); is++) {
			f << is->first << "  " << is->second << "\n";
		}
		f << "\n";
	}
}
