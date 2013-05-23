#!/bin/sh
# Checks typedefs.
# Copyright (C) 2007-2013 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/zzz_paths.sh

BASE_PATH="$SOLUTIONDIR/tools"

EXIT_STATUS=0
for f in `list_sources $SOLUTIONDIR; list_test_sources $SOLUTIONDIR`;
do
    $SOLUTIONDIR/tools/zzz_check_typedefs.pl $BASE_PATH $f $BASE_PATH/typedef_check_ignore.txt;
    test $? -eq 0 || EXIT_STATUS=1;
done

exit $EXIT_STATUS
