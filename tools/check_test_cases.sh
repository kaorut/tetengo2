#!/bin/sh
# Checks the test cases.
# Copyright (C) 2007-2013 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..

test -e "$SOLUTIONDIR/tools/zzz_functions.txt" || \
    "$SOLUTIONDIR/tools/zzz_make_function_list.sh" > "$SOLUTIONDIR/tools/zzz_functions.txt"
test -e "$SOLUTIONDIR/tools/zzz_test_cases.txt" || \
    "$SOLUTIONDIR/tools/zzz_make_test_case_list.sh" > "$SOLUTIONDIR/tools/zzz_test_cases.txt"

"$SOLUTIONDIR/tools/zzz_check_test_cases.pl" \
    "$SOLUTIONDIR/tools/zzz_functions.txt" \
    "$SOLUTIONDIR/tools/zzz_test_cases.txt" \
    "$SOLUTIONDIR/tools/test_case_check_ignore.txt"
