/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>

using namespace ast;
using stage::BindIdentifiers;

void BindIdentifiers::process(const NodePtr& node)
{
	// Bind the identifiers of the node's children.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Operate on all identifier nodes.
	if (IdentifierExpr *ident = dynamic_cast<IdentifierExpr*>(node.get())) {
		// Do nothing if the identifier already has a valid target.
		if (ident->getBindingTarget())
			return;

		// Traverse graph looking for any object with this name.
		NodePtr current(ident->asGraph()->getGraphPrev());
		NodeId target;
		const string& name = ident->getName();
		while (current) {
			// Bind to function arguments.
			if (FuncArg *arg = dynamic_cast<FuncArg*>(current.get())) {
				if (arg->getName() == name) {
					target = current->getId();
					break;
				}
			}

			// Bind to variable definitions.
			/*if (VarDefExpr *var = dynamic_cast<VarDefExpr*>(current.get())) {
				if (var->getName() == name) {
					target = current->getId();
					break;
				}
			}*/

			current = current->asGraph()->getGraphPrev();
		}

		// Find an external entity.
		/*if (target.empty()) {
			const Repository::ImportedNames& externals = repository->getImportedNamesForNodeId(node->getId());
			for (Repository::ImportedNames::const_iterator it = externals.begin(); it != externals.end(); it++) {
				if (it->second == name) {
					target = it->first;
				}
			}
		}*/

		// Check whether we've found something.
		if (target.empty()) {
			throw std::runtime_error("No node named '" + name + "' found for identifier '" + node->getId().str() + "'.");
		}
		ident->setBindingTarget(target);
	}
}