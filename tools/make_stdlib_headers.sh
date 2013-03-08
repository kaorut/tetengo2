#!/bin/sh
# Makes stdlib_headers.txt.
# Copyright (C) 2007-2013 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/zzz_paths.sh

for f in `list_sources $SOLUTIONDIR; list_test_sources $SOLUTIONDIR`;
do
     "$SOLUTIONDIR/tools/zzz_check_includes.pl" \
         "$SOLUTIONDIR" \
         "$f" \
         "$SOLUTIONDIR/tools/stdlib_headers.txt" \
         "show_progress" | \
         grep -v '^[A-Z]\+\: ';
done | sort | uniq
