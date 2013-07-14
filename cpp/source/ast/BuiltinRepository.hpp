/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "Node.hpp"
#include "builtin/NumericType.hpp"
#include <string>
#include <map>
#include <boost/smart_ptr.hpp>

namespace ast {

using std::string;
using std::map;
using boost::shared_ptr;

class Repository;

/**
 * @brief Container class for all builtin types.
 *
 * The Repository class uses the BuiltinRepository to resolve references to
 * types and functions built into the language.
 */
class BuiltinRepository
{
public:
	Repository& repository;
	BuiltinRepository(Repository& repository);

	typedef map<int, NodePtr> Nodes;
	typedef map<int, string> NodeNames;

	const NodePtr& getNode(int id);
	const NodePtr& getNode(const NodeId& id);
	const NodePtr& getNode(const string& name);
	const Nodes& getNodes() { return nodes; }
	const NodeNames& getNodeNames() { return nodeNames; }

protected:
	int index;
	Nodes nodes;
	NodeNames nodeNames;
	typedef map<string, NodePtr> NodesByName;
	NodesByName nodesByName;

	typedef shared_ptr<builtin::NumericType> NumericTypePtr;

	void build();
	void add(const NodePtr& node, const string& name);
	NumericTypePtr numericType(string name);
};

} // namespace ast