/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "Node.hpp"
#include <string>
#include <boost/smart_ptr.hpp>

namespace ast {

using std::string;
using boost::shared_ptr;

class Node;

/// Encoder interface.
class Encoder
{
public:
	virtual void encode(const NodePtr& node, bool ref = false) = 0;
	virtual void encode(const string& str) = 0;
	virtual void encode(const NodeVector& nodes, bool ref = false) = 0;
};

/// Decoder interface.
class Decoder
{
public:
	virtual void decode(NodePtr& node, bool ref = false) = 0;
	virtual void decode(string& str) = 0;
	virtual void decode(NodeVector& nodes, bool ref = false) = 0;
};

} // namespace ast