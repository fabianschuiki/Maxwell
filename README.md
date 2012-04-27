Maxwell Programming Language
============================

Overview
--------
There are two compilers in this repository. One is written in PHP in order to
provide the most basic Maxwell compiling capabilities. The other is written in Maxwell itself and acts as a language development tool. *Currently the PHP compiler is being developed*.

How to try stuff
----------------
The PHP compiler changes rapidly. Using `$ make` you may compile the `source/main.mw` file, which is also used to develop new language features. This will output a vast amount of information in the `build` directory. Note that all entities of the source (types, functions, etc.) are split up when compiling. Of particular interest are the `build/*.<highest digit>.let-nice.html` files, which contain a dump of the language entity. The `build/legend.txt` file helps looking up UUIDs of the entities.

About the Source
----------------
The PHP compiler is located at `php/bin/mwc`, its source files in `php/lib`.

