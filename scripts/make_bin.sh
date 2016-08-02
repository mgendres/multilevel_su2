#!/bin/bash

LIB=su2_pure_gauge
SRCDIR=${0%%/scripts*}/
BUILDDIR=${0%%/scripts*}/

CXX=g++

LDFLAGS=""
CXXFLAGS="-O3"
ARFLAGS=

INCLUDE_FLAGS="-I$SRCDIR/include -I$SRCDIR/src"

MAIN=$1
$CXX $CXXFLAGS $MAIN $BUILDDIR/$LIB.a $LDFLAGS $INCLUDE_FLAGS
