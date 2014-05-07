Maxwell Programming Language
============================

Maxwell aims to combine the simplicity and flexibility of dynamically typed languages like PHP with the power and efficiency of statically typed languages like C++. The language always tends to assume the most generic case, giving maximum flexibility, but providing the possibility to further specify and narrow stuff down, giving maximum performance where required. Maxwell *in general steps out of your way, except when you explicitly ask it not to*.


Ideas and Concepts
------------------

- Supports Haskell-like pattern matching for functions
- Supports infix and postfix functions
- Functions are objects
- Higher order functions possible
- Multiple return values
- Option types (i.e. combination of multiple types into type, e.g. `string|null` for functions that return a string on success or null on failure)
- Type based switches (e.g. `x object = ...; switch (x.type) { case string: ...; case array: ...; }`)
- Type inference
- Generics
 

Operators
---------
- `..` is the concatenation operator. It should work on strings, arrays and other sequential collections of data.
