/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "Node.hpp"
#include <vector>
#include <string>
#include <boost/smart_ptr.hpp>
#include <stdexcept>

namespace ast {

using std::vector;
using std::string;
using boost::shared_ptr;
using std::runtime_error;

class FuncArgTuple : public Node
{
public:
	FuncArgTuple() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kFuncArgTuple;
	}

	void setArgs(const vector<shared_ptr<Node> >& v)
	{
		if (v != args) {
			modify();
			args = v;
		}
	}
	const vector<shared_ptr<Node> >& getArgs()
	{
		return args;
	}

protected:
	vector<shared_ptr<Node> > args;
};

} // namespace ast