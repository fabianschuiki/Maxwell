Entity Hierarchy
================
This document describes the entity hierarchy and how entity information is fragmented upon persisting. The entities are persisted in the repository as `objects/<sourceId>/<rootId>`.

### Goals
The following is a brief overview of what the system should be able to achieve:

- **load entities lazily**: Wait for the program to ask for a certain information before reading that fragment from disk.
- **load root entities sparely**: Accessing a function's arguments should not trigger the entire function body to be loaded.


### Common Properties
The following properties are common among all repository objects:

- `id` Unique identification number of the entity. Source file that spawned the entity is visible in its ID.
- `class` Class of the entity. Used upon reading from disk to determine what object to instantiate.

### Fragments
- **call**: name, arguments, candidates
- **type**: type
- **code**: independentDeclarations, dependentDeclarations, definitions

### Objects
- **Identifier** *Expression*
	- range, name
	- target
	- type
- **VariableDefinition** *Expression*
	- range, human_range, name, type_expr, initial_expr
	- type
	- code
- **BinaryOperator** *Expression*
	- range, human_range, operator, lhs, rhs
	- *call*: name, arguments, candidates
	- type
	- code
- **UnaryOperator** *Expression*
	- range, human_range, operator, operand
	- *call*: name, arguments, candidates
	- type
	- code
- **Call** *Expression*
	- range, human_range, callee, arguments
	- *call*: name, arguments, candidates
	- type
	- code