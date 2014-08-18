#!/bin/bash
# Copyright (c) 2014 Fabian Schuiki

# A simple bash script that parses Maxwell files and runs the compiler stages
# for them.

set -e
DST=$(mktemp -d /tmp/mwc-stage-XXXXXX)

cd "$DST"
NODES=$("@CMAKE_BINARY_DIR@/maxwell/test/mwcparse" $@ | tail -n 1)
"@CMAKE_BINARY_DIR@/maxwell/test/mwcstage" $NODES
