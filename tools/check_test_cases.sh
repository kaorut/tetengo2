#!/bin/sh
# Checks the test cases.
# Copyright (C) 2007-2018 kaoru
# $Id$

TOOLS_DIR=`dirname $0`
SOLUTION_DIR="$1"
test -n "$SOLUTION_DIR" || SOLUTION_DIR="$TOOLS_DIR/.."
SILENT="$2"

LANG=C

FUNCTIONS_TXT="$SOLUTION_DIR/tools/zzz_test_case_check_functions.txt"
TESTCASES_TXT="$SOLUTION_DIR/tools/zzz_test_case_check_test_cases.txt"

echo 'Checking the test cases...'

(test -z "$SILENT" && test -e "$FUNCTIONS_TXT") || \
    "$TOOLS_DIR/zzz_make_function_list.sh" "$SOLUTION_DIR" "$SILENT" > "$FUNCTIONS_TXT"
(test -z "$SILENT" && test -e "$TESTCASES_TXT") || \
    "$TOOLS_DIR/zzz_make_test_case_list.sh" "$SOLUTION_DIR" "$SILENT" > "$TESTCASES_TXT"

"$TOOLS_DIR/zzz_check_test_cases.pl" \
    "$FUNCTIONS_TXT" "$TESTCASES_TXT" "$SOLUTION_DIR/tools/test_case_check_ignore.txt"

exit $?
