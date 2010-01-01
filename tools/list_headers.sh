#!/bin/sh
# Standard library usage lister.
# Copyright (C) 2007-2010 kaoru
# $Id$

LANG=C
SOLUTIONDIR=`dirname $0`/..
. $SOLUTIONDIR/tools/paths.sh

for f in `list_test_sources $SOLUTIONDIR`;
do
    $SOLUTIONDIR/tools/extract_stblib_usages.pl \
        $SOLUTIONDIR/tools/stdlib_headers.txt NOINC < $f;
done | sort | uniq
