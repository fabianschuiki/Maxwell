/* Copyright (c) 2013-2015 Fabian Schuiki */
#include "maxwell/backend/c/codegen/detail.hpp"

DEF_EXPR(IdentifierExpr) {
	const NodeId& id = node->getBindingTarget()->getId();

	// Lookup the entity that this identifier is bound to.
	auto i = ctx.vars.find(id);
	if (i == ctx.vars.end()) {
		throw std::runtime_error(
			"Identifier " + node->getName() + " is bound to target " + id.str() +
			" (a " + node->getBindingTarget()->getClassName() +
			") for which no name has been generated.");
	}


	// Configure the output.
	out.code = i->second;
	if (const auto& target = node->asType()) {
		const auto& at = target->getActualType();
		if (at->isKindOf(kImmutableCastType)) {
			out.code = "(*" + i->second + ")";
		}
		if (at->isKindOf(kMutableCastType)) {
			out.code = "(&" + i->second + ")";
		}
	}
	out.isRef = true;
	out.precedence = kPrimaryPrec;
}
