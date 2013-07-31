/* Copyright © 2013 Fabian Schuiki */
#include "BuiltinRepository.hpp"
#include "nodes/DefinedType.hpp"
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

ast::builtin::NumericType::Ptr BuiltinRepository::numericType(const string& name)
{
	builtin::NumericType::Ptr t(new builtin::NumericType);
	t->name = name;
	add(t, t->name);
	return t;
}

ast::builtin::FuncDef::Ptr BuiltinRepository::funcDef(const string& name, const NodePtr& in0, const NodePtr& out0)
{
	using ast::DefinedType;

	DefinedType::Ptr tin0(new DefinedType), tout0(new DefinedType);
	tin0->setDefinition(in0);
	tout0->setDefinition(out0);

	builtin::FuncArg::Ptr ain0(new builtin::FuncArg), aout0(new builtin::FuncArg);
	ain0->name = "a";
	ain0->type = tin0;
	aout0->name = "b";
	aout0->type = tout0;

	builtin::FuncDef::Ptr f(new builtin::FuncDef);
	f->name = name;
	f->in.resize(1);
	f->in[0] = ain0;
	f->out.resize(1);
	f->out[0] = aout0;
	add(f, f->name);
	return f;
}

ast::builtin::FuncDef::Ptr BuiltinRepository::funcDef(const string& name, const NodePtr& in0, const NodePtr& in1, const NodePtr& out0)
{
	using ast::DefinedType;

	DefinedType::Ptr tin0(new DefinedType), tin1(new DefinedType), tout0(new DefinedType);
	tin0->setDefinition(in0);
	tin1->setDefinition(in1);
	tout0->setDefinition(out0);

	builtin::FuncArg::Ptr ain0(new builtin::FuncArg), ain1(new builtin::FuncArg), aout0(new builtin::FuncArg);
	ain0->name = "a";
	ain0->type = tin0;
	ain1->name = "a";
	ain1->type = tin1;
	aout0->name = "b";
	aout0->type = tout0;

	builtin::FuncDef::Ptr f(new builtin::FuncDef);
	f->name = name;
	f->in.resize(2);
	f->in[0] = ain0;
	f->in[1] = ain1;
	f->out.resize(1);
	f->out[0] = aout0;
	add(f, f->name);
	return f;
}

void BuiltinRepository::build()
{
	const builtin::NumericType::Ptr& tInt = numericType("Int");
	const builtin::NumericType::Ptr& tReal = numericType("Real");
	const builtin::NumericType::Ptr& tBool = numericType("Bool");

	const char* comparisonNames[] = {
		"==", "!=", ">", "<", ">=", "<=", NULL
	};
	for (int i = 0; comparisonNames[i]; i++) {
		funcDef(comparisonNames[i], tInt, tInt, tBool);
		funcDef(comparisonNames[i], tReal, tReal, tBool);
		funcDef(comparisonNames[i], tBool, tBool, tBool);
	}

	const char* mathBinaryNames[] = {
		"+", "-", "*", "/", NULL
	};
	for (int i = 0; mathBinaryNames[i]; i++) {
		funcDef(mathBinaryNames[i], tInt, tInt, tInt);
		funcDef(mathBinaryNames[i], tReal, tReal, tReal);
		funcDef(mathBinaryNames[i], tInt, tReal, tReal);
		funcDef(mathBinaryNames[i], tReal, tInt, tReal);
	}

	numericType("String"); // needs to be changed

	numericType("Array"); // needs to be changed
	numericType("Set"); // dito
	numericType("Map"); // dito
}