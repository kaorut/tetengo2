#!/bin/sh
# Makes a function definition list.
# Copyright (C) 2007-2014 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

rm -f "$SOLUTIONDIR/tools/tmp"

for f in `list_sources $SOLUTIONDIR`;
do
    test -z "$1" && echo -ne "Parsing: $f        \r" >&2;
    "$SOLUTIONDIR/tools/zzz_make_function_list.pl" "$f" >> "$SOLUTIONDIR/tools/tmp";
done
test -z "$1" && echo -ne "Done.                                                        \n" >&2

sort < "$SOLUTIONDIR/tools/tmp" | uniq;

rm -f "$SOLUTIONDIR/tools/tmp"
