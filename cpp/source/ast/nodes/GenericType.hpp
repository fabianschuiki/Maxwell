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

class GenericType : public Node
{
public:
	GenericType() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kGenericType;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		return false;
	}

	virtual string getClassName() const { return "GenericType"; }

	virtual string describe(int depth = -1)
	{
		stringstream str, b;
		str << "*";
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

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<GenericType>& other = boost::dynamic_pointer_cast<GenericType>(o);
		if (!other) return false;
		return true;
	}

	typedef boost::shared_ptr<GenericType> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<GenericType>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<GenericType>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to GenericType."); return r; }
protected:
};

} // namespace ast