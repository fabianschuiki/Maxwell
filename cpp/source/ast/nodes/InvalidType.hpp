/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
#include "../Coder.hpp"
#include "interfaces.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <boost/smart_ptr.hpp>
#include <stdexcept>

namespace ast {

using std::vector;
using std::string;
using std::stringstream;
using std::endl;
using std::runtime_error;

class InvalidType : public Node
{
public:
	InvalidType() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kInvalidType;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		return false;
	}

	virtual string getClassName() const { return "InvalidType"; }

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "InvalidType{…}";
		stringstream str, b;
		str << "InvalidType{";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
	}

	virtual void decode(Decoder& d)
	{
	}

	virtual void updateHierarchyOfChildren()
	{
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

protected:
};

} // namespace ast