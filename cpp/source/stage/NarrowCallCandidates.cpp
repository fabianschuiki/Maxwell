/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>

using namespace ast;
using stage::NarrowCallCandidates;

void NarrowCallCandidates::process(const NodePtr& node)
{
	// Process the node's children first.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Mark CallCandidates with InvalidTypes as not feasible, as the type
	// conversion is not possible in those cases. In general calculate the cost
	// a given call candidate has.
	if (const CallCandidate::Ptr& candidate = CallCandidate::from(node))
	{
		// Check feasibility and cost of the candidate's arguments.
		int cost = 0;
		bool feasible = true;
		const NodeVector& args = candidate->getArgs();

		for (NodeVector::const_iterator it = args.begin(); it != args.end(); it++) {
			const NodePtr& type = CallCandidateArg::needFrom(*it)->getActualType();
			// if (const CastType::Ptr& cast = CastType::from(type)) {
			// 	cost += cast->getCost();
			// }
			if (type->isKindOf(kInvalidType)) {
				feasible = false;
			}
		}

		// Check feasibility and cost of the candidate's output.
		if (feasible) {
			const NodePtr& type = candidate->getActualType();
			// if (const CastType::Ptr& cast = CastType::from(type)) {
			// 	cost += cast->getCost();
			// }
			if (type->isKindOf(kInvalidType)) {
				feasible = false;
			}
		}

		// Store the gathered cost and feasibility information in the candidate node.
		candidate->setCost(cost);
		candidate->setFeasible(feasible);
	}
}