#!/bin/sh

# Standard library usage lister.
# $Id$
# Copyright (C) 2007-2008 kaoru

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

list()
{
    for f in `$1`;
    do
        grep "^\#include <[a-z]\+>" $f;
    done | sort | uniq
    echo ''
    for f in `$1`;
    do
        grep "^\#include <boost\/" $f;
    done | sort | uniq
}

echo '// sources'
list "list_sources $SOLUTIONDIR"
echo ''
echo '// test sources'
list "list_test_sources $SOLUTIONDIR"
