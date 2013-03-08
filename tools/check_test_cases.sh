#!/bin/sh
# Checks the test cases.
# Copyright (C) 2007-2013 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..

test -e "$SOLUTIONDIR/tools/functions.txt" || \
    "$SOLUTIONDIR/tools/make_function_list.sh" > "$SOLUTIONDIR/tools/functions.txt"
test -e "$SOLUTIONDIR/tools/test_cases.txt" || \
    "$SOLUTIONDIR/tools/make_test_case_list.sh" > "$SOLUTIONDIR/tools/test_cases.txt"

"$SOLUTIONDIR/tools/check_test_cases.pl" \
    "$SOLUTIONDIR/tools/functions.txt" \
    "$SOLUTIONDIR/tools/test_cases.txt" \
    "$SOLUTIONDIR/tools/check_test_cases_ignore.txt"
