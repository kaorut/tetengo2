#!/bin/sh
# Makes a function definition list.
# Copyright (C) 2007-2013 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

rm -f "$SOLUTIONDIR/tools/tmp"

for f in `list_sources $SOLUTIONDIR`;
do
    echo "Parsing: $f" >&2;
    "$SOLUTIONDIR/tools/make_function_list.pl" "$f" >> "$SOLUTIONDIR/tools/tmp";
done

sort < "$SOLUTIONDIR/tools/tmp" | uniq;

rm -f "$SOLUTIONDIR/tools/tmp"
