#!/bin/bash

rm -rf cfgs
mkdir cfgs
rm -rf data
mkdir data

../../scripts/make_bin.sh main.C
./a.out args/coupling.arg args/evo.arg args/lattice.arg args/plaquette.arg 
