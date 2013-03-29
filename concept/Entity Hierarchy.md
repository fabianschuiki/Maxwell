Entity Hierarchy
================
This document describes the entity hierarchy and how entity information is fragmented upon persisting.

### Goals
The following is a brief overview of what the system should be able to achieve:

- **load entities lazily**: Wait for the program to ask for a certain information before reading that fragment from disk.
- **load root entities sparely**: Accessing a function's arguments should not trigger the entire function body to be loaded.


### Common Properties
The following properties are common among all repository objects:

- `id` Unique identification number of the entity.
- `class` Class of the entity. Used upon reading from disk to determine what object to instantiate.

### Identifier
- Properties
	- string
- Hierarchy
	- range
- Binding
	- target
- Type
	- type

### Binary Operator
- Properties
	- operator
- Hierarchy
	- range
	- lhs
	- rhs
- Call
	- callee
	- arguments