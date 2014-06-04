/* Copyright (c) 2014 Fabian Schuiki */
#define BOOST_TEST_MODULE parser
#include "detail.hpp"

/** Catches a parser issue where (x,2,3) would be mistaken for the beginning of
 * a func_expr, rather than parsed as a tuple. */
BOOST_AUTO_TEST_CASE(tuple_vs_funcexpr)
{
	PARSE("func main { (1,2,3); (1,y,z); (x,2,3); }");

	// A regular tuple of integers.
	{	INSPECT("body.exprs.0");
		INSPECT_STRUCTURE("args.0.expr", "NumberConstExpr{ value = \"1\" }");
		INSPECT_STRUCTURE("args.1.expr", "NumberConstExpr{ value = \"2\" }");
		INSPECT_STRUCTURE("args.2.expr", "NumberConstExpr{ value = \"3\" }");
	}

	// A tuple starting with a number expression, but continues with identifiers.
	{	INSPECT("body.exprs.1");
		INSPECT_STRUCTURE("args.0.expr", "NumberConstExpr{ value = \"1\" }");
		INSPECT_STRUCTURE("args.1.expr", "IdentifierExpr{ name = \"y\" }");
		INSPECT_STRUCTURE("args.2.expr", "IdentifierExpr{ name = \"z\" }");
	}

	// A tuple starting with an identifier, but continues with numbers.
	{	INSPECT("body.exprs.2");
		INSPECT_STRUCTURE("args.0.expr", "IdentifierExpr{ name = \"x\" }");
		INSPECT_STRUCTURE("args.1.expr", "NumberConstExpr{ value = \"2\" }");
		INSPECT_STRUCTURE("args.2.expr", "NumberConstExpr{ value = \"3\" }");
	}
}
