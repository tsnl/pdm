#!/bin/bash

# macOS:
BISON=/usr/local/opt/bison/bin/bison
OUTPUT="--output=parser.tab.cc --defines=parser.tab.hh"

# $BISON parser.yy -o parser.tab.c $OUTPUT
# $BISON parser.yy -o parser.tab.c -t --debug --verbose -Wcex $OUTPUT
$BISON parser.yy -o parser.tab.c -t --debug --verbose $OUTPUT

