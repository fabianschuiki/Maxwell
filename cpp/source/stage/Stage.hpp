/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <ast/Node.hpp>
#include <ast/Repository.hpp>
#include <string>

namespace stage {

using std::string;
using ast::NodePtr;
using ast::Repository;

class Stage
{
public:
	Repository& repository;

	virtual string getName() const = 0;
	virtual void process(const NodePtr& node) = 0;

	Stage(Repository& r) : repository(r) {}
};

}