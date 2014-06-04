Backend Architecture
====================
This document briefly describes the architecture of Maxwell backends and how they integrate into the compiler's larger framework.

Information Segregation
-----------------------
The frontend of the Maxwell compiler is designed to read a `.mw` file from disk, turn it into a representation in memory clearly defined serialization capabilities and then running various compilation stages on this information. Thus, the frontend resolves types, generic code and any form of implicit functionality, and makes the necessary implementation decisions. The resulting data structure is a canonical AST; i.e. an explicit, fully typed representation of the program.

The backend of the compiler shall be designed to operate on this canonical AST, generating additional information specific to the backend and eventually composing the final output files. A backend for the C language will need to assign names to each entity, incorporating the entity's namespace and the like. It will also need to generate all the *vtable* structures for functions taking protocols as an argument, which produces additional information not clearly associated with a specific AST node.

As can be seen, the frontend generates and transforms the AST to obtain a data structure which has no more ambiguities and generic code. The backend generates additional information specific to the output and produces output files in the desired language.

Repository Structure
--------------------
The information the backends generated shall be persistent as well. This strongly suggests that this data should be incorporated into the already existing repository data structure which currently resides in the `ast` namespace. The shall implement a repository class specific to their needs that inherits from a base class common to all backend repositories. The compiler itself shall then add these backend-specific repositories to the main repository class instance. The main repository will then propagate the deletion of nodes to these repositories.

The resulting file structure will have a subdirectory in the main repository for each of the backends, named `backend-c`, `backend-java`, `backend-llvm`, etc.. This subdirectory may be populated at the discretion of the backend in charge of it and need not have any specific structure.

Changes to the Current Structure
--------------------------------
In order to accomodate the backend architecture, the `ast::Repository` class should be moved out of the `ast` namespace, as it is not directly associated with the AST itself, but rather acts as a generic, content-agnostic representation of a repository on disk.

The AST shall remain part of the frontend, possibly migrating the `ast` namespace to `frontend::ast`.

The main repository class shall no longer directly reference repositories in the AST namespace (i.e. `NodeRepository` et al.), but should rather provide a more general means of adding *subrepositories* that will hook up into the notification chain.

**Caution:** Before this is actually done, a careful check is necessary as to how the repository is used. It is important that the change applied to the root repository, i.e. removing explicitly typed references to subrepositories, does not overly complicate the AST and stage code.

**1)** An approach which is more comfortable to program against would be to make the root repository aware of the fixed subrepositories, i.e. the ones used in the frontend (`NodeRepository`, etc.), and have a properly-typed list of backend repositories which may be accessed by backend ID (`c`, `llvm`, `java`, ...).

**2)** Another approach which might be the most beautiful one in terms of code quality would be to go through the current AST and stage code and check whether that code uses dependency injection appropriately. Stages hold a reference to the main repository, but usually only need access to the node repository.

### Conclusion
Since the main `ast::Repository` class adds critical functionality in terms of connecting the various subrepositories and properly propagating removal of nodes and the like to the required repositories, it may be desirable to keep the current structure, with the main repository being aware of all its subrepositories directly. The backend repositories would then simply be added as a list of well defined classes that integrate into the same mechanism. The main repository would propagate node deletion and stage invalidation to the backend repositories.

Stage-based Backends
--------------------
The operation of the individual backends shall be stage-based similar to the frontend. This allows for coordinated execution of the compilation stages. In that regard, a backend defines *additional stages* that will execute after all the frontend stages. Dependencies between stages might be of interest. In general, changes to the AST will invalidate all backend stages of that node immediately.