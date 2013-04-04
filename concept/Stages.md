Driver Stages
=============

### CalculatePossibleTypes
Calculates a rough estimate of each object's possible types.

- AbstractFunctionArgument: (`name`, `typeExpr.evaluatedType`)
- AbstractFunctionArgumentTuple: (`[arguments.*.possibleType]`)
- AbstractFunctionDefinition: (`inputs.possibleType`, `outputs.possibleType`)
- CallInterface: *not yet specified*