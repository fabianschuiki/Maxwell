/* Copyright (c) 2013 Fabian Schuiki */
#include "maxwell/stage/stages.hpp"
#include <iostream>

using namespace ast;
using stage::EvalTypeExprs;

void EvalTypeExprs::process(const NodePtr& node)
{
	// Evaluate children's type expressions.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		process(*it);
	}

	// Operate on type expressions.
	if (TypeExprInterface *intf = node->asTypeExpr())
	{
		// Do nothing if the type expression is already evaluated.
		if (intf->getEvaluatedType(false))
			return;

		// Otherwise operate on all known expressions.
		if (const NamedTypeExpr::Ptr& expr = NamedTypeExpr::from(node)) {
			const NodePtr& def = expr->getDefinition();
			assert(def && "NamedTypeExpr without a resolved definition.");
			DefinedType::Ptr t(new DefinedType);
			t->setDefinition(def);
			intf->setEvaluatedType(t);
			node->updateHierarchyOfChildren();
		}

		if (node->isKindOf(kNilTypeExpr)) {
			intf->setEvaluatedType(NodePtr(new NilType));
			node->updateHierarchyOfChildren();
		}

		if (const UnionTypeExpr::Ptr& expr = UnionTypeExpr::from(node)) {
			const NodeVector& typeExprs = expr->getTypes();
			NodeVector types(typeExprs.size());
			for (unsigned i = 0; i < typeExprs.size(); i++) {
				types[i] = typeExprs[i]->asTypeExpr()->getEvaluatedType();
			}
			UnionType::Ptr t(new UnionType);
			t->setTypes(types);
			intf->setEvaluatedType(t);
			node->updateHierarchyOfChildren();
		}

		if (const QualifiedTypeExpr::Ptr& expr = QualifiedTypeExpr::from(node))
		{
			// Compile a list of qualifiers of this type.
			NodeVector typeMembers, typeFuncs, typeNatives, typeRanges;
			const NodeVector& exprs = expr->getExprs();
			for (NodeVector::const_iterator it = exprs.begin(); it != exprs.end(); it++)
			{
				// Iterate through the statements of structure qualifiers to extract the members.
				if (const StructureQualifier::Ptr& quali = StructureQualifier::from(*it)) {
					const NodeVector& stmts = quali->getStmts();

					for (NodeVector::const_iterator is = stmts.begin(); is != stmts.end(); is++) {
						const StructureQualifierMember::Ptr& member = StructureQualifierMember::needFrom(*is);

						QualifiedTypeMember::Ptr qtm(new QualifiedTypeMember);
						qtm->setName(member->getName());
						const NodePtr& type = member->getType(false);
						if (type) qtm->setType(type->needTypeExpr()->getEvaluatedType());
						typeMembers.push_back(qtm);
					}
				}
				// else if (const InterfaceQualifier::Ptr& quali = InterfaceQualifier::from(*it)) {
				// 	// TODO: Ignored for now...
				// }
				else if (const NativeQualifier::Ptr& quali = NativeQualifier::from(*it)) {
					QualifiedTypeNative::Ptr qtn(new QualifiedTypeNative);
					qtn->setName(quali->getName());
					typeNatives.push_back(qtn);
				}
				// else if (const RangeQualifier::Ptr& quali = RangeQualifier::from(*it)) {
				// 	// TODO: Ignored for now...
				// }
			}

			// Merge the list of qualifiers into a new instance of QualifiedType.
			QualifiedType::Ptr qt(new QualifiedType);
			qt->setMembers(typeMembers);
			qt->setFuncs(typeFuncs);
			qt->setNatives(typeNatives);
			qt->setRanges(typeRanges);

			// Store this qualified type in the type expression.
			intf->setEvaluatedType(qt);
			node->updateHierarchyOfChildren();
		}

		if (const SpecializedTypeExpr::Ptr& expr = SpecializedTypeExpr::from(node))
		{
			// Gather a list of the evaluated types of all specExprs.
			const NodeVector& specExprs = expr->getSpecExprs();
			NodeVector types(specExprs.size());
			for (unsigned i = 0; i < specExprs.size(); i++) {
				types[i] = specExprs[i]->needTypeExpr()->getEvaluatedType();
			}

			// Merge into a proper type and store as the node's new evaluated type.
			SpecializedType::Ptr st(new SpecializedType);
			st->setType(expr->getExpr()->needTypeExpr()->getEvaluatedType());
			st->setSpecs(types);
			intf->setEvaluatedType(st);
			node->updateHierarchyOfChildren();
		}

		if (const TupleTypeExpr::Ptr& expr = TupleTypeExpr::from(node))
		{
			// Gather the list of fields of this tuple type.
			const NodeVector& exprArgs = expr->getArgs();
			NodeVector args(exprArgs.size());
			for (unsigned i = 0; i < exprArgs.size(); i++) {
				const TupleTypeExprArg::Ptr& exprArg = TupleTypeExprArg::needFrom(exprArgs[i]);
				TupleTypeArg::Ptr arg(new TupleTypeArg);
				arg->setName(exprArg->getName(false));
				arg->setType(exprArg->getExpr()->needTypeExpr()->getEvaluatedType());
				args[i] = arg;
			}

			// Merge the fields into a TupleType.
			TupleType::Ptr type(new TupleType);
			type->setArgs(args);
			intf->setEvaluatedType(type);
			node->updateHierarchyOfChildren();
		}

		if (const FuncTypeExpr::Ptr& expr = FuncTypeExpr::from(node))
		{
			FuncType::Ptr type(new FuncType);
			type->setIn(expr->getIn()->needTypeExpr()->getEvaluatedType()->copy());
			type->setOut(expr->getOut()->needTypeExpr()->getEvaluatedType()->copy());
			intf->setEvaluatedType(type);
			node->updateHierarchyOfChildren();
		}

		// Throw an error if we were unable to assign an evaluated type.
		if (!intf->getEvaluatedType(false)) {
			throw std::runtime_error("Could not evaluate type expression " + node->getId().str() + ".");
		}
	}
}
