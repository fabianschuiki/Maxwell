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
	Fields children, attributes;

	Node& child(string name, string type) { children.push_back(makeField(name, type)); return *this; }
	Node& attr(string name, string type) { attributes.push_back(makeField(name, type)); return *this; }

private:
	Field makeField(string name, string type)
	{
		Field f;
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
			f.cpp_type = "NodeRef";
			f.allowedNodes.push_back(type);
		}
		return f;
	}
};

class Builder
{
public:
	Node& operator() (const string& nodeName, const string& parentName = "Node")
	{
		Node &n = nodes[nodeName];
		n.name = nodeName;
		n.parent = parentName;
		return n;
	}
	typedef map<string, Node> Nodes;
	Nodes nodes;
};

typedef vector<string> Headers;

void buildAST(Builder &node);