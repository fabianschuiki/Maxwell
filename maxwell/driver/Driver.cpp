/* Copyright (c) 2013-2015 Fabian Schuiki */
#include "maxwell/ast/nodes/ast.hpp"
#include "maxwell/driver/Driver.hpp"
#include "maxwell/diagnostic/diagnostic.hpp"
#include "maxwell/memory.hpp"
#include <vector>

using namespace ast;
typedef std::vector<NodePtr> Nodes;

#include "maxwell/driver/Scanner.hpp"
#include <fstream>
#include <sstream>

using driver::Driver;
using namespace maxwell;

Driver::Driver(int dl) {
	debugLevel = dl;
}

bool
Driver::parseStream(
	std::istream& in,
	const std::string& name,
	const maxwell::SourceLocation& start) {

	streamname = name; // for error messages;
	Scanner scanner(&in);
	this->lexer = &scanner;
	Parser parser(*this, start);
	parser.set_debug_level(debugLevel);
	return (parser.parse() == 0);
}

bool
Driver::parseFile(
	const std::string& filename,
	const maxwell::SourceLocation& start) {

	std::ifstream in(filename.c_str());
	if (!in.good()) return false;
	return parseStream(in, filename, start);
}

void
Driver::error(const maxwell::SourceRange& l, const std::string& m) {
	if (dc) {
		auto d = make_unique<Diagnostic>();
		auto msg = make_unique<DiagnosticMessage>(kError, m);
		msg->setMainRange(l);
		d->add(std::move(msg));
		dc->add(std::move(d));
	}
}

void
Driver::error(const std::string& m) {
	throw std::runtime_error(m);
}

void
Driver::add(const NodePtr& node) {
	nodes.push_back(node);
}

void
Driver::add(std::unique_ptr<Diagnostic>&& d) {
	if (dc) {
		dc->add(std::move(d));
	}
}

