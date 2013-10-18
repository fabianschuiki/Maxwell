Maxwell Programming Language
============================

Maxwell is a modern, high-level programming language that aims to combine the comfort and expressiveness of scripting languages with the power and efficiency of a compiled language. It aims to achieve the following goals:

- embrace refactoring as a natural part of programming
- keep repetition to a minimum (DRY)
- everything is an expression, i.e. no statements
- focus on generic programming
- imperative
- strict duck typing
- functions, strings, arrays, sets and maps are first class citizens
- implicit interfaces
- operator overloading
- type inference


How To Dive In
--------------
**For the curious**: The document `concept/Ideas.html` contains random snippets of code and ideas.

Current development is happening in the `cpp` directory, where a C++ version of the compiler is taking shape. It currently uses *flex/bison* for tokenizing and parsing, although this will probably be replaced by a custom implementation.

To get things up and running, create a *build* directory in *cpp* and build everything:

    $ mkdir cpp/build
    $ cd cpp/build
    $ cmake ..
    $ make

As soon as you have some experimental Maxwell code written:

- `$ source/test/mwcparse <something.mw>` to parse the given file;
- `$ source/test/mwcstage 1.1 1.2 1.3 ...` to analyze and process the given entities (usually starting at 1.1 to the number of root statements in your source file);
- `$ source/test/mwcdump 1.1` to see the abstract syntax tree of entity 1.1 in the console, useful for visualizing what the compiler is actually doing;
- `$ source/test/mwcbendc 1.1` to call the C backend on entity 1.1, generating C code for it.