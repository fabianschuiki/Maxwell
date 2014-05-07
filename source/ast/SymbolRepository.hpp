/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "Node.hpp"
#include <string>
#include <map>
#include <boost/filesystem.hpp>

namespace ast {

using std::string;
using std::map;

/**
 * @brief Manages a persistent store for symbol import/export tables.
 */
class SymbolRepository
{
public:
	const boost::filesystem::path path;
	SymbolRepository(const boost::filesystem::path& path);
	~SymbolRepository();

	typedef map<NodeId, string> Symbols;
	typedef map<int, Symbols> ExportedSymbols;
	const Symbols& getExportedSymbols(int source);

	void addExportedSymbol(const NodeId& id, const string& name);
	void removeExportedSymbol(const NodeId& id);
	void removeExportedSymbol(int source);

	void flush();

private:
	ExportedSymbols exportedSymbols;
	bool modified;
	bool loaded;

	void load();
	void store();
};

} // namespace ast