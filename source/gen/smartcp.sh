#!/bin/bash
# Copyright (c) 2014 Fabian Schuiki.
# Copies files from one directory to another if they don't yet exist or their
# checksums differ. Useful to copy the output of a code generator into the
# source tree, since only necessary recompiles are triggered.

if [ -z "$1" ] || [ -z "$2" ]; then
	echo "usage: $0 <src_dir> <dst_dir>"
	exit 1
fi

NUM_COPIED=0
for sf in $(echo "$1/*"); do
	name=$(basename "$sf");
	df="$2/$name"

	if ! [ -e "$df" ] || ! diff -q "$sf" "$df" > /dev/null; then
		echo "copying file $name"
		NUM_COPIED=$(expr $NUM_COPIED + 1)
		cp "$sf" "$df"
	fi
done;

if [ $NUM_COPIED = 1 ]; then
	echo "copied 1 file"
elif [ $NUM_COPIED -gt 1 ]; then
	echo "copied $NUM_COPIED files"
fi
