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

class FuncArgTuple : public Node
{
public:
	FuncArgTuple() : Node(),
		interfaceGraph(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kFuncArgTuple;
	}

	virtual string getClassName() const { return "FuncArgTuple"; }

	void setGraphPrev(const NodePtr& v)
	{
		if (!v && graphPrev) {
			modify();
			graphPrev.reset();
		}
		if (!graphPrev || v->getId() != graphPrev.id) {
			modify();
			graphPrev.set(v);
		}
	}
	const NodePtr& getGraphPrev()
	{
		return graphPrev.get(repository);
	}

	void setArgs(const NodeVector& v)
	{
		if (v != args) {
			modify();
			args = v;
		}
	}
	const NodeVector& getArgs()
	{
		return args;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "FuncArgTuple{…}";
		stringstream str, b;
		str << "FuncArgTuple{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = " << "\033[36m" << this->graphPrev.id << "\033[0m";
		if (!this->args.empty()) b << endl << "  \033[1margs\033[0m = " << indent(describeVector(this->args, depth-1)) << "";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
		e.encode(this->args);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->args);
	}

	virtual void updateHierarchy(const NodeId& id, Repository* repository = NULL, Node* parent = NULL)
	{
		Node::updateHierarchy(id, repository, parent);
		for (int i = 0; i < this->args.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->args[i]->updateHierarchy((id + "args") + buf, repository, this);
		}
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// .*
		if (true) {
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
			// graphPrev.*
			if (size >= 9 && path[0] == 'g' && path[1] == 'r' && path[2] == 'a' && path[3] == 'p' && path[4] == 'h' && path[5] == 'P' && path[6] == 'r' && path[7] == 'e' && path[8] == 'v') {
				// graphPrev
				if (size == 9) {
					return getGraphPrev();
				} else if (path[9] == '.') {
					return getGraphPrev()->resolvePath(path.substr(10));
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

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }

protected:
	NodeRef graphPrev;
	NodeVector args;

	// Interfaces
	GraphInterfaceImpl<FuncArgTuple> interfaceGraph;
};

} // namespace ast