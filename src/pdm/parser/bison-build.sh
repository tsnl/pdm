#!/bin/bash

# macOS:
BISON=/usr/local/opt/bison/bin/bison
OFLAGS="--output=parser.tab.cc --defines=parser.tab.hh"
DFLAGS="-t --debug --verbose"
EFLAGS=$*

# $BISON parser.yy -o parser.tab.c $OUTPUT
# $BISON parser.yy -o parser.tab.c -t --debug --verbose -Wcex $OUTPUT

$BISON parser.yy $DFLAGS $OFLAGS $EFLAGS
