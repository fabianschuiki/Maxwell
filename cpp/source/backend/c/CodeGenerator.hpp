/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include <ast/Node.hpp>
#include <ast/Repository.hpp>
#include <ast/nodes/ast.hpp>

namespace backendc {

using namespace ast;

class Repository;

/**
 * @brief Converts an AST into C code.
 *
 * This class operates on nodes previously processed by the various stages
 * of the frontend. It generates compilable C code from these AST nodes and
 * throws exceptions whenever something could not be compiled.
 */
class CodeGenerator
{
public:
	ast::Repository& nodeRepository;
	backendc::Repository& backendRepository;

	CodeGenerator(ast::Repository& nr, backendc::Repository& br);

	void run(const NodePtr& node);
	void run(const NodeId& id);

protected:
	void generateFuncDef(const FuncDef::Ptr& node);
	void generateTypeDef(const TypeDef::Ptr& node);
};

} // namespace backendc