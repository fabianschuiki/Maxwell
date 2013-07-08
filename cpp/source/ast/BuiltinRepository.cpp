/* Copyright © 2013 Fabian Schuiki */
#include "BuiltinRepository.hpp"
#include <stdexcept>

using ast::BuiltinRepository;
using ast::Repository;
using ast::NodePtr;
using ast::NodeId;
using std::string;

BuiltinRepository::BuiltinRepository(Repository& repository) : repository(repository)
{
	index = 0;
	build();
}

const NodePtr& BuiltinRepository::getNode(int id)
{
	if (!nodes.count(id)) {
		throw std::runtime_error("Builtin node id not known.");
	}
	return nodes[id];
}

void BuiltinRepository::add(const NodePtr& node, const string& name)
{
	index++;
	nodes[index] = node;
	nodeNames[index] = name;//node->asNamed()->getName();
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
}