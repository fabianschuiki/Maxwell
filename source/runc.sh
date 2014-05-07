#!/bin/bash
# Copyright (c) 2013-2014 Fabian Schuiki

# A simple bash script that parses Maxwell files, runs them through the front-
# and backend, and packages them into source files. The source files are fed
# through gcc to produce a debuggable executable.

set -e
NODES=$("source/test/mwcparse" $@ | tail -n 1)
"source/test/mwcstage" $NODES
"source/test/mwcbendc" $NODES | xargs "source/test/mwcbendcpkg" | grep ".*\.c" | xargs gcc -g
