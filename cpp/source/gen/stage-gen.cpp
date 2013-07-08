/* Copyright © 2013 Fabian Schuiki */

/**
 * @file This tool generates the C++ header and source files for the abstract
 * syntax tree.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

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
	stages.push_back("BindIdentifiers");
	stages.push_back("BindNamedTypes");
	stages.push_back("CalcPossibleTypes");

	// Generate the stages header file.
	boost::filesystem::path hpath = output;
	hpath /= "stages.hpp";
	ofstream h(hpath.c_str());
	h << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	h << "#pragma once\n";
	h << "#include \"Stage.hpp\"\n\n";
	h << "namespace stage {\n\n";
	for (Stages::iterator it = stages.begin(); it != stages.end(); it++) {
		h << "class " << *it << " : public Stage\n";
		h << "{\npublic:\n";
		h << "\tstring getName() const { return \"" << *it << "\"; }\n";
		h << "\tvirtual void process(const NodePtr& node);\n";
		h << "\t" << *it << "(Repository& r) : Stage(r) {}\n";

		// Custom header fields.
		boost::filesystem::path cpath = output;
		cpath /= *it + ".in.hpp";
		ifstream fin(cpath.c_str());
		if (fin.good()) {
			h << "\n";
			h << string((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
			h << "\n";
		}

		h << "};\n\n";
	}
	h << "} // namespace stage\n";

	// Generate the stage manager header file.
	boost::filesystem::path mpath = output;
	mpath /= "StageManager.hpp";
	ofstream mh(mpath.c_str());
	mh << "/* Automatically generated by ast-gen. DO NOT MODIFY. */\n";
	mh << "#pragma once\n";
	mh << "#include \"stages.hpp\"\n";
	mh << "#include <string>\n";
	mh << "#include <map>\n";
	mh << "#include <vector>\n";
	mh << "\n";
	mh << "namespace stage {\n\n";
	mh << "using std::string;\nusing std::map;\nusing std::vector;\n\n";
	mh << "class StageManager\n{\npublic:\n";
	mh << "\tRepository& repository;\n\n";

	// Generate the constructor.
	mh << "\tStageManager(Repository& r) : repository(r)";
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

	// Stages vector.
	mh << "\ttypedef vector<Stage*> Stages;\n";
	mh << "\ttypedef map<string, int> StageIndices;\n";
	mh << "\tStages stages;\n";
	mh << "\tStageIndices stageIndices;\n\n";

	mh << "protected:\n";
	for (Stages::iterator it = stages.begin(); it != stages.end(); it++) {
		mh << "\t" << *it << " stage" << *it << ";\n";
	}
	mh << "};\n\n";
	mh << "} // namespace stage\n";

	return 0;
}