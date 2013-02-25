Maxwell TODO
============
This file lists general tasks that need to be done.


### Import/Export System
The entire entity and import/export system should be rewritten. Entities should keep a list of entity names they know about, and a list of entities they actually reference and use. The compiler should then properly include all the used entities.

Implement a better referencing and import/export strategy. Entities should generate lists of entities they import and know about, thus faciliating dependency trees.


### Aggregate Compiler Output
The compiler should produce C code snippets for the root entities, but in the end re-combine them in a .c and .h file that is named the same as the original Maxwell file. This would increase readability and would allow comments to be copied to the compiled files.


### Pretty Printer
Write a pretty printer that is able to produce nice Maxwell code from a given entity tree. This would allow improved debugging as the individual entities may be dumped at different stages of the compilation process. The pretty printer would also be used in the documentation system when code snippets are required. Also, the compiler will resolved a lot of syntax sugar in the future, so it would be necessary to see the Maxwell code that is actually compiled after resolving them.