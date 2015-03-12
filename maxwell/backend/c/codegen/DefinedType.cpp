/* Copyright (c) 2013-2014 Fabian Schuiki */
#include "maxwell/ast/builtin/NumericType.hpp"
#include "maxwell/backend/c/codegen/detail.hpp"

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
		} else if (num->getName() == "String") {
			out.code = "const char*";
			return;
		} else {
			throw std::runtime_error("Code generation for builtin type " +
				num->getId().str() + " (" + num->getName() +
				") not implemented.");
		}
	}

	// Type definitions generate a typedef statement, which allows other parts
	// of the code to simply use them by name.
	if (const TypeDef::Ptr& td = TypeDef::from(def)) {
		std::string name = td->getId().str() + "_def";
		out.code = "%{" + name + "}";
		out.deps.insert(name);
		return;
	}

	// Native type definitions generate a typedef statement, which allows other
	// parts of the code to simply use them by name.
	if (const auto& td = NativeTypeDef::from(def)) {
		std::string name = td->getId().str() + "_def";
		out.code = "%{" + name + "}";
		out.deps.insert(name);
		return;
	}

	throw std::runtime_error("Reference code generation for defined type " +
		def->getId().str() + " (a " + def->getClassName() +
		") not implemented.");
}
