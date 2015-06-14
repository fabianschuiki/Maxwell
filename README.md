# Maxwell Programming Language

[![Build Status](https://travis-ci.org/fabianschuiki/Maxwell.svg?branch=master)](https://travis-ci.org/fabianschuiki/Maxwell) [![Coverage Status](https://img.shields.io/coveralls/fabianschuiki/Maxwell.svg)](https://coveralls.io/r/fabianschuiki/Maxwell)

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

Maxwell uses [Semantic Versioning](http://semver.org).


## Design Guidelines

- code is written in *C++11*
- source files have suffix `.cpp`
- header files have suffix `.hpp`
- sources and headers live in the `/maxwell` directory
- everything lives in the `maxwell` namespace
- files may be grouped into directories for better readability and structure
- files containing subnamespaces of `maxwell` must be placed in directories with the same name as the corresponding namespace (e.g. `maxwell::repository::interface` classes are to reside in the `maxwell/repository/interface` directory)
- directory names are lowercase
- includes are sorted by
  - origin (Maxwell first, then third party, then standard headers)
  - alphabet
- `using ...` and `using namespace ...` only in sources, absolutely not in headers (except for rare cases where the directive is to apply to the entire code base)
- type names are capitalized (e.g. *SourceRepository*)
- function names are camel-cased and start with a verb (e.g. `addFileToRepository`)
- variable names are camel-cased (e.g. `pendingFiles`)
- accessor functions are named `set...` and `get...`
- no underscores in type, function, or member names
- `nullptr` instead of `0` or `NULL` for pointers
- tests live in the `/test` directory (not interleaved with the source code)
- no `std::endl`, use the UNIX line feed `\n`
- write [good](http://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html) [commit](http://www.slideshare.net/TarinGamberini/commit-messages-goodpractices) [messages](https://robots.thoughtbot.com/5-useful-tips-for-a-better-commit-message)


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
