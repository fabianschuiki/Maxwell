Driver Stages
=============
This document describes the compilation stages of the driver. For each stage the operation is roughly sketched. This document should help debugging as it highlights where information in the repository is generated and how.

Operation
---------

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

### CalculateRequiredTypes
Calculates the type constraints objects impose on their children.

- **AssignmentExpr**: `rhs.requiredType` = `lhs.possibleType`
- **CallInterface**: Each argument's type is the set of types of the input arguments at this location of all candidates.


Requires Testing
----------------
- What if a call has no matching call candidates?
- What if a call has no return value? What happens to the parents if it is embedded somewhere that expects a type? 