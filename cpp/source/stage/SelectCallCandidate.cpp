/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>

using namespace ast;
using stage::SelectCallCandidate;

template <typename T> std::string toString(const T& v)
{
	std::stringstream s;
	s << v;
	return s.str();
}

void SelectCallCandidate::process(const NodePtr& node)
{
	// Process the node's children first.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Only operate on nodes implementing the CallInterface.
	CallInterface* callIntf = node->asCall();
	if (!callIntf) return;

	// Calculate the lowest possible cost of all call candidates.
	int lowestCost = INT_MAX;
	const NodeVector& candidates = callIntf->getCallCandidates();

	for (NodeVector::const_iterator it = candidates.begin(); it != candidates.end(); it++) {
		const CallCandidate::Ptr& candidate = CallCandidate::needFrom(*it);
		if (candidate->getFeasible() && candidate->getCost() < lowestCost) {
			lowestCost = candidate->getCost();
		}
		addDependency(candidate, "feasible");
		addDependency(candidate, "cost");
	}

	// Make a list of all feasible call candidates that have the lowest cost calculated above.
	NodeVector finalCandidates;
	for (NodeVector::const_iterator it = candidates.begin(); it != candidates.end(); it++) {
		const CallCandidate::Ptr& candidate = CallCandidate::needFrom(*it);
		if (candidate->getFeasible() && candidate->getCost() <= lowestCost) {
			finalCandidates.push_back(candidate);
		}
	}

	// Throw an error if we got none or multiple feasible candidates, or select
	// the one candidate in the list.
	if (finalCandidates.empty()) {
		throw std::runtime_error("No feasible function out of " + toString(candidates.size()) + " candidates for call " + node->getId().str() + ".");
	} else if (finalCandidates.size() > 1) {
		throw std::runtime_error("Ambiguous call " + node->getId().str() + " has " + toString(finalCandidates.size()) + " feasible functions out of " + toString(candidates.size()) + " candidates.");
	} else {
		const CallCandidate::Ptr& finalCandidate = CallCandidate::needFrom(finalCandidates.front());
		callIntf->setSelectedCallCandidate(finalCandidate);
		println(0, "Selected candidate " + finalCandidate->getFunc()->getId().str(), node);
	}
}