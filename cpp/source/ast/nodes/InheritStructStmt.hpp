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

class InheritStructStmt : public Node
{
public:
	InheritStructStmt() : Node(),
		interfaceGraph(this),
		interfaceNamed(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kInheritStructStmt;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kGraphInterface) return true;
		if (i == kNamedInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "InheritStructStmt"; }

	void setGraphPrev(const NodePtr& v)
	{
		if (!v && graphPrev) {
			modify("graphPrev");
			graphPrev.reset();
		}
		if (!graphPrev || v->getId() != graphPrev.id) {
			modify("graphPrev");
			graphPrev.set(v);
		}
	}
	void setGraphPrev(const NodeId& v)
	{
		if (v != graphPrev.id) {
			modify("graphPrev");
			graphPrev.set(v);
		}
	}
	const NodePtr& getGraphPrev(bool required = true)
	{
		const NodePtr& v = graphPrev.get(repository);
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have graphPrev set to a non-null value.");
		}
		return v;
	}

	void setName(const string& v)
	{
		if (!equal(v, name)) {
			modify("name");
			name = v;
		}
	}
	const string& getName(bool required = true)
	{
		const string& v = name;
		if (required && v.empty()) {
			throw runtime_error("Node " + getId().str() + " is required to have a non-empty string name set.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "InheritStructStmt{…}";
		stringstream str, b;
		str << "InheritStructStmt{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
		if (!this->name.empty()) b << endl << "  \033[1mname\033[0m = \033[33m\"" << this->name << "\"\033[0m";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
		e.encode(this->name);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->name);
	}

	virtual void updateHierarchyOfChildren()
	{
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

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<InheritStructStmt>& other = boost::dynamic_pointer_cast<InheritStructStmt>(o);
		if (!other) return false;
		if (!equal(this->graphPrev, other->graphPrev)) return false;
		if (!equal(this->name, other->name)) return false;
		return true;
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }

	typedef boost::shared_ptr<InheritStructStmt> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<InheritStructStmt>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<InheritStructStmt>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to InheritStructStmt."); return r; }
protected:
	NodeRef graphPrev;
	string name;

	// Interfaces
	GraphInterfaceImpl<InheritStructStmt> interfaceGraph;
	NamedInterfaceImpl<InheritStructStmt> interfaceNamed;
};

} // namespace ast