/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <iostream>
#include <string>
#include <boost/smart_ptr.hpp>

namespace ast {

using std::ostream;
using std::string;
using boost::shared_ptr;

class Node;

/**
 * @brief Encodes/decodes AST nodes.
 */
class Serializer
{
public:
	void encode(ostream& out, const shared_ptr<Node>& node);
	string encode(const shared_ptr<Node>& node);
};

} // namespace ast