#!/bin/sh
# Standard library usage lister.
# Copyright (C) 2007-2014 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/zzz_paths.sh

list()
{
    echo '// The standard library headers'
    echo ''
    for f in "$1";
    do
        grep -h "^\#\s*include <[a-z_\/]\+>" $f;
    done |
    $SOLUTIONDIR/tools/zzz_format_include.pl | sort | uniq
    echo ''
    echo ''
    echo '// Boost library headers'
    echo ''
    for f in "$1";
    do
        grep -h "^\#\s*include <boost\/" $f;
    done |
    grep -v "^\#\s*include <boost\/test\/" |
    $SOLUTIONDIR/tools/zzz_format_include.pl | sort | uniq
}

SOURCES=`list_sources $SOLUTIONDIR && list_test_sources $SOLUTIONDIR`
list "$SOURCES"
