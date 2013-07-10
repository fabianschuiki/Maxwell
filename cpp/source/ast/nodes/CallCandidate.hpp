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

class CallCandidate : public Node
{
public:
	CallCandidate() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kCallCandidate;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		return false;
	}

	virtual string getClassName() const { return "CallCandidate"; }

	void setFunc(const NodePtr& v)
	{
		if (v && !v->isKindOf(kFuncDef)) {
			throw runtime_error("'func' needs to be of kind {FuncDef} or implement interface {}, got " + v->getClassName() + " instead.");
		}
		if (!v && func) {
			modify();
			func.reset();
		}
		if (!func || v->getId() != func.id) {
			modify();
			func.set(v);
		}
	}
	void setFunc(const NodeId& v)
	{
		if (v != func.id) {
			modify();
			func.set(v);
		}
	}
	const NodePtr& getFunc(bool required = true)
	{
		const NodePtr& v = func.get(repository);
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have func set to a non-null value.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "CallCandidate{…}";
		stringstream str, b;
		str << "CallCandidate{";
		if (this->func) b << endl << "  \033[1mfunc\033[0m = " << "\033[36m" << this->func.id << "\033[0m";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->func);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->func);
	}

	virtual void updateHierarchy(const NodeId& id, Repository* repository = NULL, Node* parent = NULL)
	{
		Node::updateHierarchy(id, repository, parent);
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// func.*
		if (size >= 4 && path[0] == 'f' && path[1] == 'u' && path[2] == 'n' && path[3] == 'c') {
			// func
			if (size == 4) {
				return getFunc();
			} else if (path[4] == '.') {
				return getFunc()->resolvePath(path.substr(5));
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

protected:
	NodeRef func;
};

} // namespace ast