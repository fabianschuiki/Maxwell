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
- variable declaration
- unary operator
- binary operator
- array element accessor `[]`
- return statement


Unfinished Parser Code
----------------------

- parseNewExpr


General Notes
=============

**Banker's Algorithm**: Check whether deadlocks may occur at all.