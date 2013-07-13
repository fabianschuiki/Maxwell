/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include "algorithm/type.hpp"
#include <iostream>

using namespace ast;
using stage::CalcRequiredTypes;
using boost::dynamic_pointer_cast;

void CalcRequiredTypes::process(const NodePtr& node)
{
	// Assignments require the rhs to match the lhs.
	if (AssignmentExpr* expr = dynamic_cast<AssignmentExpr*>(node.get())) {
		const NodePtr& lhs = expr->getLhs();
		const NodePtr& type = lhs->needType()->getPossibleType();
		expr->getRhs()->needType()->setRequiredType(type);
		addDependency(lhs, "possibleType");
	}

	// Variables require the initial expression to match the variable type.
	if (VarDefExpr* var = dynamic_cast<VarDefExpr*>(node.get())) {
		const NodePtr& init = var->getInitialExpr(false);
		if (init) {
			const NodePtr& type = var->getType(false);
			if (type) {
				init->needType()->setRequiredType(type->needTypeExpr()->getEvaluatedType());
			}
			addDependency(node, "type.evaluatedType");
		}
	}

	// For calls we unify the input argument tuples and then assign the
	// resulting tuple as a requirement to each call argument individually.
	if (CallInterface* call = node->asCall())
	{
		// Build a list of candidate types and assign the call's required type
		// as each candidate's required type.
		const NodeVector& candidates = call->getCallCandidates();
		vector<NodeVector> inputTypes(call->getCallArgs().size());

		for (NodeVector::const_iterator it = candidates.begin(); it != candidates.end(); it++) {
			const CallCandidate::Ptr& candidate = CallCandidate::needFrom(*it);
			const FuncDef::Ptr& func = FuncDef::needFrom(candidate->getFunc());
			const FuncType::Ptr& funcType = FuncType::needFrom(func->getType());

			// Calculate the required types for each argument.
			const TupleType::Ptr& funcTypeIn = TupleType::needFrom(funcType->getIn());
			const NodeVector& funcTypeArgs = funcTypeIn->getArgs();
			const NodeVector& args = candidate->getArgs();
			addDependency(func, "type.in.types");

			for (int i = 0; i < args.size(); i++) {
				NodePtr type;
				if (i < funcTypeArgs.size()) {
					const TupleTypeArg::Ptr& funcTypeArg = TupleTypeArg::needFrom(funcTypeArgs[i]);
					type = funcTypeArg->getType();
					inputTypes[i].push_back(type);
				} else {
					type = NodePtr(new InvalidType);
				}
				args[i]->needType()->setRequiredType(type);
			}

			// Calculate the output type of this candidate.
			candidate->needType()->setRequiredType(node->needType()->getRequiredType());
			addDependency(node, "requiredType");
		}

		// For each call argument, use the inputTypes vector to find the set
		// of required types this argument must adhere to.
		const NodeVector& args = call->getCallArgs();
		for (int i = 0; i < args.size(); i++) {
			CallArgInterface* arg = args[i]->needCallArg();
			NodePtr type;
			if (i < inputTypes.size()) {
				TypeSet::Ptr typeSet(new TypeSet);
				typeSet->setTypes(inputTypes[i]);
				type = algorithm::type::simplify(typeSet);
			} else {
				type = NodePtr(new InvalidType);
			}
			arg->getExpr()->needType()->setRequiredType(type);
		}
	}

	// Operate on the children
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);

		// Children without a type requirement configured have their required type
		// set to the generic type.
		if (TypeInterface* intf = (*it)->asType()) {
			if (!intf->getRequiredType(false)) {
				intf->setRequiredType(NodePtr(new GenericType));
			}
			println(1, intf->getRequiredType()->describe(), *it);
		}
	}
}