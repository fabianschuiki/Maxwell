/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "maxwell/ast/Node.hpp"
#include <iostream>
#include <string>

namespace ast {

using std::ostream;
using std::istream;
using std::string;

class Node;

/**
 * @brief Encodes/decodes AST nodes.
 */
class Serializer
{
public:
	void encode(ostream& out, const NodePtr& node);
	string encode(const NodePtr& node);

	NodePtr decode(istream& in);
	NodePtr decode(const string& str);
};

} // namespace ast
