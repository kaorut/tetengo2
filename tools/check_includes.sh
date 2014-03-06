#!/bin/sh
# Checks the #include directives.
# Copyright (C) 2007-2014 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

EXIT_STATUS=0

echo 'Checking the #include declarations...'

for f in `list_sources $SOLUTIONDIR; list_test_sources $SOLUTIONDIR`;
do
    "$SOLUTIONDIR/tools/zzz_include_order.pl" "$f";
    "$SOLUTIONDIR/tools/zzz_check_includes.pl" \
        "$SOLUTIONDIR" \
        "$f" \
        "$SOLUTIONDIR/tools/stdlib_headers.txt" \
        "$1" \
        "$2";
    test $? -eq 0 || EXIT_STATUS=1;
done

exit $EXIT_STATUS
