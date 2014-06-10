#!/bin/bash
# Copyright (c) 2013-2014 Fabian Schuiki

# A simple bash script that parses Maxwell files, runs them through the front-
# and backend, and packages them into source files. The source files are fed
# through gcc to produce a debuggable executable.

set -e
NODES=$("maxwell/test/mwcparse" $@ | tail -n 1)
"maxwell/test/mwcstage" $NODES
"maxwell/test/mwcbendc" $NODES | xargs "maxwell/test/mwcbendcpkg" | grep ".*\.c" | xargs gcc -g
