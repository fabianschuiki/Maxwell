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

class ImplAccessor : public Node
{
public:
	ImplAccessor() : Node(),
		interfaceGraph(this),
		interfaceCallable(this),
		interfaceNamed(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kImplAccessor;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kGraphInterface) return true;
		if (i == kCallableInterface) return true;
		if (i == kNamedInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "ImplAccessor"; }

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

	void setIn(const NodeVector& v)
	{
		if (!equal(v, in)) {
			modify("in");
			in = v;
		}
	}
	const NodeVector& getIn(bool required = true)
	{
		const NodeVector& v = in;
		return v;
	}

	void setOut(const NodeVector& v)
	{
		if (!equal(v, out)) {
			modify("out");
			out = v;
		}
	}
	const NodeVector& getOut(bool required = true)
	{
		const NodeVector& v = out;
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "ImplAccessor{…}";
		stringstream str, b;
		str << "ImplAccessor{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = \033[36m" << this->graphPrev.id << "\033[0m";
		if (!this->name.empty()) b << endl << "  \033[1mname\033[0m = \033[33m\"" << this->name << "\"\033[0m";
		if (!this->in.empty()) b << endl << "  \033[1min\033[0m = " << indent(describeVector(this->in, depth-1));
		if (!this->out.empty()) b << endl << "  \033[1mout\033[0m = " << indent(describeVector(this->out, depth-1));
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
		e.encode(this->name);
		e.encode(this->in);
		e.encode(this->out);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->name);
		d.decode(this->in);
		d.decode(this->out);
	}

	virtual void updateHierarchyOfChildren()
	{
		for (int i = 0; i < this->in.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->in[i]->updateHierarchy((id + "in") + buf, repository, this);
		}
		for (int i = 0; i < this->out.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->out[i]->updateHierarchy((id + "out") + buf, repository, this);
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
			// in.*
			if (size >= 2 && path[0] == 'i' && path[1] == 'n') {
				// in
				if (size == 2) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[2] == '.') {
					size_t dot = path.find(".", 3);
					string idx_str = path.substr(3, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getIn();
					if (idx < 0 || idx >= a.size()) {
						throw std::runtime_error("Index into array '" + path.substr(0, 2) + "' is out of bounds.");
					}
					if (dot == string::npos) {
						return a[idx];
					} else {
						return a[idx]->resolvePath(path.substr(dot + 1));
					}
				}
			}
			// out.*
			if (size >= 3 && path[0] == 'o' && path[1] == 'u' && path[2] == 't') {
				// out
				if (size == 3) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[3] == '.') {
					size_t dot = path.find(".", 4);
					string idx_str = path.substr(4, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getOut();
					if (idx < 0 || idx >= a.size()) {
						throw std::runtime_error("Index into array '" + path.substr(0, 3) + "' is out of bounds.");
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
		v.insert(v.end(), this->in.begin(), this->in.end());
		v.insert(v.end(), this->out.begin(), this->out.end());
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<ImplAccessor>& other = boost::dynamic_pointer_cast<ImplAccessor>(o);
		if (!other) return false;
		if (!equal(this->graphPrev, other->graphPrev)) return false;
		if (!equal(this->name, other->name)) return false;
		if (!equal(this->in, other->in)) return false;
		if (!equal(this->out, other->out)) return false;
		return true;
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual CallableInterface* asCallable() { return &this->interfaceCallable; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }

	typedef boost::shared_ptr<ImplAccessor> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<ImplAccessor>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<ImplAccessor>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to ImplAccessor."); return r; }
protected:
	NodeRef graphPrev;
	string name;
	NodeVector in;
	NodeVector out;

	// Interfaces
	GraphInterfaceImpl<ImplAccessor> interfaceGraph;
	CallableInterfaceImpl<ImplAccessor> interfaceCallable;
	NamedInterfaceImpl<ImplAccessor> interfaceNamed;
};

} // namespace ast