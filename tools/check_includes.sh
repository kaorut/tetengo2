#!/bin/sh
# Checks the #include directives.
# Copyright (C) 2007-2011 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

for f in `list_sources $SOLUTIONDIR; list_test_sources $SOLUTIONDIR`;
do
    echo '['$f']';
    "$SOLUTIONDIR/tools/include_order.pl" < "$f";
    "$SOLUTIONDIR/tools/check_includes.pl" \
        "$SOLUTIONDIR" \
        "$f" \
        "$SOLUTIONDIR/tools/stdlib_headers.txt" \
        "$1";
    echo '';
done
