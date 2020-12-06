#!/bin/bash

# macOS:
BISON=/usr/local/opt/bison/bin/bison

# $BISON parser.yy -o parser.tab.c -d
# $BISON parser.yy -o parser.tab.c -d -t --debug --verbose -Wcex
$BISON parser.yy -o parser.tab.c -d -t --debug --verbose
