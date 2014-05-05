/* Copyright (c) 2014 Fabian Schuiki */
#include "detail.hpp"
#include <ast/builtin/NumericType.hpp>

DEF_TYPE(DefinedType)
{
	const NodePtr& def = node->getDefinition();

	// Builtin numeric types may be synthesized directly.
	if (const builtin::NumericType::Ptr& num = builtin::NumericType::from(def)) {
		if (num->getName() == "Int") {
			out.code = "int";
			return;
		} else if (num->getName() == "Real") {
			out.code = "float";
			return;
		} else {
			throw std::runtime_error("Code generation for builtin type " + num->getId().str() + " (" + num->getName() + ") not implemented.");
		}
	}

	// Type definitions generate a typedef statement, which allows other parts
	// of the code to simply use them by name.
	if (const TypeDef::Ptr& td = TypeDef::from(def)) {
		out.code = "%{" + td->getId().str() + "}";
		out.deps.insert(td->getId().str());
		return;
	}
}
