/* Copyright (c) 2013 Fabian Schuiki */
#include "maxwell/stage/stages.hpp"
#include <iostream>

using namespace ast;
using stage::BindNamedTypes;

void BindNamedTypes::process(const NodePtr& node)
{
	// Bind the named types of the node's children.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Operate on all identifier nodes.
	if (NamedTypeExpr *type = dynamic_cast<NamedTypeExpr*>(node.get())) {
		// Do nothing if the name is already bound.
		if (type->getDefinition(false))
			return;

		// Traverse graph looking for a type with this name.
		NodePtr current(type->needGraph()->getGraphPrev());
		NodeId target;
		const string& name = type->getName();
		while (current) {
			if (TypeDef *def = dynamic_cast<TypeDef*>(current.get())) {
				if (def->getName() == name) {
					target = current->getId();
					break;
				}
			}
			current = current->needGraph()->getGraphPrev(false);
		}

		// Find an external type if nothing has been found yet.
		if (target.empty()) {
			const Repository::ExternalNames& externals = repository.getExternalNamesForNodeId(node->getId());
			for (Repository::ExternalNames::const_iterator it = externals.begin(); it != externals.end(); it++) {
				if (it->second == name) {
					target = it->first;
				}
			}
		}

		// Check whether we've found something.
		if (target.empty()) {
			throw std::runtime_error("No type named '" + name + "' found for identifier '" + node->getId().str() + "'.");
		}
		type->setDefinition(target);
	}
}
