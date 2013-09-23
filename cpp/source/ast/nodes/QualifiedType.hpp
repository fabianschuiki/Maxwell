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
#include <cstdio>

namespace ast {

using std::vector;
using std::string;
using std::stringstream;
using std::endl;
using std::runtime_error;

class QualifiedType : public Node
{
public:
	QualifiedType() : Node() {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kQualifiedType;
	}

	virtual bool implements(Interface i)
	{
		if (Node::implements(i)) return true;
		return false;
	}

	virtual string getClassName() const { return "QualifiedType"; }

	void setMembers(const NodeVector& v)
	{
		if (!equal(v, members)) {
			modify("members");
			members = v;
		}
	}
	const NodeVector& getMembers(bool required = true)
	{
		const NodeVector& v = members;
		return v;
	}

	void setFuncs(const NodeVector& v)
	{
		if (!equal(v, funcs)) {
			modify("funcs");
			funcs = v;
		}
	}
	const NodeVector& getFuncs(bool required = true)
	{
		const NodeVector& v = funcs;
		return v;
	}

	void setNatives(const NodeVector& v)
	{
		if (!equal(v, natives)) {
			modify("natives");
			natives = v;
		}
	}
	const NodeVector& getNatives(bool required = true)
	{
		const NodeVector& v = natives;
		return v;
	}

	void setRanges(const NodeVector& v)
	{
		if (!equal(v, ranges)) {
			modify("ranges");
			ranges = v;
		}
	}
	const NodeVector& getRanges(bool required = true)
	{
		const NodeVector& v = ranges;
		return v;
	}

	virtual string describe(int depth = -1)
	{
		stringstream str, b;
		if (depth == 0) return "QualifiedType{…}";
		str << "QualifiedType{";
		if (!this->members.empty()) b << endl << "  \033[1mmembers\033[0m = " << indent(describeVector(this->members, depth-1));
		if (!this->funcs.empty()) b << endl << "  \033[1mfuncs\033[0m = " << indent(describeVector(this->funcs, depth-1));
		if (!this->natives.empty()) b << endl << "  \033[1mnatives\033[0m = " << indent(describeVector(this->natives, depth-1));
		if (!this->ranges.empty()) b << endl << "  \033[1mranges\033[0m = " << indent(describeVector(this->ranges, depth-1));
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->members);
		e.encode(this->funcs);
		e.encode(this->natives);
		e.encode(this->ranges);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->members);
		d.decode(this->funcs);
		d.decode(this->natives);
		d.decode(this->ranges);
	}

	virtual void updateHierarchyOfChildren()
	{
		for (int i = 0; i < this->members.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->members[i]->updateHierarchy((id + "members") + buf, repository, this);
		}
		for (int i = 0; i < this->funcs.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->funcs[i]->updateHierarchy((id + "funcs") + buf, repository, this);
		}
		for (int i = 0; i < this->natives.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->natives[i]->updateHierarchy((id + "natives") + buf, repository, this);
		}
		for (int i = 0; i < this->ranges.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->ranges[i]->updateHierarchy((id + "ranges") + buf, repository, this);
		}
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// .*
		if (true) {
			// funcs.*
			if (size >= 5 && path[0] == 'f' && path[1] == 'u' && path[2] == 'n' && path[3] == 'c' && path[4] == 's') {
				// funcs
				if (size == 5) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[5] == '.') {
					size_t dot = path.find(".", 6);
					string idx_str = path.substr(6, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getFuncs();
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
			// members.*
			if (size >= 7 && path[0] == 'm' && path[1] == 'e' && path[2] == 'm' && path[3] == 'b' && path[4] == 'e' && path[5] == 'r' && path[6] == 's') {
				// members
				if (size == 7) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[7] == '.') {
					size_t dot = path.find(".", 8);
					string idx_str = path.substr(8, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getMembers();
					if (idx < 0 || idx >= a.size()) {
						throw std::runtime_error("Index into array '" + path.substr(0, 7) + "' is out of bounds.");
					}
					if (dot == string::npos) {
						return a[idx];
					} else {
						return a[idx]->resolvePath(path.substr(dot + 1));
					}
				}
			}
			// natives.*
			if (size >= 7 && path[0] == 'n' && path[1] == 'a' && path[2] == 't' && path[3] == 'i' && path[4] == 'v' && path[5] == 'e' && path[6] == 's') {
				// natives
				if (size == 7) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[7] == '.') {
					size_t dot = path.find(".", 8);
					string idx_str = path.substr(8, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getNatives();
					if (idx < 0 || idx >= a.size()) {
						throw std::runtime_error("Index into array '" + path.substr(0, 7) + "' is out of bounds.");
					}
					if (dot == string::npos) {
						return a[idx];
					} else {
						return a[idx]->resolvePath(path.substr(dot + 1));
					}
				}
			}
			// ranges.*
			if (size >= 6 && path[0] == 'r' && path[1] == 'a' && path[2] == 'n' && path[3] == 'g' && path[4] == 'e' && path[5] == 's') {
				// ranges
				if (size == 6) {
					throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
				} else if (path[6] == '.') {
					size_t dot = path.find(".", 7);
					string idx_str = path.substr(7, dot);
					int idx = atoi(idx_str.c_str());
					const NodeVector& a = getRanges();
					if (idx < 0 || idx >= a.size()) {
						throw std::runtime_error("Index into array '" + path.substr(0, 6) + "' is out of bounds.");
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
		v.insert(v.end(), this->members.begin(), this->members.end());
		v.insert(v.end(), this->funcs.begin(), this->funcs.end());
		v.insert(v.end(), this->natives.begin(), this->natives.end());
		v.insert(v.end(), this->ranges.begin(), this->ranges.end());
		return v;
	}

	virtual bool equalTo(const NodePtr& o)
	{
		const shared_ptr<QualifiedType>& other = boost::dynamic_pointer_cast<QualifiedType>(o);
		if (!other) return false;
		if (!equal(this->members, other->members)) return false;
		if (!equal(this->funcs, other->funcs)) return false;
		if (!equal(this->natives, other->natives)) return false;
		if (!equal(this->ranges, other->ranges)) return false;
		return true;
	}

	typedef boost::shared_ptr<QualifiedType> Ptr;
	template<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<QualifiedType>(n); }
	template<typename T> static Ptr needFrom(const T& n) { Ptr r = boost::dynamic_pointer_cast<QualifiedType>(n); if (!r) throw std::runtime_error("Node " + n->getId().str() + " cannot be dynamically casted to QualifiedType."); return r; }
protected:
	NodeVector members;
	NodeVector funcs;
	NodeVector natives;
	NodeVector ranges;
};

} // namespace ast