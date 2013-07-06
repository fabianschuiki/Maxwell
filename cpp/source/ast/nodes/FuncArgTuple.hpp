/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
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

	virtual string getClassName() const { return "FuncArgTuple"; }

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

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "FuncArgTuple{…}";
		stringstream str, b;
		str << "FuncArgTuple{";
		if (!this->args.empty()) b << endl << "  \033[1margs\033[0m = [" << this->args.size() << " nodes]";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}
protected:
	vector<shared_ptr<Node> > args;
};

} // namespace ast