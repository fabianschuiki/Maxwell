/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <ast/Node.hpp>
#include <string>

namespace stage {

using std::string;
using ast::NodePtr;

class Stage
{
public:
	virtual string getName() = 0;
	virtual void process(const NodePtr& node) = 0;
};

}