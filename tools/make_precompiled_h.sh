#!/bin/sh
# Standard library usage lister.
# Copyright (C) 2007-2010 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

list()
{
    for f in "$1";
    do
        grep -h "^\#include <[a-z_\/]\+>" $f;
    done | sort | uniq
    echo ''
    for f in "$1";
    do
        grep -h "^\#include <boost\/" $f;
    done |
    grep -v "^\#include <boost\/test\/" | sort | uniq
}

SOURCES=`list_sources $SOLUTIONDIR && list_test_sources $SOLUTIONDIR`
list "$SOURCES"
