#!/bin/sh
# Checks the #include directives.
# Copyright (C) 2007-2013 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/zzz_paths.sh

for f in `list_sources $SOLUTIONDIR; list_test_sources $SOLUTIONDIR`;
do
    echo '['$f']';
    "$SOLUTIONDIR/tools/zzz_include_order.pl" < "$f";
    "$SOLUTIONDIR/tools/zzz_check_includes.pl" \
        "$SOLUTIONDIR" \
        "$f" \
        "$SOLUTIONDIR/tools/stdlib_headers.txt" \
        "$1";
    echo '';
done
