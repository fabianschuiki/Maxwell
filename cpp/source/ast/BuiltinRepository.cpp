/* Copyright © 2013 Fabian Schuiki */
#include "BuiltinRepository.hpp"
#include "nodes/ast.hpp"
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

	TupleTypeArg::Ptr ain0(new TupleTypeArg), aout0(new TupleTypeArg);
	ain0->setName("a");
	ain0->setType(tin0);
	aout0->setName("b");
	aout0->setType(tout0);

	NodeVector inArgs(1), outArgs(1);
	inArgs[0] = ain0;
	outArgs[0] = aout0;

	TupleType::Ptr inTuple(new TupleType), outTuple(new TupleType);
	inTuple->setArgs(inArgs);
	outTuple->setArgs(outArgs);

	FuncType::Ptr type(new FuncType);
	type->setIn(inTuple);
	type->setOut(outTuple);

	builtin::FuncDef::Ptr f(new builtin::FuncDef);
	f->name = name;
	f->type = type;
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

	TupleTypeArg::Ptr ain0(new TupleTypeArg), ain1(new TupleTypeArg), aout0(new TupleTypeArg);
	ain0->setName("a");
	ain0->setType(tin0);
	ain1->setName("b");
	ain1->setType(tin1);
	aout0->setName("c");
	aout0->setType(tout0);

	NodeVector inArgs(2), outArgs(1);
	inArgs[0] = ain0;
	inArgs[1] = ain1;
	outArgs[0] = aout0;

	TupleType::Ptr inTuple(new TupleType), outTuple(new TupleType);
	inTuple->setArgs(inArgs);
	outTuple->setArgs(outArgs);

	FuncType::Ptr type(new FuncType);
	type->setIn(inTuple);
	type->setOut(outTuple);

	builtin::FuncDef::Ptr f(new builtin::FuncDef);
	f->name = name;
	f->type = type;
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