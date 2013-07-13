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

class TupleType : public Node
{
public:
	TupleType() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kTupleType;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		return false;
	}

	virtual string getClassName() const { return "TupleType"; }

	void setArgs(const NodeVector& v)
	{
		if (v != args) {
			modify();
			args = v;
		}
	}
	const NodeVector& getArgs(bool required = true)
	{
		const NodeVector& v = args;
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "TupleType{…}";
		stringstream str, b;
					bool first = true;			for (NodeVector::iterator it = args.begin(); it != args.end(); it++) {				if (!first) str << ", ";				first = false;				str << (*it)->describe(depth-1);			}
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->args);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->args);
	}

	virtual void updateHierarchyOfChildren()
	{
		for (int i = 0; i < this->args.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->args[i]->updateHierarchy((id + "args") + buf, repository, this);
		}
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// args.*
		if (size >= 4 && path[0] == 'a' && path[1] == 'r' && path[2] == 'g' && path[3] == 's') {
			// args
			if (size == 4) {
				throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
			} else if (path[4] == '.') {
				size_t dot = path.find(".", 5);
				string idx_str = path.substr(5, dot);
				int idx = atoi(idx_str.c_str());
				const NodeVector& a = getArgs();
				if (idx < 0 || idx >= a.size()) {
					throw std::runtime_error("Index into array '" + path.substr(0, 4) + "' is out of bounds.");
				}
				if (dot == string::npos) {
					return a[idx];
				} else {
					return a[idx]->resolvePath(path.substr(dot + 1));
				}
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		v.insert(v.end(), this->args.begin(), this->args.end());
		return v;
	}

	typedef boost::shared_ptr<TupleType> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<TupleType>(n); }
protected:
	NodeVector args;
};

} // namespace ast