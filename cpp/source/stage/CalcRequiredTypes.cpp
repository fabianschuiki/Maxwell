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
	if (const AssignmentExpr::Ptr& expr = AssignmentExpr::from(node)) {
		const NodePtr& lhs = expr->getLhs();
		if (!lhs->isKindOf(kCallExpr)) {
			const NodePtr& type = lhs->needType()->getPossibleType();
			expr->getRhs()->needType()->setRequiredType(type);
			addDependency(lhs, "possibleType");
		}
	}

	// Variables require the initial expression to match the variable type.
	if (const VarDefExpr::Ptr& var = VarDefExpr::from(node)) {
		const NodePtr& init = var->getInitialExpr(false);
		if (init) {
			const NodePtr& typeExpr = var->getTypeExpr(false);
			if (typeExpr) {
				init->needType()->setRequiredType(typeExpr->needTypeExpr()->getEvaluatedType());
			}
			addDependency(node, "typeExpr.evaluatedType");
		}
	}

	// For calls we unify the input argument tuples and then assign the
	// resulting tuple as a requirement to each call argument individually.
	if (CallInterface* call = node->asCall())
	{
		addDependency(node, "selectedCallCandidate");
		const CallCandidate::Ptr& selectedCandidate = CallCandidate::from(call->getSelectedCallCandidate(false));
		if (selectedCandidate) {
			// Assign the candidate's argument types to the corresponding call arguments.
			const NodeVector& candidateArgs = selectedCandidate->getArgs();
			const NodeVector& args = call->getCallArgs();
			for (int i = 0; i < args.size(); i++) {
				CallArgInterface* arg = args[i]->needCallArg();
				const NodePtr& type = candidateArgs[i]->needType()->getRequiredType();
				arg->getExpr()->needType()->setRequiredType(type);
			}
		} else {
			// Build a list of candidate types and assign the call's required type
			// as each candidate's required type.
			const NodeVector& candidates = call->getCallCandidates();
			vector<NodeVector> inputTypes(call->getCallArgs().size());

			for (NodeVector::const_iterator it = candidates.begin(); it != candidates.end(); it++) {
				const CallCandidate::Ptr& candidate = CallCandidate::needFrom(*it);
				if (!candidate->getFeasible()) continue;

				// Fetch the FuncType either from the candidate's func or funcExpr.
				FuncType::Ptr funcType;
				const NodePtr& funcNode = candidate->getFunc();
				if (CallableInterface* func = funcNode->asCallable()) {
					funcType = FuncType::needFrom(func->getType());
					addDependency(funcNode, "type.in");
				} else {
					funcType = FuncType::needFrom(funcNode->needType()->getActualType());
					addDependency(funcNode, "actualType.in");
				}
				const TupleType::Ptr& inTupleType = TupleType::from(funcType->getIn());

				// Calculate the required types for each argument.
				const NodeVector& args = candidate->getArgs();

				for (int i = 0; i < args.size(); i++) {
					NodePtr type;
					if (inTupleType && i < inTupleType->getArgs().size()) {
						const TupleTypeArg::Ptr& funcArg = TupleTypeArg::needFrom(inTupleType->getArgs()[i]);
						type = funcArg->getType();
						inputTypes[i].push_back(type);
						addDependency(funcArg, "type");
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
		} // selectedCandidate
	}

	// Array, set and map literals allow us to pass on the type specialization as
	// type requirements to the literal's individual expressions.
	if (const ArrayConstExpr::Ptr& expr = ArrayConstExpr::from(node)) 
	{
		// Determine the first type of the array specialization.
		NodePtr elementType;
		const SpecializedType::Ptr& specType = SpecializedType::from(expr->getRequiredType());
		if (specType && specType->getSpecs().size() > 0) {
			elementType = specType->getSpecs()[0];
		}

		// Set this type as the required type for each individual array element.
		const NodeVector& exprs = expr->getExprs();
		for (NodeVector::const_iterator it = exprs.begin(); it != exprs.end(); it++) {
			(*it)->needType()->setRequiredType(elementType);
		}
	}

	// IfCaseExprs force their conditional expressions to be of boolean type. The
	// required type is passed through to the expressions transparently.
	if (const IfCaseExpr::Ptr& expr = IfCaseExpr::from(node)) {

		const NodePtr& requiredType = expr->getRequiredType();
		DefinedType::Ptr boolType(new DefinedType);
		boolType->setDefinition(repository.getBuiltinType("Bool"));

		const NodeVector& conds = expr->getConds();
		for (NodeVector::const_iterator it = conds.begin(); it != conds.end(); it++) {
			const IfCaseExprCond::Ptr& cond = IfCaseExprCond::from(*it);
			cond->getExpr()->needType()->setRequiredType(requiredType);
			cond->getCond()->needType()->setRequiredType(boolType);
		}
		const NodePtr& othw = expr->getOtherwise(false);
		if (othw) {
			othw->needType()->setRequiredType(requiredType);
		}
	}

	// Blocks pass on the type requirement to the last expression contained in them.
	if (const BlockExpr::Ptr& expr = BlockExpr::from(node)) {
		if (!expr->getExprs().empty()) {
			const NodePtr& requiredType = expr->getRequiredType();
			const NodePtr& last = expr->getExprs().back();
			last->needType()->setRequiredType(requiredType);
		}
	}

	// IfExprs pass on the type requirement to both branches.
	if (const IfExpr::Ptr& expr = IfExpr::from(node)) {
		const NodePtr& requiredType = expr->getRequiredType();
		const NodePtr& bodyBranch = expr->getBody();
		bodyBranch->needType()->setRequiredType(requiredType);
		const NodePtr& elseBranch = expr->getElseExpr(false);
		if (elseBranch) {
			elseBranch->needType()->setRequiredType(requiredType);
		}
	}

	// ForExprs don't do anything at the moment. This should change in the future.

	// Operate on the children
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++)
	{
		// Children without a type requirement configured have their required type
		// set to the generic type.
		if (TypeInterface* intf = (*it)->asType()) {
			if (!intf->getRequiredType(false)) {
				intf->setRequiredType(NodePtr(new GenericType));
			}
			println(1, intf->getRequiredType()->describe(), *it);
		}

		// Process the child node.
		process(*it);
	}
}