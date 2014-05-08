/* Copyright (c) 2014 Fabian Schuiki */
#include <driver/Driver.hpp>
#include <ast/Node.hpp>
#include <boost/test/unit_test.hpp>

typedef ast::NodePtr NodePtr;
extern driver::Driver drv;

extern void parse(const std::string& input);
extern std::string structure(const NodePtr& node, int depth = -1);


#define PARSE(n)\
	try { parse(n); }\
	catch (std::exception& e) { BOOST_FAIL(e.what()); }\
	BOOST_REQUIRE(drv.nodes.size() == 1);\
	NodePtr node = drv.nodes.front();

#define INSPECT(p) const NodePtr& tmp = node->resolvePath(p); const NodePtr& node = tmp;

#define CHECK_STRUCTURE(s) BOOST_CHECK_EQUAL(structure(node), s)
#define INSPECT_STRUCTURE(p,s) { INSPECT(p); CHECK_STRUCTURE(s); }

#define CHECK_STRUCTURE_LIMITED(s,d) BOOST_CHECK_EQUAL(structure(node,d), s)
#define INSPECT_STRUCTURE_LIMITED(p,s,d) { INSPECT(p); CHECK_STRUCTURE(s,d); }
