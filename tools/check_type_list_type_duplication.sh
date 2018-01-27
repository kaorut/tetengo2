#/bin/sh
# Checks type list type duplications.
# Copyright (C) 2007-2018 kaoru
# $Id$

TOOLS_DIR=`dirname $0`
SOLUTION_DIR="$1"
test -n "$SOLUTION_DIR" || SOLUTION_DIR="$TOOLS_DIR/.."

EXIT_STATUS=0

echo 'Checking the type list type duplications...'

. "$SOLUTION_DIR/tools/paths.sh"
for f in `list_sources $SOLUTION_DIR; list_test_sources $SOLUTION_DIR`;
do
    "$TOOLS_DIR/zzz_check_type_list_type_duplication.pl" "$f";
    test $? -eq 0 || EXIT_STATUS=1;
done

exit $EXIT_STATUS
