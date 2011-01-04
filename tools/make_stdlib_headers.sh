#!/bin/sh
# Makes stdlib_headers.txt.
# Copyright (C) 2007-2011 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

for f in `list_sources $SOLUTIONDIR; list_test_sources $SOLUTIONDIR`;
do
     "$SOLUTIONDIR/tools/check_includes.pl" \
         "$SOLUTIONDIR" \
         "$f" \
         "$SOLUTIONDIR/tools/stdlib_headers.txt" \
         "show_progress" | \
         grep -v '^[A-Z]\+\:';
done | sort | uniq
