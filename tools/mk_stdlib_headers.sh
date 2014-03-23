#/bin/sh
# Makes stdlib_headers.txt.
# Copyright (C) 2007-2014 kaoru
# $Id$

TOOLS_DIR=`dirname $0`
SOLUTION_DIR="$1"
test -n "$SOLUTION_DIR" || SOLUTION_DIR="$TOOLS_DIR/.."

STDLIB_HEADERS="$SOLUTION_DIR/tools/stdlib_headers.txt";
STDLIB_HEADERS_TMP=$STDLIB_HEADERS".tmp";

export LANG=C

source "$SOLUTION_DIR/tools/paths.sh"
for f in `list_sources $SOLUTION_DIR; list_test_sources $SOLUTION_DIR`;
do
    echo -n '.' 1>&2;
    "$TOOLS_DIR/zzz_mk_stdlib_headers.pl" "$f" $STDLIB_HEADERS;
done | sort | uniq > $STDLIB_HEADERS_TMP
echo '' 1>&2

mv $STDLIB_HEADERS_TMP $STDLIB_HEADERS
