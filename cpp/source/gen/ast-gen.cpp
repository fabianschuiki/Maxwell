/* Copyright © 2013 Fabian Schuiki */

/**
 * @file This tool generates the C++ header and source files for the abstract
 * syntax tree.
 */

#include "ast-def.hpp"

Node::Field Node::makeField(string name, string type, bool child)
{
	Field f;
	f.child = child;
	if (type.size() >= 1 && type[0] == '&') {
		type = type.substr(1);
		f.ref = true;
	} else {
		f.ref = false;
	}
	for (Builder::Groups::reverse_iterator it = builder->groups.rbegin(); it != builder->groups.rend(); it++) {
		boost::replace_all(type, "#" + it->first, it->second);
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
				pipe = type.find("|", offset);
				string subtype = type.substr(offset, pipe - offset);
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

void makeTypesHeader(const boost::filesystem::path& output, const Builder& builder)
{
	boost::filesystem::path path = output;
	path /= "types.hpp";
	ofstream h(path.c_str());
	h << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	h << "#pragma once\n\n";
	h << "namespace ast {\n\n";

	h << "/// Node kinds that may be used to test whether a Node is of a given subclass.\n";
	h << "typedef enum {";
	bool first = true;
	for (Builder::Nodes::const_iterator it = builder.nodes.begin(); it != builder.nodes.end(); it++) {
		h << (first ? "\n" : ",\n");
		h << "\tk" << it->first;
		first = false;
	}
	h << "\n} Kind;\n\n";

	h << "/// Node interfaces that may be used to test whether a Node implements a given interface.\n";
	h << "typedef enum {";
	first = true;
	for (Builder::Nodes::const_iterator it = builder.interfaces.begin(); it != builder.interfaces.end(); it++) {
		h << (first ? "\n" : ",\n");
		h << "\tk" << it->second.intfName;
		first = false;
	}
	h << "\n} Interface;\n";

	h << "\n} // namespace ast\n\n";
}

typedef set<string> NodeNames;
void generateFactoryBody(std::ostream& out, NodeNames names, int indent, string basePrefix = "")
{
	string pad(indent, '\t');

	// Extract the prefixes.
	string prefix;
	string commonPrefix = basePrefix;
	bool common = true;
	do {
		NodeNames newNames;
		NodeNames::iterator nambeg = names.begin();
		bool singleMatch = false;
		if ((*nambeg).size() == commonPrefix.size()) {
			newNames.insert(*nambeg);
			names.erase(nambeg);
			//cout << "one name equals common prefix " << commonPrefix << "\n";
			prefix = commonPrefix;
			singleMatch = true;
		} else {
			prefix = commonPrefix + (*nambeg)[commonPrefix.size()];
			//cout << "prefix " << prefix << "\n";
			for (NodeNames::iterator it = names.begin(); it != names.end();) {
				string name = *it;
				NodeNames::iterator tmpit = it;
				it++;
				if (name.size() < prefix.size() || name.substr(0, prefix.size()) != prefix)
					break;
				newNames.insert(name);
				names.erase(tmpit);
				//cout << "- adding " << name << "\n";
			}
		}
		if (names.empty() && common && !singleMatch) {
			commonPrefix = prefix;
			names = newNames;
			//cout << "all names consumed\n";
		} else {
			if (common) {
				common = false;
				out << pad << "// " << commonPrefix << ".*\n";
				out << pad << "if (";
				if (!commonPrefix.empty())
					out << "size >= " << commonPrefix.size();
				else
					out << "true";
				for (int i = basePrefix.size(); i < commonPrefix.size(); i++) {
					out << " && name[" << i <<"] == '" << commonPrefix[i] << "'";
				}
				out << ") {\n";
			}
			//cout << "-> generating subbranch for " << commonPrefix << " with " << newNames.size() << " names, with " << names.size() << " names remaining\n";
			if (newNames.size() > 1 || (newNames.size() == 1 && !singleMatch)) {
				generateFactoryBody(out, newNames, indent + 1, commonPrefix);
			} else {
				string name = *newNames.begin();
				out << pad << "\t// " << name << "\n";
				out << pad << "\tif (size == " << name.size() << ") ";
				out << "return NodePtr(new " << name << ");\n";
			}
		}
	} while (!names.empty());
	if (!common) {
		out << pad << "}\n";
	}
	//cout << "common prefix = " << commonPrefix << "\n";
}

void makeNodesHeader(const boost::filesystem::path& output, const Builder& builder, const Headers& headerFileNames)
{
	boost::filesystem::path path = output;
	path /= "nodes.hpp";
	ofstream h(path.c_str());
	h << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	h << "#pragma once\n#include <string>\n\n";
	for (Headers::const_iterator it = headerFileNames.begin(); it != headerFileNames.end(); it++) {
		h << "#include \"" << *it << "\"\n";
	}

	// Generate the node factory class.
	h << "\nnamespace ast {\n\n";
	h << "using std::string;\n\n";
	h << "/// Node factory.\n";
	h << "class NodeFactory\n{\npublic:\n";
	h << "\tstatic NodePtr make(const string& name)\n\t{\n";
	h << "\t\tsize_t size = name.size();\n";
	NodeNames names;
	for (Builder::Nodes::const_iterator it = builder.nodes.begin(); it != builder.nodes.end(); it++) {
		names.insert(it->first);
	}
	generateFactoryBody(h, names, 2);
	h << "\t\tthrow std::runtime_error(\"Node class name '\" + name + \"' not known to NodeFactory.\");\n";
	h << "\t}\n";
	h << "};\n";
	h << "\n} // namespace ast\n\n";
}

typedef set<string> FieldNames;
void generateResolvePathBody(std::ostream& out, FieldNames names, const FieldNames& arrayFields, int indent, string basePrefix = "")
{
	string pad(indent, '\t');

	// Extract the prefixes.
	string prefix;
	string commonPrefix = basePrefix;
	bool common = true;
	do {
		NodeNames newNames;
		NodeNames::iterator nambeg = names.begin();
		bool singleMatch = false;
		if ((*nambeg).size() == commonPrefix.size()) {
			newNames.insert(*nambeg);
			names.erase(nambeg);
			prefix = commonPrefix;
			singleMatch = true;
		} else {
			prefix = commonPrefix + (*nambeg)[commonPrefix.size()];
			for (NodeNames::iterator it = names.begin(); it != names.end();) {
				string name = *it;
				NodeNames::iterator tmpit = it;
				it++;
				if (name.size() < prefix.size() || name.substr(0, prefix.size()) != prefix)
					break;
				newNames.insert(name);
				names.erase(tmpit);
			}
		}
		if (names.empty() && common && !singleMatch) {
			commonPrefix = prefix;
			names = newNames;
		} else {
			if (common) {
				common = false;
				out << pad << "// " << commonPrefix << ".*\n";
				out << pad << "if (";
				if (!commonPrefix.empty())
					out << "size >= " << commonPrefix.size();
				else
					out << "true";
				for (int i = basePrefix.size(); i < commonPrefix.size(); i++) {
					out << " && path[" << i <<"] == '" << commonPrefix[i] << "'";
				}
				out << ") {\n";
			}
			//cout << "-> generating subbranch for " << commonPrefix << " with " << newNames.size() << " names, with " << names.size() << " names remaining\n";
			if (newNames.size() > 1 || (newNames.size() == 1 && !singleMatch)) {
				generateResolvePathBody(out, newNames, arrayFields, indent + 1, commonPrefix);
			} else {
				string name = *newNames.begin();
				bool isArray = arrayFields.count(name);
				string upper = (char)toupper(name[0]) + name.substr(1);

				out << pad << "\t// " << name << "\n";
				out << pad << "\tif (size == " << name.size() << ") {\n";
				if (isArray) {
					out << pad << "\t\tthrow std::runtime_error(\"Path '\" + path + \"' refers to an array instead of a concrete array element.\");\n";
				} else {
					out << pad << "\t\treturn get" << upper << "();\n";	
				}
				out << pad << "\t} else if (path[" << name.size() << "] == '.') {\n";
				if (isArray) {
					out << pad << "\t\tsize_t dot = path.find(\".\", " << name.size() + 1 << ");\n";
					out << pad << "\t\tstring idx_str = path.substr(" << name.size() + 1 << ", dot);\n";
					out << pad << "\t\tint idx = atoi(idx_str.c_str());\n";
					out << pad << "\t\tconst NodeVector& a = get" << upper << "();\n";
					out << pad << "\t\tif (idx < 0 || idx >= a.size()) {\n";
					out << pad << "\t\t\tthrow std::runtime_error(\"Index into array '\" + path.substr(0, " << name.size() << ") + \"' is out of bounds.\");\n";
					out << pad << "\t\t}\n";
					out << pad << "\t\tif (dot == string::npos) {\n";
					out << pad << "\t\t\treturn a[idx];\n";
					out << pad << "\t\t} else {\n";
					out << pad << "\t\t\treturn a[idx]->resolvePath(path.substr(dot + 1));\n";
					out << pad << "\t\t}\n";
				} else {
					out << pad << "\t\treturn get" << upper << "()->resolvePath(path.substr(" << name.size() + 1 << "));\n";
				}
				out << pad << "\t}\n";
			}
		}
	} while (!names.empty());
	if (!common) {
		out << pad << "}\n";
	}
	//cout << "common prefix = " << commonPrefix << "\n";
}

struct InterfaceFunction {
	string prototype;
	string name;
	string args;
	bool ret;
};

void makeInterfacesHeader(const boost::filesystem::path& output, const Builder& builder)
{
	boost::filesystem::path path = output;
	path /= "interfaces.hpp";
	ofstream h(path.c_str());
	h << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	h << "#pragma once\n#include <boost/function.hpp>\n\n";

	// Generate the interfaces.
	h << "namespace ast {\n\n";
	for (Builder::Nodes::const_iterator it = builder.interfaces.begin(); it != builder.interfaces.end(); it++) {
		const Node& intf = it->second;
		vector<InterfaceFunction> funcs;

		h << "class " << intf.intfName << "\n{\npublic:\n";
		h << "\tvirtual Node* getNode() = 0;\n";
		for (Node::Fields::const_iterator jt = intf.attributes.begin(); jt != intf.attributes.end(); jt++) {
			const Node::Field& f = *jt;
			string upper = (char)toupper(f.name[0]) + f.name.substr(1);

			InterfaceFunction getter;
			getter.name = "get" + upper;
			getter.prototype = "const " + f.cpp_type + "& " + getter.name + "(bool required = true)";
			getter.args = "required";
			getter.ret = true;
			funcs.push_back(getter);

			InterfaceFunction setter;
			setter.name = "set" + upper;
			setter.prototype = "void " + setter.name + "(const " + f.cpp_type + "& v)";
			setter.args = "v";
			setter.ret = false;
			funcs.push_back(setter);

			h << "\n";
			h << "\tvirtual " << setter.prototype << " = 0;\n";
			h << "\tvirtual " << getter.prototype << " = 0;\n";
		}
		h << "};\n";

		h << "template <typename T> class " << intf.intfName << "Impl : public " << intf.intfName << "\n{\npublic:\n";
		h << "\tNode* getNode() { return node; }\n";
		h << "\t" << intf.intfName << "Impl(T* node) : node(node) {}\n\n";
		for (int i = 0; i < funcs.size(); i++) {
			InterfaceFunction& f = funcs[i];
			h << "\t" << f.prototype << " { ";
			if (f.ret) h << "return ";
			h << "node->" << f.name << "(" << f.args << "); }\n";
		}
		h << "\nprotected:\n";
		h << "\tT* const node;\n";
		h << "};\n\n";
	}
	h << "} // namespace ast\n";
}

void makeBaseNodeHeader(const boost::filesystem::path& output, const Builder& builder)
{
	boost::filesystem::path path = output;
	path /= "BaseNode.hpp";
	ofstream h(path.c_str());
	h << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	h << "#pragma once\n#include <stdexcept>\n\n";

	// Generate the node factory class.
	h << "namespace ast {\n\n";
	for (Builder::Nodes::const_iterator it = builder.interfaces.begin(); it != builder.interfaces.end(); it++) {
		h << "class " << it->second.intfName << ";\n";
	}
	h << "\n";
	h << "class BaseNode\n{\npublic:\n";
	for (Builder::Nodes::const_iterator it = builder.interfaces.begin(); it != builder.interfaces.end(); it++) {
		const Node& intf = it->second;
		h << "\tvirtual " << intf.intfName << "* as" << intf.name << "() { return NULL; }\n";
		h << "\t" << intf.intfName << "* need" << intf.name << "() { " << intf.intfName << "* i = as" << intf.name << "(); if (i) return i; throw std::runtime_error(\"Node does not implement " << intf.name << " interface.\"); }\n";
	}
	h << "};\n\n";
	h << "} // namespace ast\n";
}

void determineImplementedInterfaces(Builder& builder)
{
	// Analyze every node in the builder separately.
	for (Builder::Nodes::iterator it = builder.nodes.begin(); it != builder.nodes.end(); it++) {
		Node& node = it->second;
		for (Builder::Nodes::iterator is = builder.interfaces.begin(); is != builder.interfaces.end(); is++) {
			Node& intf = is->second;

			// Check whether node implements interface intf.
			bool implemented = true;
			for (Node::Fields::iterator ir = intf.attributes.begin(); ir != intf.attributes.end(); ir++) {
				bool found = false;
				for (Node::Fields::iterator iq = node.attributes.begin(); iq != node.attributes.end(); iq++) {
					if ((*iq).name == (*ir).name && (*iq).cpp_type == (*ir).cpp_type) {
						found = true;
						break;
					}
				}
				if (!found) {
					implemented = false;
					break;
				}
			}

			// If the node implements this interface, add it to the node's interfaces list.
			if (implemented) {
				node.interfaces.insert(&intf);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	// Parse command line arguments.
	boost::filesystem::path output(".");
	if (argc >= 2) output = argv[1];

	// Create the output directory if required.
	if (!boost::filesystem::exists(output)) {
		cout << "Creating output directory " << output << endl;
		boost::filesystem::create_directory(output);
	}

	// Build the AST.
	Builder builder;
	buildAST(builder);

	// Determine implemented interfaces.
	determineImplementedInterfaces(builder);

	// Generate the code for the nodes.
	Headers headerFileNames;
	for (Builder::Nodes::iterator it = builder.nodes.begin(); it != builder.nodes.end(); it++) {
		const string &name = it->first;
		Node &node = it->second;
		//cout << "- Generating \033[36;1m" << name << "\033[0m" << endl;
		string headerName = name + ".hpp";

		// Generate the header file.
		boost::filesystem::path hpath = output;
		hpath /= headerName;
		ofstream h(hpath.c_str());
		h << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
		h << "#pragma once\n";
		h << "#include \"../Node.hpp\"\n";
		h << "#include \"../Coder.hpp\"\n";
		h << "#include \"interfaces.hpp\"\n";
		if (node.parent != "Node") h << "#include \"" << node.parent << ".hpp\"\n";
		h << "#include <vector>\n#include <string>\n#include <sstream>\n#include <boost/smart_ptr.hpp>\n#include <stdexcept>\n\n";
		h << "namespace ast {\n\n";
		h << "using std::vector;\nusing std::string;\nusing std::stringstream;\nusing std::endl;\nusing std::runtime_error;\n\n";
		h << "class " << name << " : public Node\n{\npublic:\n";

		// Generate the constructor.
		h << "\t" << name << "() : Node()";
		for (Node::Interfaces::iterator it = node.interfaces.begin(); it != node.interfaces.end(); it++) {
			const Node& intf = **it;
			h << ",\n\t\tinterface" << intf.name << "(this)";
		}
		h << " {}\n\n";

		// Generate auxiliary functions.
		h << "\tvirtual bool isKindOf(Kind k)\n\t{\n";
		h << "\t\tif (" << node.parent << "::isKindOf(k)) return true;\n";
		h << "\t\treturn k == k" << node.name << ";\n";
		h << "\t}\n\n";
		h << "\tvirtual bool implements(Interface i)\n\t{\n";
		h << "\t\tif (" << node.parent << "::implements(i)) return true;\n";
		for (Node::Interfaces::iterator it = node.interfaces.begin(); it != node.interfaces.end(); it++) {
			const Node& intf = **it;
			h << "\t\tif (i == k" << intf.intfName << ") return true;\n";
		}
		h << "\t\treturn false;\n";
		h << "\t}\n\n";
		h << "\tvirtual string getClassName() const { return \"" << node.name << "\"; }\n\n";

		for (Node::Fields::iterator fit = node.attributes.begin(); fit != node.attributes.end(); fit++) {
			Node::Field& f = *fit;
			string ref = "const " + f.cpp_type + "&";
			string upper = f.name;
			if (!upper.empty()) upper[0] = toupper(upper[0]);
			h << "\tvoid set" << upper << "(" << ref << " v)\n\t{\n";

			vector<string> ifcomponents;
			string allowedNodes;
			string allowedInterfaces;
			for (int i = 0; i < f.allowedNodes.size(); i++) {
				ifcomponents.push_back("!v->isKindOf(k" + f.allowedNodes[i] + ")");
				if (!allowedNodes.empty()) allowedNodes += ", ";
				allowedNodes += f.allowedNodes[i];
			}
			for (int i = 0; i < f.allowedInterfaces.size(); i++) {
				ifcomponents.push_back("!v->implements(k" + builder.interfaces[f.allowedInterfaces[i]].intfName + ")");
				if (!allowedInterfaces.empty()) allowedInterfaces += ", ";
				allowedInterfaces += f.allowedInterfaces[i];
			}
			if (!ifcomponents.empty()) {
				h << "\t\tif (v";
				for (int i = 0; i < ifcomponents.size(); i++) {
					h << " && " << ifcomponents[i];
				}
				h << ") {\n";
				h << "\t\t\tthrow runtime_error(\"'" << f.name << "' needs to be of kind {" << allowedNodes << "} or implement interface {" << allowedInterfaces << "}, got \" + v->getClassName() + \" instead.\");\n";
				h << "\t\t}\n";
			}

			if (f.ref) {
				h << "\t\tif (!v && " << f.name << ") {\n";
				h << "\t\t\tmodify();\n";
				h << "\t\t\t" << f.name << ".reset();\n";
				h << "\t\t}\n";
				h << "\t\tif (!" << f.name << " || v->getId() != " << f.name << ".id) {\n";
			} else {
				h << "\t\tif (v != " << f.name << ") {\n";
			}
			h << "\t\t\tmodify();\n";
			if (f.ref) {
				h << "\t\t\t" << f.name << ".set(v);\n";
			} else {
				h << "\t\t\t" << f.name << " = v;\n";
			}
			h << "\t\t}\n";
			h << "\t}\n";

			if (f.ref) {
				h << "\tvoid set" << upper << "(const NodeId& v)\n\t{\n";
				h << "\t\tif (v != " << f.name << ".id) {\n";
				h << "\t\t\tmodify();\n";
				h << "\t\t\t" << f.name << ".set(v);\n";
				h << "\t\t}\n";
				h << "\t}\n";
			}

			h << "\t" << ref << " get" << upper << "(bool required = true)\n\t{\n";
			h << "\t\tconst " << f.cpp_type << "& v = ";
			if (f.ref) {
				h << f.name << ".get(repository);\n";
			} else {
				h << f.name << ";\n";
			}
			if (f.isNode) {
				h << "\t\tif (required && !v) {\n";
				h << "\t\t\tthrow runtime_error(\"Node \" + getId().str() + \" is required to have " << f.name << " set to a non-null value.\");\n";
				h << "\t\t}\n";
			} else if (f.isString) {
				h << "\t\tif (required && v.empty()) {\n";
				h << "\t\t\tthrow runtime_error(\"Node \" + getId().str() + \" is required to have a non-empty string " << f.name << " set.\");\n";
				h << "\t\t}\n";
			}
			h << "\t\treturn v;\n";
			h << "\t}\n\n";
		}

		// Generate the describe() function.
		h << "\tvirtual string describe(int depth = -1)\n\t{\n";
		h << "\t\tif (depth == 0) return \"" << name << "{…}\";\n";
		h << "\t\tstringstream str, b;\n";
		h << "\t\tstr << \"" << name << "{\";\n";
		for (Node::Fields::iterator fit = node.attributes.begin(); fit != node.attributes.end(); fit++) {
			Node::Field& f = *fit;
			if (f.isString) {
				h << "\t\tif (!this->"<<f.name<<".empty()) b << endl << \"  \\033[1m"<<f.name<<"\\033[0m = '\\033[33m\" << this->"<<f.name<<" << \"\\033[0m'\";\n";
			} else if (f.isBool) {
				h << "\t\tb << endl << \"  \\033[1m"<<f.name<<"\\033[0m = \\033[34m\" << (this->"<<f.name<<" ? \"true\" : \"false\") << \"\\033[0m\";\n";
			} else if (f.isNode) {
				h << "\t\tif (this->" << f.name << ")";
				h << " b << endl << \"  \\033[1m"<<f.name<<"\\033[0m = \"";
				if (f.ref) {
					h << " << \"\\033[36m\" << this->" << f.name << ".id << \"\\033[0m\";\n";
				} else {
					h << " << indent(this->"<<f.name<<"->describe(depth-1));\n";
				}
			} else if (f.isArray) {
				h << "\t\tif (!this->"<<f.name<<".empty()) b << endl << \"  \\033[1m"<<f.name<<"\\033[0m = \" << indent(describeVector(this->"<<f.name<<", depth-1)) << \"\";\n";
			}
		}
		h << "\t\tstring bs = b.str();\n";
		h << "\t\tif (!bs.empty()) str << bs << endl;\n";
		h << "\t\tstr << \"}\";\n";
		h << "\t\treturn str.str();\n";
		h << "\t}\n\n";

		// Generate the encode() function.
		h << "\tvirtual void encode(Encoder& e)\n\t{\n";
		for (Node::Fields::iterator f = node.attributes.begin(); f != node.attributes.end(); f++) {
			h << "\t\te.encode(this->" << (*f).name << ");\n";
		}
		h << "\t}\n\n";

		// Generate the decode() function.
		h << "\tvirtual void decode(Decoder& d)\n\t{\n";
		for (Node::Fields::iterator f = node.attributes.begin(); f != node.attributes.end(); f++) {
			h << "\t\td.decode(this->" << (*f).name << ");\n";
		}
		h << "\t}\n\n";

		// Generate the updateHierarchy() function.
		h << "\tvirtual void updateHierarchy(const NodeId& id, Repository* repository = NULL, Node* parent = NULL)\n\t{\n";
		h << "\t\t" << node.parent << "::updateHierarchy(id, repository, parent);\n";
		for (Node::Fields::iterator fit = node.attributes.begin(); fit != node.attributes.end(); fit++) {
			Node::Field& f = *fit;
			if (f.isNode && !f.ref) {
				h << "\t\tif (this->"<<f.name<<") this->"<<f.name<<"->updateHierarchy(id + \""<<f.name<<"\", repository, this);\n";
			} else if (f.isArray) {
				h << "\t\tfor (int i = 0; i < this->"<<f.name<<".size(); i++) {\n";
				h << "\t\t\tchar buf[32]; snprintf(buf, 31, \"%i\", i);\n";
				h << "\t\t\tthis->"<<f.name<<"[i]->updateHierarchy((id + \""<<f.name<<"\") + buf, repository, this);\n";
				h << "\t\t}\n";
			}
		}
		h << "\t}\n\n";

		// Generate the resolvePath() function.
		h << "\tvirtual const NodePtr& resolvePath(const string& path)\n\t{\n";
		FieldNames fields, arrayFields;
		for (Node::Fields::iterator fit = node.attributes.begin(); fit != node.attributes.end(); fit++) {
			Node::Field& f = *fit;
			if (f.isNode) {
				fields.insert(f.name);
			} else if (f.isArray) {
				fields.insert(f.name);
				arrayFields.insert(f.name);
			}
		}
		if (!fields.empty()) {
			h << "\t\tsize_t size = path.size();\n";
			generateResolvePathBody(h, fields, arrayFields, 2);
		}
		h << "\t\tthrow std::runtime_error(\"Node path '\" + path + \"' does not point to a node or array of nodes.\");\n";
		h << "\t}\n\n";

		// Generate the getChildren() function.
		if (!node.children.empty()) {
			h << "\tvirtual NodeVector getChildren()\n\t{\n";
			h << "\t\tNodeVector v;\n";
			for (Node::FieldIndices::iterator c = node.children.begin(); c != node.children.end(); c++) {
				Node::Field& f = node.attributes[*c];
				if (f.isNode) {
					string upper = (char)toupper(f.name[0]) + f.name.substr(1);
					h << "\t\tif (const NodePtr& n = this->get" << upper << "(false)) v.push_back(n);\n";
				} else if (f.isArray) {
					h << "\t\tv.insert(v.end(), this->" << f.name << ".begin(), this->" << f.name << ".end());\n";
				}
			}
			h << "\t\treturn v;\n";
			h << "\t}\n\n";
		}

		// Generate the interface accessors.
		if (!node.interfaces.empty()) {
			h << "\t// Interfaces\n";
			for (Node::Interfaces::iterator it = node.interfaces.begin(); it != node.interfaces.end(); it++) {
				const Node& intf = **it;
				h << "\tvirtual " << intf.intfName << "* as" << intf.name << "() { return &this->interface" << intf.name << "; }\n";
			}
			h << "\n";
		}

		h << "protected:\n";
		for (Node::Fields::iterator f = node.attributes.begin(); f != node.attributes.end(); f++) {
			if ((*f).ref) {
				h << "\tNodeRef " << (*f).name << ";\n";
			} else {
				h << "\t" << (*f).cpp_type << " " << (*f).name << ";\n";
			}
		}
		if (!node.interfaces.empty()) {
			h << "\n\t// Interfaces\n";
			for (Node::Interfaces::iterator it = node.interfaces.begin(); it != node.interfaces.end(); it++) {
				const Node& intf = **it;
				h << "\t" << intf.intfName << "Impl<" << node.name << "> interface" << intf.name << ";\n";
			}
		}

		h << "};\n\n";
		h << "} // namespace ast";
		headerFileNames.push_back(headerName);
	}

	// Generate the header file containing general typedefs.
	makeTypesHeader(output, builder);
	makeNodesHeader(output, builder, headerFileNames);
	makeInterfacesHeader(output, builder);

	// Generate the base header file for ast::Node which implements default interface accessors.
	makeBaseNodeHeader(output, builder);

	// Generate the header file aggregating all AST things.
	boost::filesystem::path ahpath = output;
	ahpath /= "ast.hpp";
	ofstream ah(ahpath.c_str());
	ah << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	ah << "#pragma once\n\n";
	ah << "#include \"types.hpp\"\n";
	ah << "#include \"nodes.hpp\"\n";
	ah << "#include \"interfaces.hpp\"\n";

	return 0;
}