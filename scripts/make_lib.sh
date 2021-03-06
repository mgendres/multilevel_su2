#!/bin/bash

LIB=su2_pure_gauge
SRCDIR=$PWD
BUILDDIR=$PWD
SRCDIR2=$SRCDIR/src
BUILDDIR2=$BUILDDIR/objs

CC=gcc
CXX=g++
AR=ar

LDFLAGS=""
CXXFLAGS="-O3"
ARFLAGS="ruv"

INCLUDE_FLAGS="-I$SRCDIR/include -I$SRCDIR/src"

if [ -d $BUILDDIR2 ]; then
  rm -r $BUILDDIR2
fi

mkdir $BUILDDIR2
cd $BUILDDIR2

$CXX $CXXFLAGS $LDFLAGS $INCLUDE_FLAGS -c $SRCDIR2/*.C
$AR $ARFLAGS $BUILDDIR/$LIB.a $BUILDDIR2/*.o
ranlib  $BUILDDIR/$LIB.a

