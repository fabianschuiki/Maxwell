/* Copyright © 2013 Fabian Schuiki */

/**
 * @file This tool generates the C++ header and source files for the abstract
 * syntax tree.
 */

#include "ast-def.hpp"

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
	h << "\n} Kind;\n";
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
	int guard = 0;
	do {
		if (guard++ > 15) break;
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
				out << pad << "if (size >= " << commonPrefix.size();
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

	// Build the stage list.
	typedef vector<string> Stages;
	Stages stages;
	stages.push_back("BuildGraph");

	// Generate the stages header file.
	boost::filesystem::path hpath = output;
	hpath /= "stages.hpp";
	ofstream h(hpath.c_str());
	h << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	h << "#pragma once\n";
	h << "#include \"Stage.hpp\"\n\n";
	h << "namespace stage {\n\n";
	h << "using std::runtime_error;\n\n";
	for (Stages::iterator it = stages.begin(); it != stages.end(); it++) {
		h << "class " << *it << "Base : public Stage\n";
		h << "{\npublic:\n";
		h << "\tstring getName() const { return \"" << *it << "\"; }\n";
		h << "\t" << *it << "Base(const shared_ptr<Repository>& r) : Stage(r) {}\n";
		h << "};\n\n";
	}
	h << "} // namespace stage\n";

	// Generate the stage manager header file.
	boost::filesystem::path mpath = output;
	mpath /= "StageManager.hpp";
	ofstream mh(mpath.c_str());
	mh << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	mh << "#pragma once\n";
	mh << "#include <string>\n";
	mh << "#include <map>\n";
	mh << "#include <vector>\n";
	for (Stages::iterator it = stages.begin(); it != stages.end(); it++) {
		mh << "#include \"" << *it << ".hpp\"\n";
	}
	mh << "\n";
	mh << "namespace stage {\n\n";
	mh << "using std::string;\nusing std::map;\nusing std::vector;\n\n";
	mh << "class StageManager\n{\npublic:\n";

	// Generate the constructor.
	mh << "\tStageManager(const shared_ptr<Repository>& r) : repository(r)";
	for (Stages::iterator it = stages.begin(); it != stages.end(); it++) {
		mh << ",\n\t\tstage" << *it << "(r)";
	}
	mh << "\n";
	mh << "\t{\n";
	for (Stages::iterator it = stages.begin(); it != stages.end(); it++) {
		mh << "\t\tstageIndices[\"" << *it << "\"] = stages.size();\n";
		mh << "\t\tstages.push_back(&stage" << *it << ");\n";
	}
	mh << "\t}\n\n";

	// Generate the stage accessors.
	mh << "\tStage& operator[](int index)\n\t{\n";
	mh << "\t\tif (index < 0 || index >= stage.size()) {\n";
	mh << "\t\t\tthrow std::runtime_error(\"Stage index out of bounds.\");\n";
	mh << "\t\t}\n";
	mh << "\t\treturn stages[index];\n";
	mh << "\t}\n\n";

	mh << "\tStage& operator[](string name)\n\t{\n";
	mh << "\t\tmap<string, int>::iterator it = stageIndices.find(name);\n";
	mh << "\t\tif (it == stageIndices.end()) {\n";
	mh << "\t\t\tthrow std::runtime_error(\"Stage named '\" + name + \"' does not exist.\");\n";
	mh << "\t\t}\n";
	mh << "\t\treturn stages[it->second];\n";
	mh << "\t}\n\n";

	mh << "protected:\n";
	mh << "\tvector<Stage*> stages;\n";
	mh << "\tmap<string, int> stageIndices;\n";
	for (Stages::iterator it = stages.begin(); it != stages.end(); it++) {
		mh << "\t" << *it << " stage" << *it << ";\n";
	}
	mh << "};\n\n";
	mh << "} // namespace stage\n";

	return 0;
}