#/bin/sh
# Checks the #include directives.
# Copyright (C) 2007-2016 kaoru
# $Id$

TOOLS_DIR=`dirname $0`
SOLUTION_DIR="$1"
test -n "$SOLUTION_DIR" || SOLUTION_DIR="$TOOLS_DIR/.."

EXIT_STATUS=0

echo "Checking the #include declarations in \"$SOLUTION_DIR\" ..."

. "$SOLUTION_DIR/tools/paths.sh"
for f in `list_sources $SOLUTION_DIR; list_test_sources $SOLUTION_DIR`;
do
    "$TOOLS_DIR/zzz_check_includes.pl" "$f" "$SOLUTION_DIR/tools/stdlib_headers.txt";
    test $? -eq 0 || EXIT_STATUS=1;
done

exit $EXIT_STATUS
