/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "Node.hpp"
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
	void encode(ostream& out, const NodeRef& node);
	string encode(const NodeRef& node);

	NodeRef decode(istream& in);
	NodeRef decode(const string& str);
};

} // namespace ast