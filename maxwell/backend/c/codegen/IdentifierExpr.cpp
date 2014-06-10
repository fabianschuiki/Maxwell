/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_EXPR(IdentifierExpr)
{
	const NodeId& id = node->getBindingTarget()->getId();

	// Lookup the entity that this identifier is bound to.
	std::map<NodeId,std::string>::const_iterator i = ctx.vars.find(id);
	if (i == ctx.vars.end()) {
		throw std::runtime_error(
			"Identifier " + node->getName() + " is bound to target " + id.str() +
			" (a " + node->getBindingTarget()->getClassName() +
			") for which no name has been generated.");
	}

	// Configure the output.
	out.code = i->second;
	out.isRef = true;
	out.precedence = kPrimaryPrec;
}
