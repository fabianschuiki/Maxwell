Maxwell Programming Language
============================

Overview
--------
There are two compilers in this repository. One is written in PHP in order to
provide the most basic Maxwell compiling capabilities. The other is written in Maxwell itself and acts as a language development tool. *Currently the PHP compiler is being developed*.

How to try stuff
----------------
The PHP compiler changes rapidly. For debugging the current development, the `debug/debug.mw` file is compiled using `$ php/bin/debug.php debug/debug.mw`. The compiler dumps all its output to `debug/build`. Of particular interest is the `debug/build/debug.let.html` output file that contains a dump of the *Language Entity Tree*, i.e. the entities parsed from the source file along with the type analysis and specializations.

About the Source
----------------
The PHP compiler source files are located in `php/lib`. There is a rudimentary driver file in `php/bin/debug.php` that initializes the fundamental components `SourceFile`, `Lexer`, `Parser`, and `Analyzer`, and executes the compilation.

Most of the files on the root level of `php/lib` are now *obsolete* and may be ignored.