/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "Stage.hpp"

namespace stage {

using ast::NodePtr;
using ast::NodeVector;
using ast::Repository;

class BuildGraph : public Stage
{
protected:
	virtual void process(const NodePtr& node);
public:
	string getName() const { return "BuildGraph"; }
	BuildGraph(Repository& r) : Stage(r) {}

	/* Copyright © 2013 Fabian Schuiki */
	NodePtr process(const NodePtr& node, const NodePtr& carry);
};

class BindIdentifiers : public Stage
{
protected:
	virtual void process(const NodePtr& node);
public:
	string getName() const { return "BindIdentifiers"; }
	BindIdentifiers(Repository& r) : Stage(r) {}
};

class BindNamedTypes : public Stage
{
protected:
	virtual void process(const NodePtr& node);
public:
	string getName() const { return "BindNamedTypes"; }
	BindNamedTypes(Repository& r) : Stage(r) {}
};

class EvalTypeExprs : public Stage
{
protected:
	virtual void process(const NodePtr& node);
public:
	string getName() const { return "EvalTypeExprs"; }
	EvalTypeExprs(Repository& r) : Stage(r) {}
};

class InitRootTypes : public Stage
{
protected:
	virtual void process(const NodePtr& node);
public:
	string getName() const { return "InitRootTypes"; }
	InitRootTypes(Repository& r) : Stage(r) {}

	/* Copyright © 2013 Fabian Schuiki */
	void wrapFuncArgs(NodeVector& args, const NodeVector& funcArgs);
};

class ConfigureCalls : public Stage
{
protected:
	virtual void process(const NodePtr& node);
public:
	string getName() const { return "ConfigureCalls"; }
	ConfigureCalls(Repository& r) : Stage(r) {}
};

class FindCallCandidates : public Stage
{
protected:
	virtual void process(const NodePtr& node);
public:
	string getName() const { return "FindCallCandidates"; }
	FindCallCandidates(Repository& r) : Stage(r) {}
};

class CalcPossibleTypes : public Stage
{
protected:
	virtual void process(const NodePtr& node);
public:
	string getName() const { return "CalcPossibleTypes"; }
	CalcPossibleTypes(Repository& r) : Stage(r) {}

	/* Copyright © 2013 Fabian Schuiki */
	void processChildren(const NodePtr& node);
};

class CalcRequiredTypes : public Stage
{
protected:
	virtual void process(const NodePtr& node);
public:
	string getName() const { return "CalcRequiredTypes"; }
	CalcRequiredTypes(Repository& r) : Stage(r) {}
};

} // namespace stage
