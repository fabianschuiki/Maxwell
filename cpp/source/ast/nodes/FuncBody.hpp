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

class FuncBody : public Node
{
public:
	FuncBody() : Node(),
		interfaceGraph(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kFuncBody;
	}

	virtual string getClassName() const { return "FuncBody"; }

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

	void setStmts(const NodeVector& v)
	{
		if (v != stmts) {
			modify();
			stmts = v;
		}
	}
	const NodeVector& getStmts()
	{
		return stmts;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "FuncBody{…}";
		stringstream str, b;
		str << "FuncBody{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = " << "\033[36m" << this->graphPrev.id << "\033[0m";
		if (!this->stmts.empty()) b << endl << "  \033[1mstmts\033[0m = " << indent(describeVector(this->stmts, depth-1)) << "";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
		e.encode(this->stmts);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->stmts);
	}

	virtual void updateHierarchy(const NodeId& id, Repository* repository = NULL, Node* parent = NULL)
	{
		Node::updateHierarchy(id, repository, parent);
		for (int i = 0; i < this->stmts.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->stmts[i]->updateHierarchy((id + "stmts") + buf, repository, this);
		}
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// .*
		if (true) {
			// graphPrev.*
			if (size >= 9 && path[0] == 'g' && path[1] == 'r' && path[2] == 'a' && path[3] == 'p' && path[4] == 'h' && path[5] == 'P' && path[6] == 'r' && path[7] == 'e' && path[8] == 'v') {
				// graphPrev
				if (size == 9) {
					return getGraphPrev();
				} else if (path[9] == '.') {
					return getGraphPrev()->resolvePath(path.substr(10));
				}
			}
			// stmts.*
			if (size >= 5 && path[0] == 's' && path[1] == 't' && path[2] == 'm' && path[3] == 't' && path[4] == 's') {
				// stmts
				if (size == 5) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[5] == '.') {
					size_t dot = path.find(".", 6);
					string idx_str = path.substr(6, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getStmts();
					if (idx < 0 || idx >= a.size()) {
						throw std::runtime_error("Index into array '" + path.substr(0, 5) + "' is out of bounds.");
					}
					if (dot == string::npos) {
						return a[idx];
					} else {
						return a[idx]->resolvePath(path.substr(dot + 1));
					}
				}
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		v.insert(v.end(), this->stmts.begin(), this->stmts.end());
		return v;
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }

protected:
	NodeRef graphPrev;
	NodeVector stmts;

	// Interfaces
	GraphInterfaceImpl<FuncBody> interfaceGraph;
};

} // namespace ast