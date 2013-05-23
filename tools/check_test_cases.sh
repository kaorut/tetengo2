#!/bin/sh
# Checks the test cases.
# Copyright (C) 2007-2013 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..

FUNCTIONS_TXT="$SOLUTIONDIR/tools/zzz_test_case_check_functions.txt"
TESTCASES_TXT="$SOLUTIONDIR/tools/zzz_test_case_check_test_cases.txt"

echo 'Checking the test cases...'

(test -n "$1" && test -e "$FUNCTIONS_TXT") || \
    "$SOLUTIONDIR/tools/zzz_make_function_list.sh" "$2" > "$FUNCTIONS_TXT"
(test -n "$1" && test -e "$TESTCASES_TXT") || \
    "$SOLUTIONDIR/tools/zzz_make_test_case_list.sh" "$2" > "$TESTCASES_TXT"

"$SOLUTIONDIR/tools/zzz_check_test_cases.pl" \
    "$FUNCTIONS_TXT" "$TESTCASES_TXT" "$SOLUTIONDIR/tools/test_case_check_ignore.txt"

exit $?
