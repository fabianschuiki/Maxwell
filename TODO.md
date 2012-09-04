Random TODOs
============

- Storing the entity IDs per root entity is not required if, when loading a root entity, all entity ids are registered with the entity store.
- Assign token and AST node IDs on a per-file level.
- In the Entitializer, feedback the entity IDs to the AST and/or tokens that spawned the entity. Use this information when storing the `.tokens` file. This faciliates writing of IDEs and even some command line tools.
- Work on Entitializer to not only create root entities, but also their child entities.
- Create an `Entity\TypeDef` class that wraps around an `AST\Stmt\TypeDef`. It should contain an identifier to its superclass which may be bound later.
- Add raw C types to the language, possibly through a prefix like `@` or `$`. These should become obsolete as the language evolves. Later on it might even be possible to recognize a C type without special indicator.
- Implement entity reading and decoding. Maybe it's best to read the file and create the bare objects and assign their IDs. Then in a second pass initialize the objects and setup object relationships.
- Implement binding. Maybe there should be an `Analysis\Node` that may be assigned to each entity which holds all the information the analyzer gathers. This way, identifiers would get an `Analysis\Ident` object that contains the binding results.
- Create a `Type` base class.
- Create an `OptionType` class which implements a set of types.
- Create a `TupleType` class which implements a named tuple of types.
- Create a `FuncType` class which consists of two `TupleType`s, one for input and for output parameters.
- Create a `ConcreteType` which references a `TypeDef` and the like.
- Calculate the type of each expression. Maybe this should be stored in an `Analysis\Expr` object (superclass of `Analysis\Ident` and the like).
- Identifiers of function calls have bound to multiple functions. Filter them according to the type information calculated before. Throw errors where types don't match.
- Add a `Compiler\Node` class that holds basic compilation information for entities. Each entity should then have such a compiler node.
- There should be a class hierarchy to create C code structures in memory, i.e. `C\IfStmt` or `C\StructStmt` or `C\Func`, from which actual C code can be generated.
- Implement the code generation. In a first pass, assign a compiler node to each entity and decide what name the entity should have. In a second pass, actually generate code fragments from the entities using the C class hierarchy created earlier.
- Put public declarations from the compiler nodes into `.h` files, private declarations and the actual definitions into `.c` files. Either each entity generates one pair of files (i.e. `89.h` and `89.c`), or the entities are gathered according to their original files (i.e. `frontend.h` and `frontend.c`).
- Call GCC with all relevant `.c` files to generate the executable.
- The `EntityStore` now persists everything to disk as soon as something changes. This is pretty slow. Better use some persist queue and a function that finally flushes things to disk. This flush function might be registered with PHP to be executed whenever the script terminates.

- In a git manner, add the possibility for a project to have a `.mwc` directory that contains the Maxwell compiler configuration files. This will also allow the intermediate build directory to be placed there. This will then allow the user to call `mwc build` and have the compiler find the `.mwc/config` file by itself. This also allows the easy generation of documentation and information lookups.
- With the `.mwc` directory in place, it should be possible to call `mwc info main.mw:6 x` to ask the compiler what `x` is on line 6 of `main.mw`. If `x` is in scope, the compiler should spit out everything it knows about it, i.e. type, value range, assumptions, etc..
- Add compiler options to output error messages in XML and HTML, as well as the currently existing colored command line output.
- Generate documentation.


General
=======
The following needs to be written:

- Coder: Classes to serialize stuff into an object hierarchy that is then automatically synthesized into XML, YAML or whatever. Special visitor classes (like `TokenSerializer`) should then walk through Tokens or AST Nodes and serialize them into the Coder. The Coder may then be dumped to an XML file.
- update Token Serializer
- AST Serializer
- LET Serializer
- Token, AST and LET Store classes


Syntax
======
The following AST nodes need to be implemented (parser and AST class):

- for loop
- return statement
- env statement
- unary operator
- binary operator
- array element accessor `[]`
- return statement
- type definition


Unfinished Parser Code
----------------------

- parseNewExpr


General Notes
=============

**Banker's Algorithm**: Check whether deadlocks may occur at all.