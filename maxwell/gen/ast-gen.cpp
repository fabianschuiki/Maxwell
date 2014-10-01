/* Copyright (c) 2013-2014 Fabian Schuiki */

/// \file
/// This tool generates the C++ header and source files for the abstract syntax
/// tree.

#include "maxwell/gen/ast-gen.hpp"
#include <boost/filesystem/fstream.hpp>

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
	f.isInt = false;
	if (type == "string") {
		f.isString = true;
		f.cpp_type = "std::string";
	} else if (type == "bool") {
		f.isBool = true;
		f.cpp_type = "bool";
	} else if (type == "int") {
		f.isInt = true;
		f.cpp_type = "int";
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
				for (unsigned i = basePrefix.size(); i < commonPrefix.size(); i++) {
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
	boost::filesystem::path hpath = output, spath = output;
	hpath /= "nodes.hpp";
	spath /= "nodes.cpp";
	boost::filesystem::ofstream h(hpath.c_str());
	boost::filesystem::ofstream s(spath.c_str());

	h << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	h << "#pragma once\n";
	for (Headers::const_iterator it = headerFileNames.begin(); it != headerFileNames.end(); it++) {
		h << "#include \"maxwell/ast/nodes/" << *it << "\"\n";
	}
	h << "#include <string>\n";

	s << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	s << "#include \"maxwell/ast/nodes/nodes.hpp\"\n\n";

	// Generate the node factory class.
	h << "\nnamespace ast {\n\n";
	// h << "class NodeFactory\n{\npublic:\n";
	// h << "\tstatic NodePtr make(const std::string& name);\n";
	// h << "};\n";
	h << "NodePtr makeNode(const std::string& name);\n\n";
	h << "} // namespace ast\n\n";

	// s << "NodePtr NodeFactory::make(const std::string& name) {\n";
	s << "ast::NodePtr ast::makeNode(const std::string& name) {\n";
	s << "\tsize_t size = name.size();\n";
	NodeNames names;
	for (Builder::Nodes::const_iterator it = builder.nodes.begin(); it != builder.nodes.end(); it++) {
		names.insert(it->first);
	}
	generateFactoryBody(s, names, 1);
	s << "\tthrow std::runtime_error(\"Node class name '\" + name + \"' not known to NodeFactory.\");\n";
	s << "}\n";
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
				for (unsigned i = basePrefix.size(); i < commonPrefix.size(); i++) {
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
					out << pad << "\t\tif (idx < 0 || idx >= (int)a.size()) {\n";
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
	h << "#pragma once\n";
	h << "#include \"maxwell/ast/Node.hpp\"\n";
	h << "#include <boost/function.hpp>\n";
	h << '\n';

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
		for (unsigned i = 0; i < funcs.size(); i++) {
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
	h << "#pragma once\n";
	h << "#include \"maxwell/ast/NodeId.hpp\"\n";
	h << "#include <stdexcept>\n";
	h << '\n';

	// Generate the node factory class.
	h << "namespace ast {\n\n";
	for (Builder::Nodes::const_iterator it = builder.interfaces.begin(); it != builder.interfaces.end(); it++) {
		h << "class " << it->second.intfName << ";\n";
	}
	h << "\n";
	h << "class BaseNode\n{\npublic:\n";
	h << "\tvirtual string getClassName() const = 0;\n";
	h << "\tvirtual const NodeId& getId() const = 0;\n";
	for (Builder::Nodes::const_iterator it = builder.interfaces.begin(); it != builder.interfaces.end(); it++) {
		const Node& intf = it->second;
		h << "\tvirtual " << intf.intfName << "* as" << intf.name << "() { return NULL; }\n";
		h << "\t" << intf.intfName << "* need" << intf.name << "() { " << intf.intfName << "* i = as" << intf.name << "(); if (i) return i; throw std::runtime_error(\"Node \" + getId().str() + \" (a \" + getClassName() + \") does not implement " << intf.name << " interface.\"); }\n";
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

void determineChildNodes(Builder& builder)
{
	// Analyze every node in the builder separately.
	for (Builder::Nodes::iterator it = builder.nodes.begin(); it != builder.nodes.end(); it++) {
		Node& node = it->second;
		for (Node::Fields::iterator is = node.attributes.begin(); is != node.attributes.end(); is++) {
			if ((*is).child) {
				node.children.push_back(&*is);
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
		cout << "Creating output directory " << output << '\n';
		boost::filesystem::create_directory(output);
	}

	// Build the AST.
	Builder builder;
	buildAST(builder);

	// Determine implemented interfaces and child nodes.
	determineImplementedInterfaces(builder);
	determineChildNodes(builder);

	// Generate the code for the nodes.
	Headers headerFileNames;
	Headers sourceFileNames;
	for (Builder::Nodes::iterator it = builder.nodes.begin(); it != builder.nodes.end(); it++) {
		const std::string &name = it->first;
		Node &node = it->second;
		//cout << "- Generating \033[36;1m" << name << "\033[0m" << '\n';
		std::string headerName = name + ".hpp";
		std::string sourceName = name + ".cpp";

		// Generate the header and source file.
		boost::filesystem::path hpath = output, spath = output;
		hpath /= headerName;
		spath /= sourceName;
		std::ofstream h(hpath.c_str());
		std::ofstream s(spath.c_str());

		h << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
		h << "#pragma once\n";
		h << "#include \"maxwell/ast/Node.hpp\"\n";
		h << "#include \"maxwell/ast/nodes/interfaces.hpp\"\n";
		h << "#include \"maxwell/ast/nodes/types.hpp\"\n";
		if (node.parent != "Node") h << "#include \"maxwell/ast/nodes/" << node.parent << ".hpp\"\n";
		h << '\n';

		s << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
		s << "#include \"maxwell/ast/nodes/" << headerName << "\"\n";
		s << "#include \"maxwell/ast/Coder.hpp\"\n";
		s << "#include <cstdio>\n";
		s << "#include <sstream>\n";
		s << "#include <stdexcept>\n";
		s << "using ast::" << name << ";\n";
		s << "using ast::NodePtr;\n";
		s << "using ast::NodeVector;\n\n";

		h << "namespace ast {\n\n";
		h << "class Encoder;\n";
		h << "class Decoder;\n\n";
		h << "class " << name << " : public Node\n{\npublic:\n";

		// Generate the constructor.
		h << "\t// constructor\n";
		h << "\t" << name << "();\n\n";
		s << name << "::" << name << "() : Node()";
		for (Node::Interfaces::iterator it = node.interfaces.begin(); it != node.interfaces.end(); it++) {
			const Node& intf = **it;
			s << ",\n\tinterface" << intf.name << "(this)";
		}
		s << " {}\n\n";

		// Generate auxiliary functions.
		h << "\t// auxiliary functions\n";
		h << "\tvirtual bool isKindOf(Kind k);\n";
		h << "\tvirtual bool implements(Interface i);\n";
		h << "\tvirtual std::string getClassName() const { return \"" << node.name << "\"; }\n";
		h << "\tvirtual NodePtr copy();\n";
		h << "\tvirtual bool equalTo(const NodePtr& o);\n";
		h << "\tvirtual std::string describe(int depth = -1);\n";
		h << '\n';

		// isKindOf
		s << "bool " << name << "::isKindOf(Kind k) {\n";
		s << "\tif (" << node.parent << "::isKindOf(k)) return true;\n";
		s << "\treturn k == k" << node.name << ";\n";
		s << "}\n\n";

		// implements
		s << "bool " << name << "::implements(Interface i) {\n";
		s << "\tif (" << node.parent << "::implements(i)) return true;\n";
		for (Node::Interfaces::iterator it = node.interfaces.begin(); it != node.interfaces.end(); it++) {
			const Node& intf = **it;
			s << "\tif (i == k" << intf.intfName << ") return true;\n";
		}
		s << "\treturn false;\n";
		s << "}\n\n";

		// copy
		s << "NodePtr " << name << "::copy() {\n";
		s << "\tPtr c (new " << name << ");\n";
		for (Node::Fields::iterator f = node.attributes.begin(); f != node.attributes.end(); f++) {
			s << "\tNode::copy(this->" << (*f).name << ", c->" << (*f).name << ");\n";
		}
		s << "\treturn c;\n";
		s << "}\n\n";

		// equalTo
		s << "bool " << name << "::equalTo(const NodePtr& o) {\n";
		s << "\tconst shared_ptr<" << node.name << ">& other = boost::dynamic_pointer_cast<" << node.name << ">(o);\n";
		s << "\tif (!other) return false;\n";
		for (Node::Fields::iterator fit = node.attributes.begin(); fit != node.attributes.end(); fit++) {
			Node::Field& f = *fit;
			s << "\tif (!equal(this->" << f.name << ", other->" << f.name << ")) return false;\n";
		}
		s << "\treturn true;\n";
		s << "}\n\n";

		// describe
		s << "std::string " << name << "::describe(int depth) {\n";
		s << "\tstd::stringstream str, b;\n";
		if (node.descriptionBody.empty()) {
			s << "\tif (depth == 0) return \"" << name << "{…}\";\n";
			s << "\tstr << \"" << name << "{\";\n";
			for (Node::Fields::iterator fit = node.attributes.begin(); fit != node.attributes.end(); fit++) {
				Node::Field& f = *fit;

				// Don't print empty strings and arrays.
				s << "\t";
				if (f.isString || f.isArray) s << "if (!this->" <<f.name<< ".empty()) ";
				if (f.isNode) s << "if (this->" << f.name << ") ";

				// Print the field name.
				s << "b << \"\\n  \\033[1m" << f.name << "\\033[0m = ";

				// Print the actual data.
				if (f.isString) s << "\\033[33m\\\"\" << this->" << f.name << " << \"\\\"\\033[0m\";";
				if (f.isBool) s << "\\033[34m\" << (this->" << f.name << " ? \"true\" : \"false\") << \"\\033[0m\";";
				if (f.isInt) s << "\\033[35m\" << this->" << f.name << " << \"\\033[0m\";";
				if (f.isNode) {
					if (f.ref) {
						s << "\\033[36m\" << this->" << f.name << ".id << \"\\033[0m\";";
					} else {
						s << "\" << indent(this->" << f.name << "->describe(depth-1));";
					}
				}
				if (f.isArray) s << "\" << indent(describeVector(this->" << f.name << ", depth-1));";
				s << "\n";
			}
			s << "\tstring bs = b.str();\n";
			s << "\tif (!bs.empty()) str << bs << '\\n';\n";
			s << "\tstr << \"}\";\n";
		} else {
			string body(node.descriptionBody);
			boost::algorithm::replace_all(body, "\n", "\n\t\t");
			s << "\t" << body << "\n";
		}
		s << "\treturn str.str();\n";
		s << "}\n\n";
		s << '\n';

		// Generate the accessor functions.
		h << "\t// accessor functions\n";
		for (Node::Fields::iterator fit = node.attributes.begin(); fit != node.attributes.end(); fit++) {
			Node::Field& f = *fit;
			string ref = "const " + f.cpp_type + "&";
			string upper = f.name;
			if (!upper.empty()) upper[0] = toupper(upper[0]);
			h << "\tvoid set" << upper << "(" << ref << " v);\n";
			s << "void " << name << "::set" << upper << "(" << ref << " v) {\n";

			vector<string> ifcomponents;
			string allowedNodes;
			string allowedInterfaces;
			for (unsigned i = 0; i < f.allowedNodes.size(); i++) {
				ifcomponents.push_back("!v->isKindOf(k" + f.allowedNodes[i] + ")");
				if (!allowedNodes.empty()) allowedNodes += ", ";
				allowedNodes += f.allowedNodes[i];
			}
			for (unsigned i = 0; i < f.allowedInterfaces.size(); i++) {
				ifcomponents.push_back("!v->implements(k" + builder.interfaces[f.allowedInterfaces[i]].intfName + ")");
				if (!allowedInterfaces.empty()) allowedInterfaces += ", ";
				allowedInterfaces += f.allowedInterfaces[i];
			}
			if (!ifcomponents.empty()) {
				s << "\tif (v";
				for (unsigned i = 0; i < ifcomponents.size(); i++) {
					s << " && " << ifcomponents[i];
				}
				s << ") {\n";
				s << "\t\tthrow std::runtime_error(\"'" << f.name << "' of \" + id.str() + \" needs to be of kind {" << allowedNodes << "} or implement interface {" << allowedInterfaces << "}, got \" + v->getClassName() + \" (\" + v->getId().str() + \") instead.\");\n";
				s << "\t}\n";
			}

			if (f.ref) {
				s << "\tif (!v && " << f.name << ") {\n";
				s << "\t\tmodify(\"" << f.name << "\");\n";
				s << "\t\t" << f.name << ".reset();\n";
				s << "\t}\n";
				s << "\tif (!" << f.name << " || v->getId() != " << f.name << ".id) {\n";
			} else {
				s << "\tif (!equal(v, " << f.name << ")) {\n";
			}
			s << "\t\tmodify(\"" << f.name << "\");\n";
			if (f.ref) {
				s << "\t\t" << f.name << ".set(v);\n";
			} else {
				s << "\t\t" << f.name << " = v;\n";
			}
			s << "\t}\n";
			s << "}\n\n";

			// special setter for references
			if (f.ref) {
				h << "\tvoid set" << upper << "(const NodeId& v);\n";
				s << "void " << name << "::set" << upper << "(const NodeId& v) {\n";
				s << "\tif (v != " << f.name << ".id) {\n";
				s << "\t\tmodify(\"" << f.name << "\");\n";
				s << "\t\t" << f.name << ".set(v);\n";
				s << "\t}\n";
				s << "}\n\n";
			}

			h << "\t" << ref << " get" << upper << "(bool required = true);\n\n";
			s << ref << " " << name << "::get" << upper << "(bool required) {\n";
			s << "\tconst " << f.cpp_type << "& v = ";
			if (f.ref) {
				s << f.name << ".get(repository);\n";
			} else {
				s << f.name << ";\n";
			}
			if (f.isNode) {
				s << "\tif (required && !v) {\n";
				s << "\t\tthrow std::runtime_error(\"Node \" + getId().str() + \" is required to have " << f.name << " set to a non-null value.\");\n";
				s << "\t}\n";
			} else if (f.isString) {
				s << "\tif (required && v.empty()) {\n";
				s << "\t\tthrow std::runtime_error(\"Node \" + getId().str() + \" is required to have a non-empty string " << f.name << " set.\");\n";
				s << "\t}\n";
			}
			s << "\treturn v;\n";
			s << "}\n\n\n";
		}

		// Generate the encode() and decode() function.
		h << "\t// encoding and decoding\n";
		h << "\tvirtual void encode(Encoder& e);\n";
		h << "\tvirtual void decode(Decoder& d);\n";
		h << '\n';

		s << "void " << name << "::encode(Encoder& e) {\n";
		for (Node::Fields::iterator f = node.attributes.begin(); f != node.attributes.end(); f++) {
			s << "\te.encode(this->" << (*f).name << ");\n";
		}
		s << "}\n\n";

		s << "void " << name << "::decode(Decoder& d) {\n";
		for (Node::Fields::iterator f = node.attributes.begin(); f != node.attributes.end(); f++) {
			s << "\td.decode(this->" << (*f).name << ");\n";
		}
		s << "}\n\n";
		s << '\n';

		// Generate the hierarchy functions.
		h << "\t// hierarchy functions\n";
		h << "\tvirtual void updateHierarchyOfChildren();\n";
		h << "\tvirtual const NodePtr& resolvePath(const std::string& path);\n";

		// updateHierarchy
		s << "void " << name << "::updateHierarchyOfChildren() {\n";
		for (Node::Fields::iterator fit = node.attributes.begin(); fit != node.attributes.end(); fit++) {
			Node::Field& f = *fit;
			if (f.isNode && !f.ref) {
				s << "\tif (this->"<<f.name<<") this->"<<f.name<<"->updateHierarchy(id + \""<<f.name<<"\", repository, this);\n";
			} else if (f.isArray) {
				s << "\tfor (unsigned i = 0; i < this->"<<f.name<<".size(); i++) {\n";
				s << "\t\tchar buf[32]; snprintf(buf, 31, \"%i\", i);\n";
				s << "\t\tthis->"<<f.name<<"[i]->updateHierarchy((id + \""<<f.name<<"\") + buf, repository, this);\n";
				s << "\t}\n";
			}
		}
		s << "}\n\n";

		// resolvePath
		s << "const NodePtr& " << name << "::resolvePath(const std::string& path) {\n";
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
			s << "\tsize_t size = path.size();\n";
			generateResolvePathBody(s, fields, arrayFields, 1);
		}
		s << "\tthrow std::runtime_error(\"Node path '\" + path + \"' does not point to a node or array of nodes.\");\n";
		s << "}\n\n";

		// getChildren
		if (!node.children.empty()) {
			h << "\tvirtual NodeVector getChildren();\n";
			s << "NodeVector " << name << "::getChildren() {\n";
			s << "\tNodeVector v;\n";
			for (Node::Children::iterator c = node.children.begin(); c != node.children.end(); c++) {
				Node::Field& f = **c;
				if (f.isNode) {
					string upper = (char)toupper(f.name[0]) + f.name.substr(1);
					s << "\tif (const NodePtr& n = this->get" << upper << "(false)) v.push_back(n);\n";
				} else if (f.isArray) {
					s << "\tv.insert(v.end(), this->" << f.name << ".begin(), this->" << f.name << ".end());\n";
				}
			}
			s << "\treturn v;\n";
			s << "}\n\n";
		}
		h << '\n';

		// Generate the interface accessors.
		if (!node.interfaces.empty()) {
			h << "\t// interfaces\n";
			for (Node::Interfaces::iterator it = node.interfaces.begin(); it != node.interfaces.end(); it++) {
				const Node& intf = **it;
				h << "\tvirtual " << intf.intfName << "* as" << intf.name << "() { return &this->interface" << intf.name << "; }\n";
			}
			h << "\n";
		}

		// Generate boost::shared_ptr convenience typedef.
		h << "\t// shared_ptr convenience\n";
		h << "\ttypedef boost::shared_ptr<" << node.name << "> Ptr;\n";
		h << "\ttemplate<typename T> static Ptr from(const T& n) { return boost::dynamic_pointer_cast<" << node.name << ">(n); }\n";
		h << "\ttemplate<typename T> static Ptr needFrom(const T& n) {\n";
		h << "\t\tPtr r = boost::dynamic_pointer_cast<" << node.name << ">(n);\n";
		h << "\t\tif (!r)\n";
		h << "\t\t\tthrow std::runtime_error(\"Node \" + n->getId().str() + \" (a \" + n->getClassName() + \") cannot be dynamically cast to " << node.name << ".\");\n";
		h << "\t\treturn r;\n";
		h << "\t}\n";
		h << '\n';

		h << "protected:\n";
		for (Node::Fields::iterator f = node.attributes.begin(); f != node.attributes.end(); f++) {
			if ((*f).ref) {
				h << "\tNodeRef " << (*f).name << ";\n";
			} else {
				h << "\t" << (*f).cpp_type << " " << (*f).name << ";\n";
			}
		}
		if (!node.interfaces.empty()) {
			h << "\n\t// interfaces\n";
			for (Node::Interfaces::iterator it = node.interfaces.begin(); it != node.interfaces.end(); it++) {
				const Node& intf = **it;
				h << "\t" << intf.intfName << "Impl<" << node.name << "> interface" << intf.name << ";\n";
			}
		}

		h << "};\n\n";
		h << "} // namespace ast\n";
		headerFileNames.push_back(headerName);
		sourceFileNames.push_back(sourceName);
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
	ah << "#include \"maxwell/ast/nodes/types.hpp\"\n";
	ah << "#include \"maxwell/ast/nodes/nodes.hpp\"\n";
	ah << "#include \"maxwell/ast/nodes/interfaces.hpp\"\n";

	return 0;
}
