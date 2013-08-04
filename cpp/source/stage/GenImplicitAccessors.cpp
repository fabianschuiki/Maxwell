/* Copyright © 2013 Fabian Schuiki */
#include "stages.hpp"
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace ast;
using stage::GenImplicitAccessors;
using boost::lexical_cast;

void GenImplicitAccessors::process(const NodePtr& node)
{
	// Process children.
	processChildren(node);

	// Gather implicit accessors for root type definitions.
	if (const TypeDef::Ptr& typeDef = TypeDef::from(node)) {
		NodeVector implicits;
		gatherImplAccessors(typeDef, implicits);
		println(0, "Gathered " + lexical_cast<string>(implicits.size()) + " implicit accessors of " + typeDef->getId().str() + ".");

		// Add the accessors to the repository.
		for (NodeVector::iterator it = implicits.begin(); it != implicits.end(); it++) {
			repository.addExportedSymbol((*it)->getId(), (*it)->needNamed()->getName());
		}
	}
}

void GenImplicitAccessors::processChildren(const NodePtr& node)
{
	// Process the node's children first.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		processChildren(*it);
	}

	// Generate accessors for members of structure qualifiers.
	if (const QualifiedTypeExpr::Ptr& typeExpr = QualifiedTypeExpr::from(node))
	{
		println(0, "Type expr has evaluated type " + typeExpr->getEvaluatedType()->getId().str(), node);

		// Create a type that refers back to this qualified type expression.
		// DefinedType::Ptr self(new DefinedType);
		// self->setDefinition(typeExpr->getEvaluatedType());

		// Process each type expression individually.
		const NodeVector& exprs = typeExpr->getExprs();
		for (NodeVector::const_iterator is = exprs.begin(); is != exprs.end(); is++) {
			const StructureQualifier::Ptr& quali = StructureQualifier::from(*is);
			if (!quali) continue;
			println(0, "Generating implicit accessors of " + quali->getId().str() + ".");

			// Iterate through the members and perform operations.
			const NodeVector& members = quali->getStmts();
			for (NodeVector::const_iterator it = members.begin(); it != members.end(); it++) {
				const StructureQualifierMember::Ptr& member = StructureQualifierMember::needFrom(*it);

				// Generate the argument templates.
				TupleTypeArg::Ptr refArg(new TupleTypeArg), valueArg(new TupleTypeArg), retArg(new TupleTypeArg);
				refArg->setType(typeExpr->getEvaluatedType());
				valueArg->setType(member->getType()->needTypeExpr()->getEvaluatedType());
				retArg->setType(member->getType()->needTypeExpr()->getEvaluatedType());

				// Generate the setter.
				ImplAccessor::Ptr setter(new ImplAccessor);
				setter->setName(member->getName() + "=");
				
				NodeVector setterIn, setterOut;
				setterIn.push_back(refArg);
				setterIn.push_back(valueArg);
				setterOut.push_back(retArg);
				
				TupleType::Ptr setterInTuple(new TupleType), setterOutTuple(new TupleType);
				setterInTuple->setArgs(setterIn);
				setterOutTuple->setArgs(setterOut);

				FuncType::Ptr setterType(new FuncType);
				setterType->setIn(setterInTuple);
				setterType->setOut(setterOutTuple);
				setter->setType(setterType);


				// Generate the getter.
				ImplAccessor::Ptr getter(new ImplAccessor);
				getter->setName(member->getName());

				NodeVector getterIn, getterOut;
				getterIn.push_back(NodePtr(refArg));
				getterOut.push_back(NodePtr(retArg));

				TupleType::Ptr getterInTuple(new TupleType), getterOutTuple(new TupleType);
				getterInTuple->setArgs(getterIn);
				getterOutTuple->setArgs(getterOut);

				FuncType::Ptr getterType(new FuncType);
				getterType->setIn(getterInTuple);
				getterType->setOut(getterOutTuple);
				getter->setType(getterType);

				// Store the accessors.
				member->setImplSetter(setter);
				member->setImplGetter(getter);
				member->updateHierarchyOfChildren();
			}
		}
	}
}

void GenImplicitAccessors::gatherImplAccessors(const NodePtr& node, NodeVector& into)
{
	// Gather getters and setters.
	if (node->isKindOf(kImplAccessor)) {
		into.push_back(node);
	}

	// Gather accessors of the children.
	const NodeVector& children = node->getChildren();
	for (NodeVector::const_iterator it = children.begin(); it != children.end(); it++) {
		gatherImplAccessors(*it, into);
	}
}