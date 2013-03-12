#!/bin/sh
# Makes a test case list.
# Copyright (C) 2007-2013 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/zzz_paths.sh

rm -f "$SOLUTIONDIR/tools/tmp"

for f in `list_test_sources $SOLUTIONDIR`;
do
    echo -ne "Parsing: $f        \r" >&2;
    "$SOLUTIONDIR/tools/zzz_make_test_case_list.pl" "$f" >> "$SOLUTIONDIR/tools/tmp";
done
echo -ne "Done.                                                        \n" >&2

sort < "$SOLUTIONDIR/tools/tmp" | uniq;

rm -f "$SOLUTIONDIR/tools/tmp"
