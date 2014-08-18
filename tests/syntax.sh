#!/bin/bash
# Copyright (c) 2014 Fabian Schuiki

# A simple bash script that parses Maxwell files as a means of testing the
# compiler.

set -e
rm -rf mwcrepo
"@CMAKE_BINARY_DIR@/maxwell/test/mwcparse" $@
