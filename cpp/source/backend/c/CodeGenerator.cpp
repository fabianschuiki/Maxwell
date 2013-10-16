/* Copyright © 2013 Fabian Schuiki */
#include "CodeGenerator.hpp"
#include <ast/nodes/ast.hpp>
#include <iostream>
#include <sstream>

using namespace ast;
using backendc::CodeGenerator;
using std::cout;
using std::stringstream;


CodeGenerator::CodeGenerator(ast::Repository& nr, backendc::Repository& br)
	: nodeRepository(nr), backendRepository(br)
{
}

/**
 * @brief Generates code for this node.
 */
void CodeGenerator::run(const NodePtr& node)
{
	if (const FuncDef::Ptr& func = FuncDef::from(node)) {
		generateFuncDef(func);
	} else if (const TypeDef::Ptr& type = TypeDef::from(node)) {
		generateTypeDef(type);
	} else {
		stringstream s;
		s << "Node " << node->getId() << " (" << node->getClassName() << ") cannot be compiled as a root node.";
		throw std::runtime_error(s.str());
	}
}

/**
 * @brief Generates code for the given node id.
 *
 * Looks up the node with the given id in the AST repository and calls run()
 * with that node as an argument.
 */
void CodeGenerator::run(const NodeId& id)
{
	run(nodeRepository.getNode(id));
}


void CodeGenerator::generateFuncDef(const FuncDef::Ptr& node)
{
}

void CodeGenerator::generateTypeDef(const TypeDef::Ptr& node)
{

}