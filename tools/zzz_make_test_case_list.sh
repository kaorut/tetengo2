#!/bin/sh
# Makes a test case list.
# Copyright (C) 2007-2019 kaoru
# $Id$

TOOLS_DIR=`dirname $0`
SOLUTION_DIR="$1"
test -n "$SOLUTION_DIR" || SOLUTION_DIR="$TOOLS_DIR/.."
SILENT="$2"

LANG=C

TEMP_FILE="$SOLUTION_DIR/tools/tmp"
rm -f "$TEMP_FILE"

. $SOLUTION_DIR/tools/paths.sh
for f in `list_test_sources $SOLUTION_DIR`;
do
    test -z "$SILENT" && echo -ne "Parsing: $f        \r" >&2;
    "$TOOLS_DIR/zzz_make_test_case_list.pl" "$f" >> "$TEMP_FILE";
done
test -z "$SILENT" && echo -ne "Done.                                                        \n" >&2

sort < "$TEMP_FILE" | uniq;

rm -f "$TEMP_FILE"
