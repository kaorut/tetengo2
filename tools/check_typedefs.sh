#!/bin/sh
# Checks typedefs.
# Copyright (C) 2007-2014 kaoru
# $Id$

TOOLS_DIR=`dirname $0`
SOLUTION_DIR="$1"
test -n "$SOLUTION_DIR" || SOLUTION_DIR="$TOOLS_DIR/.."

LANG=C

echo 'Checking the typedefs...'

EXIT_STATUS=0
. "$SOLUTION_DIR/tools/paths.sh"
for f in `list_sources $SOLUTION_DIR; list_test_sources $SOLUTION_DIR`;
do
    $TOOLS_DIR/zzz_check_typedefs.pl $TOOLS_DIR $f $SOLUTION_DIR/tools/typedef_check_ignore.txt;
    test $? -eq 0 || EXIT_STATUS=1;
done

exit $EXIT_STATUS
