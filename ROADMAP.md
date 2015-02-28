# Maxwell Roadmap
The following is a brief overview of the development roadmap for the Maxwell compiler and language. The general concept is as follows:

- *v0.1*: Develop the compiler and language far enough such that meaningful programs and libraries can be written.
- *v0.2*: Replace the first parts of the compiler written in C++ with code written in Maxwell.
- *v0.3*: Have the entire compiler written in Maxwell. This concludes the bootstrapping process.

A list of must-have features for specific versions follows.


## v0.1

- call native functions, use native types
- constant and mutable arrays
- constant and mutable maps
- constant and mutable sets
- constant and mutable strings
- standard library for arrays
- standard library for maps
- standard library for sets
- standard library for strings
- expose functions and types to native code (i.e. compile into a C library)
- manual memory management
- defer expression


## v0.2

- rewrite lexer in Maxwell
- rewrite parser in Maxwell


## v0.3

- automated memory management


## v1.0

- self-synthesis (Maxwell code can generate more code at compile time)
- type inference
- finish mwc program
