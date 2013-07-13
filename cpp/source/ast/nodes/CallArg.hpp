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

class CallArg : public Node
{
public:
	CallArg() : Node(),
		interfaceCallArg(this),
		interfaceNamed(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kCallArg;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		if (i == kCallArgInterface) return true;
		if (i == kNamedInterface) return true;
		return false;
	}

	virtual string getClassName() const { return "CallArg"; }

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

	void setExpr(const NodePtr& v)
	{
		if (v && !v->implements(kTypeInterface)) {
			throw runtime_error("'expr' needs to be of kind {} or implement interface {Type}, got " + v->getClassName() + " instead.");
		}
		if (!v && expr) {
			modify("expr");
			expr.reset();
		}
		if (!expr || v->getId() != expr.id) {
			modify("expr");
			expr.set(v);
		}
	}
	void setExpr(const NodeId& v)
	{
		if (v != expr.id) {
			modify("expr");
			expr.set(v);
		}
	}
	const NodePtr& getExpr(bool required = true)
	{
		const NodePtr& v = expr.get(repository);
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have expr set to a non-null value.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "CallArg{…}";
		stringstream str, b;
		str << "CallArg{";
		if (!this->name.empty()) b << endl << "  \033[1mname\033[0m = \033[33m\"" << this->name << "\"\033[0m";
		if (this->expr) b << endl << "  \033[1mexpr\033[0m = \033[36m" << this->expr.id << "\033[0m";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->name);
		e.encode(this->expr);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->name);
		d.decode(this->expr);
	}

	virtual void updateHierarchyOfChildren()
	{
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// expr.*
		if (size >= 4 && path[0] == 'e' && path[1] == 'x' && path[2] == 'p' && path[3] == 'r') {
			// expr
			if (size == 4) {
				return getExpr();
			} else if (path[4] == '.') {
				return getExpr()->resolvePath(path.substr(5));
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<CallArg>& other = boost::dynamic_pointer_cast<CallArg>(o);
		if (!other) return false;
		if (!equal(this->name, other->name)) return false;
		if (!equal(this->expr, other->expr)) return false;
		return true;
	}

	// Interfaces
	virtual CallArgInterface* asCallArg() { return &this->interfaceCallArg; }
	virtual NamedInterface* asNamed() { return &this->interfaceNamed; }

	typedef boost::shared_ptr<CallArg> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<CallArg>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<CallArg>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to CallArg."); return r; }
protected:
	string name;
	NodeRef expr;

	// Interfaces
	CallArgInterfaceImpl<CallArg> interfaceCallArg;
	NamedInterfaceImpl<CallArg> interfaceNamed;
};

} // namespace ast