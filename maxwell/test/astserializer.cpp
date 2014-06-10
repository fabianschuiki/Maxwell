/* Copyright (c) 2013 Fabian Schuiki */

/**
 * @file This program serves as a testing facility for the ast::Serializer.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "maxwell/ast/nodes/ast.hpp"
#include "maxwell/ast/Serializer.hpp"
#include <boost/smart_ptr.hpp>

using std::cout;
using std::cerr;
using boost::shared_ptr;
using namespace ast;
using std::vector;
using std::string;
using std::stringstream;

int main(int argc, char *argv[])
{
	try {
		Serializer ser;

		// Create a function definition.
		shared_ptr<FuncDef> fdef(new FuncDef);
		fdef->setName("main");
		shared_ptr<BlockExpr> fbody(new BlockExpr);
		fdef->setBody(fbody);
		shared_ptr<FuncArg> farg(new FuncArg);
		farg->setName("x");
		//farg->setType("Integer");
		vector<shared_ptr<Node> > args;
		args.push_back(farg);
		fdef->setIn(args);
		fdef->updateHierarchy(NodeId(1,1));

		// Dump it to the console.
		cout << "Arg x has ID: " << farg->getId() << "\n";
		cout << "Will serialize: " << fdef->describe() << "\n";

		// Serialize.
		stringstream serialized;
		ser.encode(serialized, fdef);
		cout << "\n" << serialized.str() << "\n\n";

		// Unserialize.
		shared_ptr<Node> unserialized = ser.decode(serialized.str());
		cout << "Unserialized: " << unserialized->describe() << "\n";

	} catch (std::exception &e) {
		cerr << "*** \033[31;1mexception:\033[0m " << e.what() << "\n";
		return 1;
	}
	return 0;
}
