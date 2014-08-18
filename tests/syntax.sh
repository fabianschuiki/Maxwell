#!/bin/bash
# Copyright (c) 2014 Fabian Schuiki

# A simple bash script that parses Maxwell files as a means of testing the
# compiler.

set -e
DST=$(mktemp -d /tmp/mwc-syntax-XXXXXX)

cd "$DST"
"@CMAKE_BINARY_DIR@/maxwell/test/mwcparse" $@
