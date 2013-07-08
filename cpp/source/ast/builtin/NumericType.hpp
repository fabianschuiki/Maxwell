/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "BuiltinNode.hpp"
#include <string>

namespace ast {

class BuiltinRepository;

namespace builtin {

using std::string;

class NumericType : public BuiltinNode
{
public:

protected:
	friend class BuiltinRepository;
	string name;
};

} // namespace builtin
} // namespace ast