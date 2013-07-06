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

class FuncBody : public Node
{
public:
	FuncBody() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kFuncBody;
	}

	virtual string getClassName() const { return "FuncBody"; }

	void setStmts(const vector<shared_ptr<Node> >& v)
	{
		if (v != stmts) {
			modify();
			stmts = v;
		}
	}
	const vector<shared_ptr<Node> >& getStmts()
	{
		return stmts;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "FuncBody{…}";
		stringstream str, b;
		str << "FuncBody{";
		if (!this->stmts.empty()) b << endl << "  \033[1mstmts\033[0m = [" << this->stmts.size() << " nodes]";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}
protected:
	vector<shared_ptr<Node> > stmts;
};

} // namespace ast