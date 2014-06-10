# Maxwell Programming Language

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

The compiler is continuously built and tested: [![Build Status](https://travis-ci.org/fabianschuiki/Maxwell.svg?branch=master)](https://travis-ci.org/fabianschuiki/Maxwell)


## How To Dive In

To get things up and running create a *build* directory, ask *cmake* to generate a build system for you, and build the compiler as follows:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ ln -s ../maxwell/runc.sh runc

The last command symlinks the `../maxwell/runc.sh` script into your build directory so you can build things easily. This file calls the low-level plumbing commands that parse and process Maxwell source files, generate C code, and package the generated code into C source files. It then feeds this files to *gcc* to generate an executable.

Take a look at the `tests` directory for some sample snippets of Maxwell code; or write your own if you feel like it. To compile your source run `./runc yourfile.mw`, which will compile your code to `a.out`. You might also be interested in the `*.{c|h}` files generated next to your source file, as they show you how the Maxwell compiler transforms your input to C code.

**For the curious**: The document `language/Ideas.html` contains random snippets of code and ideas.
