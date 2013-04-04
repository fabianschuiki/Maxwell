Driver Stages
=============

### CalculatePossibleTypes
Calculates a rough estimate of each object's possible types.

- **AbstractFunctionArgument**: (`name`, `typeExpr.evaluatedType`)
- **AbstractFunctionArgumentTuple**: (`[arguments.*.possibleType]`)
- **AbstractFunctionDefinition**: (`inputs.possibleType`, `outputs.possibleType`)
- **CallInterface**: Set of output argument tuples of different length, where all argument tuples of the same length are merged into each other, producing arguments which have a set of types as type.
- **IdentifierExpr**: Type depends on target:
	- AbstractFunctionArgument: `possibleType.type`
	- otherwise: *null*
- **AssignmentExpr**: `lhs.possibleType`
