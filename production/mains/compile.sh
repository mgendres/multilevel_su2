#!/bin/bash
FILES="v0 v1a v1b v1c v1d v2 v3"

for f in $FILES; do
echo "Compiling $f"
../../scripts/make_bin.sh "$f.C -o $f.out"
done
