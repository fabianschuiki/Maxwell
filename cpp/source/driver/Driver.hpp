/* Copyright © 2013 Fabian Schuiki */
#include <string>
#include <iostream>
#include <boost/smart_ptr.hpp>
#include <ast/nodes/ast.hpp>

namespace driver {

using boost::shared_ptr;
using ast::NodePtr;
using ast::NodeVector;

class Driver
{
public:
	Driver();

	/// Stream name (file or input stream) used for error messages.
	std::string streamname;

	/**
	 * Routes the given input stream through the scanner and parser.
	 */
	bool parseStream(std::istream& in, const std::string& name = "stream");

	/**
	 * Opens the file at path %filename and routes it through the scanner and
	 * parser.
	 */
	bool parseFile(const std::string& filename);

	/**
	 * Error handling with associated location. Called by the parser and lexer
	 * if they encounter an error.
	 */
	void error(const class location& l, const std::string& m);

	/** General error handling. */
	void error(const std::string& m);

	/**
	 * Pointer to the current lexer instance, used to connect the parser to
	 * the scanner.
	 */
	class Scanner* lexer;

	typedef NodeVector Nodes;
	Nodes nodes;

	void add(const NodePtr& node);
};

} // namespace driver