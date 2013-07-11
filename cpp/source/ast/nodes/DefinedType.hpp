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

class DefinedType : public Node
{
public:
	DefinedType() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kDefinedType;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		return false;
	}

	virtual string getClassName() const { return "DefinedType"; }

	void setDefinition(const NodePtr& v)
	{
		if (!v && definition) {
			modify();
			definition.reset();
		}
		if (!definition || v->getId() != definition.id) {
			modify();
			definition.set(v);
		}
	}
	void setDefinition(const NodeId& v)
	{
		if (v != definition.id) {
			modify();
			definition.set(v);
		}
	}
	const NodePtr& getDefinition(bool required = true)
	{
		const NodePtr& v = definition.get(repository);
		if (required && !v) {
			throw runtime_error("Node " + getId().str() + " is required to have definition set to a non-null value.");
		}
		return v;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "DefinedType{…}";
		stringstream str, b;
		str << "DefinedType{";
		if (this->definition) b << endl << "  \033[1mdefinition\033[0m = " << "\033[36m" << this->definition.id << "\033[0m";
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->definition);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->definition);
	}

	virtual void updateHierarchyOfChildren()
	{
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// definition.*
		if (size >= 10 && path[0] == 'd' && path[1] == 'e' && path[2] == 'f' && path[3] == 'i' && path[4] == 'n' && path[5] == 'i' && path[6] == 't' && path[7] == 'i' && path[8] == 'o' && path[9] == 'n') {
			// definition
			if (size == 10) {
				return getDefinition();
			} else if (path[10] == '.') {
				return getDefinition()->resolvePath(path.substr(11));
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

protected:
	NodeRef definition;
};

} // namespace ast