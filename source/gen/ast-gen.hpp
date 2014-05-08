/* Copyright © 2013 Fabian Schuiki */
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::list;
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
	string descriptionBody;

	struct NameCompare {
		bool operator() (const Node* a, const Node* b) const {
			return a->name < b->name;
		}
	};

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
		bool isInt;
		vector<string> allowedNodes;
		vector<string> allowedInterfaces;
	};
	typedef list<Field> Fields;
	typedef vector<Field*> Children;
	typedef set<const Node*, NameCompare> Interfaces;
	Fields attributes;
	Children children;
	Interfaces interfaces;

	Node& attr(string name, string type, bool child = false)
	{
		Field f = makeField(name, type, child);
		dropAttribute(f);
		attributes.push_back(f);
		return *this;
	}
	Node& child(string name, string type)
	{
		return attr(name, type, true);
	}

	Node& intf(const Node& interface)
	{
		for (Node::Fields::const_iterator it = interface.attributes.begin(); it != interface.attributes.end(); it++) {
			dropAttribute(*it);
			attributes.push_back(*it);
		}
		return *this;
	}

	Node& describe(const string& body)
	{
		descriptionBody = body;
		return *this;
	}

private:
	Field makeField(string name, string type, bool child);
	void dropAttribute(const Field& f)
	{
		for (Fields::iterator it = attributes.begin(); it != attributes.end();) {
			Fields::iterator is = it;
			it++;
			if ((*is).name == f.name) {
				if ((*is).cpp_type != f.cpp_type) {
					throw std::runtime_error("Adding attribute " + f.name + " to " + name + " with different cpp_types (existing " + (*is).cpp_type + " != new " + f.cpp_type + ").");
				}
				attributes.erase(is);
			}
		}
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