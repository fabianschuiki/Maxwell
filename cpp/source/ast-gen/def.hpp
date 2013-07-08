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
	string parent;

	struct Field {
		bool ref; // whether or not only a reference to the node should be generated
		string name;
		string type;
		string cpp_type;
		bool isString;
		bool isArray;
		bool isNode;
		vector<string> allowedNodes;
		vector<string> allowedInterfaces;
	};
	typedef vector<Field> Fields;
	typedef set<const Node*> Interfaces;
	Fields attributes;
	Interfaces interfaces;

	Node& attr(string name, string type) { attributes.push_back(makeField(name, type)); return *this; }
	Node& intf(const Node& interface) {
		interfaces.insert(&interface);
		for (Node::Fields::const_iterator it = interface.attributes.begin(); it != interface.attributes.end(); it++) {
			attributes.push_back(*it);
		}
		return *this;
	}

private:
	Field makeField(string name, string type)
	{
		Field f;
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
		if (type == "string") {
			f.isString = true;
			f.cpp_type = "string";
		} else if (type.size() > 2 && type[0] == '[') {
			f.isArray = true;
			f.cpp_type = "NodeVector";
		} else {
			f.isNode = true;
			f.cpp_type = "NodePtr";
			if (type != "any") {
				f.allowedNodes.push_back(type);
			}
		}
		return f;
	}
};

class Builder
{
public:
	Node& operator() (const string& nodeName, const string& parentName = "Node")
	{
		Node &n = (nodeName.size() >= 1 && nodeName[0] == '@' ? interfaces[nodeName] : nodes[nodeName]);
		n.name = nodeName;
		n.parent = parentName;
		return n;
	}
	typedef map<string, Node> Nodes;
	Nodes nodes;
	Nodes interfaces;
};

typedef vector<string> Headers;

void buildAST(Builder &node);