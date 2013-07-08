/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <ast/Node.hpp>
#include <ast/Repository.hpp>
#include <ast/nodes/ast.hpp>
#include <string>

namespace stage {

using std::string;
using ast::NodePtr;
using ast::Repository;

/**
 * @brief Base class for all AST processing stages.
 *
 * Individual stages implement the virtual methods below to perform their
 * processing steps. The StageManager object maintains a list of all stages and
 * the order in which they're supposed to be executed.
 */
class Stage
{
public:
	Repository& repository;

	virtual string getName() const = 0;
	virtual void process(const NodePtr& node) = 0;

	Stage(Repository& r) : repository(r) {}
};

}