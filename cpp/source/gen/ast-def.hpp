/* Copyright © 2013 Fabian Schuiki */
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::ofstream;
using std::vector;

class Builder;

class Node
{
public:
	Builder* builder;
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
		for (Interfaces::iterator it = interface.interfaces.begin(); it != interface.interfaces.end(); it++) {
			interfaces.insert(*it);
		}
		for (Node::Fields::const_iterator it = interface.attributes.begin(); it != interface.attributes.end(); it++) {
			attributes.push_back(*it);
		}
		return *this;
	}

private:
	Field makeField(string name, string type, bool child);
};

class Builder
{
public:
	Node& operator() (string nodeName, const string& parentName = "Node")
	{
		if (nodeName.size() >= 1 && nodeName[0] == '@') {
			nodeName = nodeName.substr(1);
			Node &n = interfaces[nodeName];
			n.builder = this;
			n.name = nodeName;
			n.intfName = nodeName + "Interface";
			n.parent = parentName;
			return n;
		} else {
			Node &n = nodes[nodeName];
			n.builder = this;
			n.name = nodeName;
			n.parent = parentName;
			return n;
		}
	}
	typedef map<string, Node> Nodes;
	Nodes nodes;
	Nodes interfaces;
	typedef map<string, string> Groups;
	Groups groups;
};

typedef vector<string> Headers;

void buildAST(Builder &node);