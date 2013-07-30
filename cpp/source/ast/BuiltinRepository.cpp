/* Copyright © 2013 Fabian Schuiki */
#include "BuiltinRepository.hpp"
#include <stdexcept>
#include <boost/lexical_cast.hpp>

using ast::BuiltinRepository;
using ast::Repository;
using ast::NodePtr;
using ast::NodeId;
using std::string;
using boost::lexical_cast;

BuiltinRepository::BuiltinRepository(Repository& repository) : repository(repository)
{
	index = 0;
	build();
}

const NodePtr& BuiltinRepository::getNode(int id)
{
	if (!nodes.count(id)) {
		throw std::runtime_error("Builtin node with id " + lexical_cast<string>(id) + " does not exist.");
	}
	return nodes[id];
}

const NodePtr& BuiltinRepository::getNode(const string& name)
{
	NodesByName::iterator it = nodesByName.find(name);
	if (it == nodesByName.end()) {
		throw std::runtime_error("Builtin node named " + name + " does not exist.");
	}
	return it->second;
}

void BuiltinRepository::add(const NodePtr& node, const string& name)
{
	index++;
	nodes[index] = node;
	nodeNames[index] = name;//node->asNamed()->getName();
	nodesByName[name] = node;
	node->updateHierarchy(NodeId(0, index), &repository);
}

BuiltinRepository::NumericTypePtr BuiltinRepository::numericType(string name)
{
	NumericTypePtr t(new builtin::NumericType);
	t->name = name;
	add(t, t->name);
	return t;
}

void BuiltinRepository::build()
{
	numericType("Int");
	numericType("Real");

	numericType("Array"); // needs to be changed
	numericType("Set"); // dito
	numericType("Map"); // dito
}