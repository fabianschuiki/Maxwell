/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
#include "../Coder.hpp"
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

class FuncArg : public Node
{
public:
	FuncArg() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kFuncArg;
	}

	virtual string getClassName() const { return "FuncArg"; }

	void setGraphPrev(const NodePtr& v)
	{
		if (v != graphPrev) {
			modify();
			graphPrev = v;
			graphPrev_ref.clear();
		}
	}
	const NodePtr& getGraphPrev()
	{
	if (!graphPrev_ref.empty()) {
		graphPrev = resolveReference(graphPrev_ref);
		graphPrev_ref.clear();
	}
		return graphPrev;
	}

	void setName(const string& v)
	{
		if (v != name) {
			modify();
			name = v;
		}
	}
	const string& getName()
	{
		return name;
	}

	void setType(const string& v)
	{
		if (v != type) {
			modify();
			type = v;
		}
	}
	const string& getType()
	{
		return type;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "FuncArg{…}";
		stringstream str, b;
		str << "FuncArg{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = " << indent(this->graphPrev->describe(depth-1));
		if (!this->name.empty()) b << endl << "  \033[1mname\033[0m = '\033[33m" << this->name << "\033[0m'";
		if (!this->type.empty()) b << endl << "  \033[1mtype\033[0m = '\033[33m" << this->type << "\033[0m'";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev, &graphPrev_ref);
		e.encode(this->name);
		e.encode(this->type);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev, &graphPrev_ref);
		d.decode(this->name);
		d.decode(this->type);
	}

	virtual void updateHierarchy(const NodeId& id, const weak_ptr<Repository>& repository = weak_ptr<Repository>(), const weak_ptr<Node>& parent = weak_ptr<Node>())
	{
		Node::updateHierarchy(id, repository, parent);
		const NodePtr& self(shared_from_this());
		if (this->graphPrev) this->graphPrev->updateHierarchy(id + "graphPrev", repository, self);
	}

protected:
	NodePtr graphPrev;
	NodeId graphPrev_ref;
	string name;
	string type;
};

} // namespace ast