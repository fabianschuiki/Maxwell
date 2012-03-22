- Create a Type class
  - name, fields
  - location of definition (AST node, other file, etc.)
  
- Create a Func class
  - name
  - patterns
  
- Create a FuncPattern class
  - input/output arguments
  - location of definition
  - function body

- Extend Scope class
  - Separate function array
  - Separate type array
  - Add function search which looks for FuncPattern instances for a given name
  - Add type search

- Implement the type operator (probably '@') which should return the `Type` instance for the given object. For primitive types this has to be done statically at compile time.

- Write a late binding function which tries to resolve the types of generic variables ('any') and function calls. Basically everything that depends on type inference having taken place.

- Add specializations where functions that accept `any` as a parameter are listed with their generic parameters replaced by specific incarnations.

- Add type variables where functions may be defined that allow generic parameters, but only in specific combinations. E.g.: the builtin `+`, `-`, `*`, `/` and `=` operators would be defined as functions `(a, a) -> (a)`. Of course once a function is finally bound, additional type deduction may take place.