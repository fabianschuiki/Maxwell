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
- call expression
- member access operator `.`

Things to do with the parser in general:

- update func statement parsing to use backtick operator notation instead of ()


Unfinished Parser Code
----------------------

- parseVarExpr
- parseNewExpr
- parseCallExpr


General Notes
=============

**Banker's Algorithm**: Check whether deadlocks may occur at all.