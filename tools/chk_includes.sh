#/bin/sh
# Checks the #include directives.
# Copyright (C) 2007-2014 kaoru
# $Id$

TOOLS_DIR=`dirname $0`
SOLUTION_DIR=$1

EXIT_STATUS=0

echo 'Checking the #include declarations...'

source "$TOOLS_DIR/paths.sh"
for f in `list_sources $SOLUTION_DIR; list_test_sources $SOLUTION_DIR`;
do
    "$TOOLS_DIR/chk_includes.pl" "$f" "$TOOLS_DIR/stdlib_headers.txt";
    test $? -eq 0 || EXIT_STATUS=1;
done

exit $EXIT_STATUS
