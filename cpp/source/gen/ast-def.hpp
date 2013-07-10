/* Copyright © 2013 Fabian Schuiki */
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <boost/filesystem.hpp>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::ofstream;
using std::vector;

class Node
{
public:
	string name;
	string intfName;
	string parent;

	struct Field {
		bool ref; // whether or not only a reference to the node should be generated
		bool child;
		string name;
		string type;
		string cpp_type;
		bool isString;
		bool isArray;
		bool isNode;
		bool isBool;
		vector<string> allowedNodes;
		vector<string> allowedInterfaces;
	};
	typedef vector<Field> Fields;
	typedef vector<int> FieldIndices;
	typedef set<const Node*> Interfaces;
	Fields attributes;
	FieldIndices children;
	Interfaces interfaces;

	Node& attr(string name, string type, bool child = false) { attributes.push_back(makeField(name, type, child)); return *this; }
	Node& child(string name, string type) { children.push_back(attributes.size()); return attr(name, type, true); }
	Node& intf(const Node& interface) {
		interfaces.insert(&interface);
		for (Node::Fields::const_iterator it = interface.attributes.begin(); it != interface.attributes.end(); it++) {
			attributes.push_back(*it);
		}
		return *this;
	}

private:
	Field makeField(string name, string type, bool child)
	{
		Field f;
		f.child = child;
		if (type.size() >= 1 && type[0] == '&') {
			type = type.substr(1);
			f.ref = true;
		} else {
			f.ref = false;
		}
		f.name = name;
		f.type = type;
		f.isString = false;
		f.isArray = false;
		f.isNode = false;
		f.isBool = false;
		if (type == "string") {
			f.isString = true;
			f.cpp_type = "string";
		} else if (type == "bool") {
			f.isBool = true;
			f.cpp_type = "bool";
		} else if (type.size() > 2 && type[0] == '[') {
			f.isArray = true;
			f.cpp_type = "NodeVector";
		} else {
			f.isNode = true;
			f.cpp_type = "NodePtr";
			if (type != "any") {
				size_t pipe = -1, offset = 0;
				do {
					offset = pipe + 1;
					pipe = type.find("|", pipe + 1);
					string subtype = type.substr(offset, pipe);
					if (subtype.size() >= 1 && subtype[0] == '@') {
						f.allowedInterfaces.push_back(subtype.substr(1));
					} else {
						f.allowedNodes.push_back(subtype);
					}
				} while (pipe != string::npos);
			}
		}
		return f;
	}
};

class Builder
{
public:
	Node& operator() (string nodeName, const string& parentName = "Node")
	{
		if (nodeName.size() >= 1 && nodeName[0] == '@') {
			nodeName = nodeName.substr(1);
			Node &n = interfaces[nodeName];
			n.name = nodeName;
			n.intfName = nodeName + "Interface";
			n.parent = parentName;
			return n;
		} else {
			Node &n = nodes[nodeName];
			n.name = nodeName;
			n.parent = parentName;
			return n;
		}
	}
	typedef map<string, Node> Nodes;
	Nodes nodes;
	Nodes interfaces;
};

typedef vector<string> Headers;

void buildAST(Builder &node);