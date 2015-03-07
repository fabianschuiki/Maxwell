#!/bin/bash
# Copyright (c) 2015 Fabian Schuiki
# Parses Maxwell files, runs them through the compiler stages, and performs the
# backend operations on them.

set -e
rm -rf mwcrepo
NODES=$("@CMAKE_BINARY_DIR@/maxwell/test/mwcparse" $@ | tail -n 1)
"@CMAKE_BINARY_DIR@/maxwell/test/mwcstage" $NODES
FRAGMENTS=$("@CMAKE_BINARY_DIR@/maxwell/test/mwcbendc" $NODES)
FILES=$("@CMAKE_BINARY_DIR@/maxwell/test/mwcbendcpkg" $FRAGMENTS | grep .c$)
@CMAKE_C_COMPILER@ -lm $FILES
