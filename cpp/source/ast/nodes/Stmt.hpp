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

class Stmt : public Node
{
public:
	Stmt() : Node(),
		interfaceGraph(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kStmt;
	}

	virtual string getClassName() const { return "Stmt"; }

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

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "Stmt{…}";
		stringstream str, b;
		str << "Stmt{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = " << "\033[36m" << this->graphPrev.id << "\033[0m";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
	}

	virtual void updateHierarchy(const NodeId& id, Repository* repository = NULL, Node* parent = NULL)
	{
		Node::updateHierarchy(id, repository, parent);
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// graphPrev.*
		if (size >= 9 && path[0] == 'g' && path[1] == 'r' && path[2] == 'a' && path[3] == 'p' && path[4] == 'h' && path[5] == 'P' && path[6] == 'r' && path[7] == 'e' && path[8] == 'v') {
			// graphPrev
			if (size == 9) {
				return getGraphPrev();
			} else if (path[9] == '.') {
				return getGraphPrev()->resolvePath(path.substr(10));
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }

protected:
	NodeRef graphPrev;

	// Interfaces
	GraphInterfaceImpl<Stmt> interfaceGraph;
};

} // namespace ast