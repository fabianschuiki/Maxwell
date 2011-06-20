Maxwell Programming Language
============================

Root Section
------------
The root section of a file is the topmost level of statements, that is, such that are not enclosed
in any kind of block structure.

The root section may contain:
- import statements
- class declarations
- function declarations

Maxwell combines the concept of namespaces and classes. Therefore only global functions and class
declarations are allowed at root level. Global variables are forbidden.


Requirements
------------
-
    property int x;
-
    int x;
    property x;
-
    int x;
    property (readonly) x;
-
	property (readonly) int x;
-
	property {
		(readonly) int x;
		float y;
		String z;
	}